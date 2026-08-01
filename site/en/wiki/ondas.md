# ONDAS Theory

> *Oscillating Normalized Dynamic Adaptive Stabilization — phase-aware control for flapping-wing flight.*

## Why ONDAS Exists

Quadcopter PIDs assume **continuous, isotropic thrust**. A motor spins, thrust is produced, and it's the same regardless of *when* you measure it. This assumption is baked into every Betaflight/PX4/ArduPilot PID loop.

**Ornithopters violate this assumption.** Thrust is produced **phasically** — only during the power stroke. The same corrective impulse applied at different points in the stroke cycle produces *drastically* different aerodynamic moments:

| Phase | Effect of Additional Thrust |
|-------|---------------------------|
| **Downstroke centre** | Maximum lift, roll authority |
| **Downstroke end (braking)** | Induced drag → yaw moment |
| **Upstroke centre** | Rearward thrust, pitch-up |
| **Upstroke end (reversal)** | Minimal aerodynamic coupling |

A conventional PID fighting a roll disturbance might apply correction during the upstroke — where it has almost no leverage — then overshoot when the downstroke arrives and suddenly the same gain has 5× the authority. The result: oscillation, inefficiency, and pilot frustration.

**ONDAS solves this by making every control parameter phase-aware.**

## The 10 Parameters

### 1. Cadence Gain — The Timing Brain

Cadence shifts the modulation window along the stroke cycle. It answers: *when* should correction happen?

- **Low cadence** (0–30): Modulation peaks during downstroke — maximum authority, aggressive response
- **Mid cadence** (30–70): Balanced distribution — good general-purpose
- **High cadence** (70–100): Modulation peaks during upstroke — subtle, efficiency-focused

Cadence is governed by `k0=1.0`, `k2=10.0`, and `phase_scale=0.00005` — tiny numbers with enormous leverage. A change of 5 units in cadence_gain can shift the modulation window by 30° of stroke phase.

### 2. Ferocity — Wave Shape from Sine to Square

Ferocity controls how "aggressive" each stroke is. At low values, the waveform is sinusoidal — smooth, efficient, quiet. At high values, it becomes trapezoidal — sharp dwell at the extremes, maximum instantaneous thrust.

**Ferocity P** (proportional): Immediate asymmetric thrust. Roll error? One wing gets harder, the other softer. The braked wing produces induced drag — this is the counter-moment.

**Ferocity D** (derivative): Anticipates error rate. If the craft is *accelerating* into a roll, D pushes ferocity *before* the error peaks. It completes P's picture by using the drag of the slowed wing as a precision brake.

**P+D together** form a differential moment pair: thrust on one side, drag on the other. More efficient than thrust alone.

| Ferocity | Waveform | Effect |
|----------|---------|--------|
| 0–20 | Near-sinusoidal | Smooth, efficient, low peak force |
| 30–60 | Transitional | Progressive authority increase |
| 70–100 | Near-trapezoidal | Maximum authority, sharp dwell |

### 3. Asymmetry (Balance Gain)

Shifts the modulation bias towards upstroke or downstroke. Positive balance favours downstroke authority (lift-biased), negative favours upstroke (pitch-biased). Signed value, stored wire as `val+128`.

### 4. Warp Gain

Temporal stretching/shrinking of the modulation window. High warp concentrates the correction into a narrower phase window — more "punch" but less tolerance for timing error. Low warp spreads correction more evenly.

### 5. Anchor Gain

Baseline coupling strength. Like a "dry/wet" mix between raw PID output and ONDAS-modulated output. At 0, only ONDAS modulation reaches the servo. At 100, the raw PID signal passes through unmodulated.

### 6. Resonance Gain

Resonant feedback — how much the previous cycle's residual energy feeds into the next. High resonance creates a "ringing" effect useful for sustained oscillations like hovering. Low resonance is cleaner for forward flight.

### 7. Prescience Gain (Phase 2)

Predictive phase offset — shifts modulation *ahead* of the current phase to compensate for servo latency and aerodynamic lag.

### 8. Espelho Gain (Phase 2)

Mirror/twin-wing coupling. When the left wing modulates, how much does the right wing *counter-modulate*? High espelho creates tight differential pairs for crisp roll response.

### 9. Saudade Gain (Phase 2)

Hysteresis/memory — carries a decaying trace of the previous stroke's modulation into the current one. The wing remembers its past.

### 10. SSFF Gain (Phase 2)

Stroke-Synchronized Feed-Forward. A direct, phase-locked injection of gyro rate into the waveform — bypasses the PID loop entirely for the fastest possible response.

## Cadence + Ferocity D: The Hidden Synergy

**Cadence decides *when* force is applied. Ferocity D decides *how much force* based on error rate.**

When the ornithopter enters a stall:
1. High sink rate → D detects rapid altitude change
2. D increases ferocity → harder strokes
3. Cadence shifts the window to downstroke → maximum aerodynamic bite
4. Result: stall recovery faster than P-only because D *saw it coming* and Cadence *placed the force correctly*

## Tuning Philosophy

ONDAS tuning is *not* PID tuning. The order matters:

1. **First: Cadence.** Find the phase window where your airframe has the most aerodynamic leverage.
2. **Second: Ferocity P.** Increase until you feel crisp response without oscillation.
3. **Third: Ferocity D.** Bring in D to dampen P-induced ringing.
4. **Fourth: Asymmetry & Warp.** Fine-tune for your specific airframe's stroke geometry.
5. **Last: Phase 2 gains.** Only tune when the base 6 are solid.

## The ONDAS Promise

A properly tuned ONDAS system doesn't feel like a PID controller. It feels like the aircraft *wants* to fly straight. The best control system is the one you forget is there.

---

*OrniFlight — Fly Natural. Control Precise.*
