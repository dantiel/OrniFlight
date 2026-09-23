# ONDAS Development — Mathematical Methods and Simulated Testing

This article documents the statistical and adaptive generation of the ONDAS stabilizer: the
**envelope modules** (B) that measure how much of the attitude error is real signal, the
**Vold–Kalman order tracker** (A) that extracts the flap-synchronous component under variable
frequency sweeps, the **consensus gate** that lets A take over only when both independent
extractors agree, the **rearrangement-invariant scheduling** underneath the whole chain, and the
**ferocity phase-lock model** that re-frames ferocity as a local clock shift taking over the wind.
Every method was prototyped in the Ruby simulation harness (`sim_ferocity.rb`) before the
firmware port; the simulated-testing section reproduces the discriminating numbers.

---

## 1. The Problem: A Stabilizer That Cannot See Its Own Error

An ornithopter's attitude error is a mixture of two components:

1. **Flap-synchronous oscillation** — the component the wings can actually correct. It lives
   exactly at the wingbeat frequency ω(t) and its harmonics.
2. **Broadband disturbance** — gusts, turbulence, sensor noise, servo chatter. It carries most
   of the RMS energy but is largely uncorrectable phase-bound actuation.

The classical PID loop cannot tell them apart. Correcting broadband noise at the wingbeat phase
*dissipates* control authority and excites the airframe. Correcting the synchronous component
*late* (wrong stroke phase) is equally wasteful. The development goal was therefore:

> Measure the two components **separately, online, on the flight controller**, and schedule
> every ONDAS layer from that measurement — instead of from fixed gains.

---

## 2. Architecture: The Chain B → A → ONDAS

~~~mermaid
flowchart TD
    subgraph ERR["Attitude error (per axis)"]
        e["e = setpoint − measured"]
    end
    subgraph B["B — Statistical Envelope (ondas_metrics)"]
        B1["λ_e(s) histogram<br/>32 log-bins, τ≈1 s leak"]
        B2["q90 · weak-L² · tail mass"]
        B3["Poincaré phase envelope<br/>16 golden-angle bins @ reversal"]
    end
    subgraph GATE["Consensus Gate"]
        G1["r = EMA(b·sinθ)/√(EMA(sin²θ)·EMA(b²))"]
        G2["α = soft-knee(r), floor 0.3<br/>τ_in 1 s, τ_out 0.4 s"]
    end
    subgraph A["A — Vold–Kalman Order Tracker (ondas_tracker)"]
        A1["2nd-order resonator, ζ=0.06, Q≈8.3"]
        A2["coefficients follow ω(t) per sample"]
    end
    subgraph LAYERS["ONDAS 8 Layers (oscillator domain)"]
        L1["CADENCE · FEROCITY · BALANCE · WARP"]
        L2["RESONANCE · PRESCIENCE · ESPELHO · SAUDADE · ANCHOR"]
    end
    e --> B1 --> B2
    e --> B3
    e --> A1 --> A2 -->|"b (tracker output)"| G1
    A1 -.->|"sinθ (lock-in ref)"| G1
    G1 --> G2 -->|"α ∈ [−1, +1]"| L1
    A2 -->|"replace-blend:<br/>legacy·(1−|α|) + 0.5·b·α"| L2
    B2 -.->|"windup q90 clamp"| L1
    B2 -.->|"D-cutoff adaptation (roadmap)"| L2
~~~

**Design principle — open loop.** The tracker consumes the *pre-resonance* error: it never sees
its own contribution, so the gate cannot fall into a self-confirming loop. The phase envelope
(B3) is deliberately **not** part of the activation path — it stays a pure measurement, the
blackbox evidence that will verify the tracker in real flight.

**Fail-safe invariance.** At α = 0 the replace-blend reduces to the legacy resonance path
exactly. No validated ONDAS layer is touched by the new chain until both extractors agree.

---

## 3. Method A: Vold–Kalman Order Tracking — Reorganizing the Transient Clock

Classical bandpass filters are tuned to a *fixed* center frequency. Under a throttle chirp the
wingbeat frequency moves, and a fixed filter detunes: the extracted amplitude collapses and the
phase rotates. The Vold–Kalman order tracker solves this by making the filter coefficients
*follow* the instantaneous frequency:

~~~text
Resonator (order 1, analog prototype):
    b'' + 2·ζ·ω(t)·b' + ω(t)²·b = 2·ζ·ω(t)·e'

Discretization (per sample, explicit Euler, DT = loop period):
    b[n+1] = b[n] + DT · v[n]
    v[n+1] = v[n] + DT · ( 2·ζ·ω(t)·(e[n] − e[n−1]) − 2·ζ·ω(t)·v[n] − ω(t)²·b[n] )

