# ONDAS — Oscillating Normalized Dynamic Adaptive Stabilization

## The Core Principle

A fixed-wing or conventional aircraft generates control forces **continuously** — a control surface deflection or RPM change produces a steady-state moment. An ornithopter does not. Every gram of thrust, every Newton of torque, is **phase-bound** within the wingbeat cycle. The same force impulse applied at different points in the stroke produces fundamentally different results.

ONDAS acknowledges this reality and modulates stabilization effort synchronously with the flapping cycle.

---

## Cadence — The Timing Brain

Cadence is the most critical ONDAS filter because it determines **when** correction happens within each wingbeat.

| Stroke Phase | Effect of Force Application |
|---|---|
| Downstroke center | Maximum lift, roll authority |
| Downstroke end (braking) | Induced drag → yaw moment |
| Upstroke center | Thrust rearward, pitch-up |
| Upstroke end | Wing reversal, minimal effect |

**Cadence shifts the modulation window** to align with the phase where the aerodynamic lever arm is longest. Wrong cadence = fighting wing physics. Correct cadence = every milliwatt becomes control authority.

### Parameters

| Parameter | Value | Function |
|-----------|-------|----------|
| `ONDAS_K0` | 1.0 | Base phase offset |
| `ONDAS_K2` | 10.0 | Phase spread / sharpness |
| `ONDAS_PHASE_SCALE` | 0.00005 | Small factor, large leverage |

---

## Ferocity P — Immediate Asymmetric Thrust

Ferocity P increases the **waveform squareness** (trapezoidal shaping: dwell at ±1, cosine ramp between) proportionally to the current PID error.

- More thrust on one side → immediate moment
- The braked wing at stroke-end experiences **induced drag** — this is the counter-moment
- Effect: direct, proportional, immediate

---

## Ferocity D — Anticipatory Drag Exploitation

Ferocity D completes the picture. Where P provides thrust asymmetry, D leverages the **drag of the contralateral wing** as a brake.

- Reads error rate of change and **anticipates**
- Can deliberately exploit the drag of a slowed wing for yaw/pitch moments
- P+D together create a **differential moment pair** — thrust on side A, drag on side B — more efficient than thrust-only

---

## Three Ways Cadence/Ferocity D Increases Ferocity

### 1. Direct — D boosts P during rapid error change

In gusts or aggressive maneuvers, `error_rate` is large. D multiplies this and adds to base ferocity. The wing becomes *sharper* (more trapezoidal) because P+D together demand more squareness than P alone. Result: maximum authority precisely when critical.

### 2. Indirect — Cadence shifts the leverage point

Cadence modulates *when* in the cycle ferocity acts. Moving the window into a more aerodynamically sensitive phase (e.g., downstroke center vs. upstroke end) means the **same ferocity value** produces more effect — effectively amplification without numerical change.

### 3. Combinatorial — D × Cadence during stall recovery

In a stall: high sink rate → D detects the rate → increases ferocity. Simultaneously, cadence shifts modulation into the downstroke phase where the wing has maximum bite. The interplay: D provides the force, cadence the right moment. Without cadence, D-force arrives at the wrong phase and dissipates uselessly.

---

## Additional ONDAS Parameters

| Parameter | Function |
|-----------|----------|
| **Balance** | Up/down thrust symmetry — I-term bias between upstroke and downstroke. Compensates for wing asymmetry, manufacturing tolerances, and wear |
| **Warp** | Roll/Yaw P → L/R ferocity differential — right and left wings flap independently on the roll axis for bank and turn maneuvers |
| **Anchor** | Phase anchoring — locks modulation to a specific phase reference, resisting drift |
| **Resonance** | Airframe resonance compensation — avoids exciting structural modes of the airframe |

---

## The New Generation: Statistical Envelope and Order Tracker

The eight layers above are the **oscillator domain** — they modulate the wingbeat. Around them,
two measurement modules now form the **statistical envelope** that schedules the layers and
adapts them online:

~~~mermaid
flowchart LR
    e["Attitude error"] --> M["ondas_metrics<br/>λ_e(s) · q90 · weak-L²<br/>phase envelope"]
    e --> T["ondas_tracker<br/>Vold–Kalman, follows ω(t)"]
    T -->|"b"| G["Consensus gate<br/>r vs. lock-in sinθ"]
    G -->|"α ∈ [−1,+1]"| R["Resonance replace-blend"]
    M -->|"q90"| W["Anti-windup I-clamp"]
    M -.->|"q90 (roadmap)"| D["D-cutoff adaptation"]
~~~

- **ondas_metrics (B)** — a 32-bin survival-function histogram of |error| per axis
  (λ_e(s), log-spaced, exponential leak τ ≈ 1 s) providing q90, the weak-L² tail norm and the
  tail mass; plus a 16-bin **Poincaré phase envelope** sampled at stroke reversals with a
  golden-angle rotation — the synchronous residual, logged to Blackbox.
- **ondas_tracker (A)** — a Vold–Kalman order tracker: a 2nd-order resonator (ζ = 0.06,
  Q ≈ 8.3) whose coefficients follow the instantaneous wingbeat frequency per sample, so it
  keeps extracting the flap-synchronous error component under throttle sweeps where fixed
  filters detune. Feed is pre-resonance (open loop — it never sees its own contribution).
- **Consensus gate** — the tracker may take over the resonance boost only when it and the
  independent lock-in reference agree: correlation r = EMA(b·sinθ)/√(EMA(sin²θ)·EMA(b²)) with
  a soft-knee over r = 0.3, slow in / fast out. At α = 0 the legacy resonance path is restored
  **exactly**.
- **Substrate** — the flapping amplitude uses a Marcinkiewicz-consistent geometric soft-knee
  (no authority kink), and the I-branch is anti-windup censored at κ·q90 so BALANCE and
  SAUDADE never absorb gust spikes as learned trim.

Full mathematics, simulated testing and build verification: see the development article below.

---

## Analogy

**Cadence is the conductor. Ferocity P and D are the instruments.**

Without a conductor, they play — but not together. With one, noise becomes music.

---

## See Also

- [ONDAS Development — Mathematical Methods and Simulated Testing](ondas_development.html) — the envelope/tracker generation
- [ONDAS Tuning Guide](../../tutorials/ondas_tuning.html) — practical tuning procedure
- [MSP Protocol](msp.html) — wire format for ONDAS parameters
- [Flight Profiles](profiles.html) — profile-aware ONDAS configuration