with ζ = 0.06  →  Q = 1/(2ζ) ≈ 8.3
~~~

ω(t) is the **measured** wingbeat rate (flap phase derivative) — the tracker's clock is the
wing's own clock, not the lab clock. Below ω < 0.1 rad/s the states are zeroed: an Euler
resonator on stale coefficients drifts linearly during glide, a failure mode the simulation
never saw because it never glided. The firmware port found it; the fix is a hard state reset.

The lock-in reference `sinθ` (flap phase) forms the second, *independent* extractor: the
wingbeat-coherent component of the error is exactly the projection of the tracker output onto
the flap sine. Two extractors, one measurement, zero shared code path.

---

## 4. Method B: The λ_e(s) Envelope — Rearrangement-Invariant Statistics

Following the rearrangement-invariant viewpoint (Tao, 247A): oscillatory structure is ignored;
the distribution of |e| *is* the signal. Two views of one 32-bin module:

### 4.1 Raw view — λ_e(s), weak-L², q90

~~~text
λ_e(s) = P( |e| > s )          (survival function, 3 axes)
bins:   32 log-spaced over [0.25, 256] °/s
leak:   exponential, τ ≈ 1 s (shift derived from dT via float-bit ilog2)

weak-L² = sup_s  s · √λ(s)     (scale-invariant tail norm)
q90     = interpolated 90th percentile
~~~

The weak-L² norm is the correct tool for a controller: ordinary RMS is dominated by rare large
events (gusts), but the *control* decision needs the typical scale. q90 feeds two existing
consumers: the weak-L¹ anti-windup clamp (Section 6) and, later, D-cutoff adaptation.

### 4.2 Phase view — the Poincaré envelope

~~~text
16 bins, one per stroke reversal
bin index k → k·0.618·16 mod 16   (golden-angle rotation)
EMA 1/16 per strobe
metric = ‖⟨e⟩_θ‖₂,∞ = sup over bins of |phase-averaged error|
~~~

The phase view demodulates the error against the flap phase and averages per bin. What survives
the averaging is the **synchronous residual** — exactly the quantity the tracker must reduce.

---

## 5. Serendipity by Construction: The Golden-Angle Strobe

The first naive implementation sampled every loop tick into a phase histogram — and exposed a
genuine number-theoretic trap:

~~~text
ω = 4.8 rad/s, DT = 1 ms  →  2π/(ω·DT) = 1308.997 samples per cycle
~~~

Lab clock and flap clock are **almost commensurable**. The sampling grid repeats nearly
identically from cycle to cycle, so the histogram converges only with the *beat period*
(≈ 90 s). At firmware rates the trap is worse: 4 kHz loop, 6 Hz flap = 666.67 samples/cycle —
a per-sample histogram would *never* converge on some phase bins.

The fix is the phyllotactic constellation: **one sample per stroke reversal**, bin index
rotated by the golden angle {k·0.618}. Deterministic uniform coverage, minimal sample count,
immune to any clock ratio — because the coverage law depends only on the irrationality of the
rotation, not on the clocks.

~~~mermaid
flowchart LR
    R["Stroke reversal"] --> S["Strobe sample"]
    S --> B["bin k = round(k·0.618·16) mod 16"]
    B --> E["EMA 1/16 per bin"]
    E --> M["‖⟨e⟩_θ‖₂,∞"]
    R --> N["k += 1"]
    N --> R
~~~

---

## 6. Scheduling: Marcinkiewicz Soft-Knee and Weak-L¹ Anti-Windup

The substrate beneath all ONDAS layers:

**Soft-knee amplitude scheduling** — the flapping amplitude A is shaped by the geometric
soft-knee

~~~text
A = (A_lin · L) / √(A_lin² + L²)
~~~

which is the canonical interpolation between linear authority (small signal: A ≈ A_lin, the
`flap_magnitude` sensitivity is preserved exactly) and saturation (large signal: A → L). The
former hard clamp produced a kink in dA/dThrottle — every ONDAS layer inherited a discontinuity
of its effectiveness there.

**Weak-L¹ anti-windup** — the I-branch feeds BALANCE (up/down asymmetry), and SAUDADE would
permanently absorb any windup-induced bias as learned trim. The fix: the per-sample I-increment
is censored at κ·q90 of |itermErrorRate| (κ = 2, floor 10 °/s), where q90 tracks with
asymmetric leak (up 50 ms, down 450 ms → equilibrium percentile 0.9). Bulk errors integrate
unchanged; tail spikes are rejected.

---

## 7. The Consensus Gate — When May A Take Over?

The gate asks: do the tracker output `b` and the lock-in reference `sinθ` tell the same story?

~~~text
r = EMA(b·sinθ) / √( EMA(sin²θ) · EMA(b²) )
α = soft-knee over floor:  r < 0.3 → 0,  r > 0.9 → ±1
    (slow in: τ = 1 s — evidence must accumulate;
     fast out: τ = 0.4 s — consensus loss must retreat quickly)
~~~

In-phase oscillation yields α → +1, anti-phase α → −1 (the sign is *learned*, not assumed),
quadrature and pure noise yield α = 0. The resonance boost is then replace-blended:

~~~text
boost = legacy · (1 − |α|) + 0.5 · b · α
~~~

(the 0.5 keeps the blend gain-neutral: the lock-in extracts only half the amplitude of a
full-wave rectified projection).

---

## 8. Simulated Testing — What the Numbers Say

Harness: `ruby sim_ferocity.rb harmonize ...` — wing ODE, trapezoidal wave shaper, PID,
throttle chirp driving ω from 2.4 to 7.2 rad/s; 3 s warmup for filter settling.

### 8.1 Order tracker vs. fixed bandpass (triangle throttle chirp)

| Metric | Vold–Kalman | Fixed bandpass | Ratio |
|---|---|---|---|
| Amplitude fidelity (extracted vs. proxy) | — | — | **2.5×** under chirp |
| Phase correlation ρ (vs. shaped wing proxy) | **−0.504** | 0.001 | coherence kept vs. lost |
| Residual RMS | 4.30° | 4.27° | 1.006 (breitband-dominated) |
| Const-ω sanity | — | — | **1.000** (exact baseline) |

The tracker wins where it matters: it *keeps* the flap component under frequency sweep (ρ
intact) while the fixed filter loses it completely. The residual is marginally worse — the
the extractor injects filter ringing into the broadband, which is the honest cost of extraction.

### 8.2 The λ_e(s) finding: raw fails, phase-demodulated discriminates

| Metric | Chirp | Const ω | Ratio |
|---|---|---|---|
| weak-L² of raw residual, VK/fixed | 1.000 | 1.000 | **blind** |
| ‖⟨e⟩_θ‖₂,∞ envelope, VK | 3.260° | 3.166° | — |
| ‖⟨e⟩_θ‖₂,∞ envelope, fixed | 3.219° | 3.166° | **1.013** |

The raw residual is broadband-dominated — tail events hit both filters identically, so raw
λ_e(s) cannot judge the tracker (this falsified the naive design of B). The phase-demodulated
envelope sees exactly what ρ sees, on the error level, with direction physically consistent:
the tracker extracts 2.4× more amplitude but anti-phased (ρ = −0.5), so it slightly *raises*
the synchronous residual until the gate learns the sign. Const-ω sanity: 1.000 exactly.

### 8.3 Consensus gate validation (exact C-math port, 2 kHz, 10 s)

| Scenario | α |
|---|---|
| In-phase | **+0.97** |
| Anti-phase | **−0.97** (sign learned) |
| Quadrature | 0.000 |
| Pure noise | 0.000 |

### 8.4 Commensurability discovery

At ω = 4.8 rad/s, DT = 1 ms: 2π/(ω·DT) = 1308.997 — the near-integer that motivated the
golden-angle strobe (Section 5). Per-sample phase histograms are beat-limited to ~90 s
convergence; the phyllotactic strobe is deterministic from the first reversal.

---

## 9. Ferocity as a Clock Shift — The Phase-Lock Model

The chain above schedules *how much* of the flap-synchronous component to trust. But the
commensurability finding (8.4) exposed a deeper question: what *is* ferocity, physically? The
working thesis — stated before any flight test — is that ferocity is not a force law but a
**local clock shift** (Taktverschiebung). The dwell parks the wing at stroke reversal, which is a
phase-resetting event. The reversal grid itself moves at the free flap rate ω, so the dwell's
parking well does not live in the lab frame but in the **rotating error frame** δ = θ − ωt.

~~~mermaid
flowchart TD
    W["wind η(t)<br/>chaotic detuning"] --> D["phase error δ = θ − ωt"]
    WELL["dwell well −2κ·d·sin(2δ)"] --> D
    D --> S["stable clock → Poincaré + golden-angle samplers"]
    subgraph eq["dδ/dt = η − 2κ·d·sin(2δ)"]
        D
        WELL
    end
~~~

The governing equation, in the rotating frame:

~~~text
dδ/dt = η(t) − 2·κ·d·sin(2δ)
   δ = phase error (pendulum phase vs free-running reversal grid)
   η = wind phase noise (chaotic detuning)
   d = ferocity dwell fraction ∈ [0,1]
   κ = dwell → coupling strength
~~~

`sin(2δ)` has period π — the two reversals per cycle. At d = 0 the equation is a free random
walk: the wind *owns* the clock and δ drifts without bound. At d > 0 the dwell well confines δ
near a reversal: ferocity *owns* the clock.

### 9.1 The correctness trap: sin(2δ), not sin(2θ)

A first implementation coupled `sin(2θ)` in the **lab frame** — and the result inverted the
thesis (dwell made jitter 16× worse). This is not a bug but the physics speaking: a lab-frame
well pins the phase to a *fixed* angle and locks the pendulum, instead of re-anchoring it at the
reversal. The well must be `sin(2δ)` in the error frame — the shift is *relative to the moving
reversal*, exactly the "phase translation of the pendulum system".

### 9.2 Dwell takes over the wind

Harness: `ruby sim_ferocity.rb phaselock` — pendulum phase ω = 4.8 rad/s, κ = 8.0, wind
σ = 0.6 rad/s, 20 s, seeded.

| Dwell d | Phase std δ (rad) | Max \|δ\| (rad) | Wind → lock gain |
|---|---|---|---|
| 0.00 (cos) | 0.1142 | 0.2228 | — (unbounded) |
| 0.05 | 0.0105 | 0.0363 | **10.8×** |
| 0.15 | 0.0060 | 0.0216 | 19.0× |
| 0.30 | 0.0043 | 0.0157 | 26.5× |
| 0.50 | 0.0033 | 0.0129 | 34.2× |
| 0.80 | 0.0026 | 0.0101 | **43.3×** |

The decisive test for "taking over": over increasing horizons, d = 0 lets δ grow without bound
(0.011 → 0.114 → 0.314 rad over 5/20/80 s) while d = 0.3 **saturates** (0.0037 → 0.0043 →
0.0044 rad). The wind owns an unlocked clock; ferocity owns a locked one.

### 9.3 The clock shift itself (limiar translation)

Ferocity asymmetry translates the reversal point `limiar` away from 180°:

| f_down | f_up | limiar (°) | Reversal shift |
|---|---|---|---|
| 0 | 0 | 180.0 | 0° |
| 4 | 0 | 120.0 | −60° |
| 8 | 0 | 0.4 | **−179.6°** |
| 0 | 8 | 359.6 | **+179.6°** |

The local, phase-translational nature: a full asymmetry swing moves the reversal point up to
±179.6° — a clock shift, not a gain change. And its dwell well is what re-anchors the pendulum
phase against the wind's detuning.

### 9.4 The link to commensurability

Wind detunes the flap clock (η), the lab/flap ratio drifts, and per-sample phase coverage
collapses — the "never-converging samples" of 8.4. The dwell re-anchors δ near the reversal grid
and restores a stable clock for the Poincaré and golden-angle samplers. Commensurability is thus
not only a *sampling* problem (solved by phyllotaxis) but also a *clock* problem — and ferocity
is its physical solution.

---

## 10. Firmware Verification Status

| Component | File | Status |
|---|---|---|
| B: λ_e(s) + phase envelope | `src/main/flight/ondas_metrics.c` | ✅ in loop, debug `ONDAS_METRICS` slots 0–3 |
| A: Vold–Kalman tracker | `src/main/flight/ondas_tracker.c` | ✅ in loop, pre-resonance feed |
| Consensus gate | `ondas_metrics.c` | ✅ validated in Ruby before port |
| Resonance replace-blend | `src/main/flight/pid.c` | ✅ α = 0 → legacy exactly |
| Soft-knee amplitude | `pid.c` (getFlappingAmplitude) | ✅ both coupling modes |
| Weak-L¹ I-clamp | `pid.c` (I-branch) | ✅ q90-censored increments |
| Debug logging | `src/main/build/debug.h` | ✅ slots 0–5 (envelope, q90, coverage, b, α) |

Build (TINYFISH): **FLASH 88.77 %, RAM 67.10 %** — clean, HEX produced.

---

## 11. Roadmap

| Step | Feeds From | Status |
|---|---|---|
| D-cutoff adaptation | B raw view q90 — shrink D pass-through when the error drowns in noise | ⏳ next |
| Flight regression of A against B3 | phase envelope as blackbox evidence | ⏳ flight test |
| Full-phase gate (quadrature) | envelope-vs-tracker coherence | ⏳ after regression |

---

## See Also

- [ONDAS](ondas.html) — the stabilization system this chain schedules
- [ONDAS Tuning Guide](../../tutorials/ondas_tuning.html) — practical tuning procedure
- [MSP Protocol](msp.html) — wire format for ONDAS parameters