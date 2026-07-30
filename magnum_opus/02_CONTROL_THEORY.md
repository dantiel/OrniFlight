# 02 — Control Theory: ONDAS, Ferocity & Wing Physics

> **Updated**: Ported from tanh wave shaping to the GralhaAzul trapezoidal model (2026-07-29).

## The Wing Phase ODE

The flapping wing is modeled as a driven harmonic oscillator:

```
θ̈ = k₀ · T_cmd − k₂ · ω

where:
  θ    = wing phase angle (radians, modulo 2π)
  ω    = angular velocity (rad/s)
  k₀   = drive gain (ONDAS_K0 = 1.0)
  k₂   = damping coefficient (ONDAS_K2 = 10.0)
  T_cmd = throttle command (normalized)
```

**Euler integration** (performed each PID iteration at 4-8 kHz):

```
θ(t+dt) = θ(t) + ω(t) · dt
ω(t+dt) = ω(t) + θ̈(t) · dt
```

Where `dt` is the PID loop period (typically 125-250 µs).

### Throttle Command Decomposition

```
T_cmd = (rc_throttle − 480.0) × (1.0 / (0.1 × flap_base_frequency)
        + (flap_speed_modificator − 1500) × 0.000725)
```

- `rc_throttle`: RC channel value (typically 1000-2000)
- `flap_base_frequency`: base flap rate (CLI 0-255, maps to actual flapping frequency)
- `flap_speed_modificator`: rate modifier from control profile (µs offset from 1500)

**⚠️ Known fragility**: When `flap_base_frequency = 0`, `1.0/(0.1×0)` → `+Inf`, cascading through the entire ODE to NaN.

## P-Term Phase Modulation (Channel 1)

When the PID P-term on the pitch axis demands correction, the wing is made to move faster through its current stroke by scaling `k₀`:

```
flappingPhaseModulation = 1.0 + P · ondas_gain · ONDAS_PHASE_SCALE
                        = 1.0 + P · ondas_gain · 0.00005

Clamped to [0.5, 2.0]

Result: k₀_effective = k₀ · flappingPhaseModulation
```

**Physical interpretation**: Higher P term → wing accelerates faster through the current stroke → more thrust sooner. "Push harder now."

At maximum modulation (2.0), the wing drive is doubled — the wing reaches the aerodynamic power phase sooner. At minimum (0.5), the wing slows down, delaying the power stroke.

## D-Term Ferocity Modulation (Channel 2 — "Breathing Pause")

The D-term modulates the *sharpness* of the wave shape — the "breathing pause" depth:

```
flappingFerocityModulation = D · ondas_gain2 · ONDAS_FEROCITY_SCALE
                           = D · ondas_gain2 · 0.0003

Clamped to [−0.5, +0.5]

Applied as: dFactor = 1.0 + dMod
  fDown_effective = fDown_base × dFactor
  fUp_effective   = fUp_base   × dFactor
```

**Physical interpretation**: Higher D (velocity opposing change) → both strokes become sharper → more dwell at endpoints → "delay the next opposite stroke." This acts like aerodynamic braking — the wing pauses longer at the reversal point, reducing the next stroke's impulse.

Negative D (accelerating motion) → softer wave → less dwell → faster stroke transitions.

## I-Term Asymmetry Modulation (Channel 3)

The I-term introduces a persistent up/down bias:

```
flappingAsymmetryBias = I · ondas_gain3 · ONDAS_ASYMMETRY_SCALE
                      = I · ondas_gain3 · 0.0001

Clamped to [−3.0, +3.0]

Applied as:
  fDown_effective = fDown_base − iBias
  fUp_effective   = fUp_base   + iBias
```

**Physical interpretation**: Persistent pitch error integrates into an asymmetry bias. Positive bias → stronger upstroke, weaker downstroke → nose-down pitching moment. This corrects for sustained aerodynamic imbalances (CG offset, wing twist asymmetry, manufacturing tolerances).

## Ferocity Wave Shaping — Trapezoidal Model

The wave shape is produced by a trapezoidal model with explicit dwell zones connected by a cosine ramp. Ported from the GralhaAzul `formaDoBaterDasAsas()` algorithm. This replaces the old tanh(F·sinθ)/tanh(F) approach.

### Parameters

- **Ferocity f ∈ [0, 8]**: `f = 0` → pure cosine (no dwell), `f = 8` → pure square wave
- **Dwell ratio d = f/8**: fraction of each half-stroke spent held at the extremum
- **Half-dwell dh = d/2**: dwell duration at each extreme of a half-stroke
- **Shared limiar**: the θ-value (in [0, 2π)) where the downstroke→upstroke reversal occurs. Computed from **raw** config ferocities (before PID modulation) to keep the reversal point stable:

```
w_down  = 8 − fDown_raw    (softness of downstroke)
w_up    = 8 − fUp_raw      (softness of upstroke)
limiar  = 2π · w_down / (w_down + w_up)
```

### Shape Construction

Within each half-cycle, parameter `t ∈ [0, 1]` is the normalized position:

```
Downstroke (θ < limiar):  t = θ / limiar
Upstroke   (θ ≥ limiar):  t = (θ − limiar) / (2π − limiar)
```

The shaped value follows three zones:

```
Zone 1: t ∈ [0, dh]              → output = ±1    (initial dwell at stroke peak)
Zone 2: t ∈ [dh, 1−dh]           → output = ±cos(π·(t−dh)/(1−d))   (cos ramp)
Zone 3: t ∈ [1−dh, 1]            → output = ∓1    (final dwell at opposite peak)
```

The sign (+1/−1) depends on whether it's a downstroke or upstroke. For downstroke: starts at +1 (bottom), ramps to −1 (top). For upstroke: starts at −1, ramps to +1.

### Derivative (for aeroelastic PID scaling)

```
d(shapedWave)/dθ = 0                                         in dwell zones
                 = ∓k · sin(k·(t−dh)) · dt/dθ               in ramp zone

where k = π/(1−d),  dt/dθ = 1/limiar (down) or 1/(2π−limiar) (up)
```

Then `flappingDerivative = d(shapedWave)/dθ · ω` for the time derivative used by aeroelastic gain scaling.

### Visual Comparison

| f | d (dwell%) | Waveform |
|---|------------|----------|
| 0 | 0% | Pure cosine — smooth sinusoidal flapping |
| 2 | 25% | Subtle dwell at extremes, soft transition |
| 4 | 50% | Equal dwell/ramp — pronounced breathing pause |
| 6 | 75% | Dominant dwell, short snappy transitions |
| 8 | 100% | Pure square wave — instant reversal, maximum thrust |

**Key insight**: Unlike the old tanh model which smoothly compressed a sine wave, the trapezoidal model gives **independent control** over dwell duration vs. ramp steepness. The "breathing pause" is now an explicit, tunable parameter rather than an emergent property of tanh saturation.

## ONDAS Gate: Phase-Gated PID Authority

> **Removed**. The old ONDAS gate (`ondasAttenuation = −|shapedWave| + 0.5`) was replaced by the three-channel breathing-pause architecture. PID terms now modulate wing trajectory parameters directly rather than gating servo authority through a window function. The ferocity waveform itself creates the "gate" — dwell zones at stroke extremes naturally suppress aerodynamic authority while the cos ramp provides a smooth transition to the power phase.

## SSFF: Stroke-Synchronous Feed-Forward

The PID loop fights the same flap-frequency error pattern every cycle. SSFF learns and pre-compensates:

```
1. ACCUMULATE: Sum pitch errorRate over each half-stroke
2. DETECT: sinθ changes sign → half-stroke boundary
3. COMPUTE: mean_error = ΣerrorRate / count
4. BIAS: Next half-stroke ferocity += ssff_gain × 0.001 × mean_error

Downstroke completed, mean pitch error > 0 (nose drifting up)
  → Increase UPSTROKE ferocity → stronger nose-down thrust
Upstroke completed, mean pitch error < 0 (nose drifting down)
  → Increase DOWNSTROKE ferocity → stronger nose-up thrust
```

SSFF eliminates the phase lag inherent in PID-only control at the flap frequency (~12 Hz). The PID only handles residuals — not the repetitive battle.

## Aeroelastic PID Scaling

Flapping aerodynamics cause the effective control authority to vary with wing velocity. The shaped derivative provides velocity-dependent scaling:

```
flappingDerivative = d(shapedWave)/dθ · ω
                   = 0                                          (dwell zones)
                   = ∓k · sin(k·(t−dh)) · dt/dθ · ω            (ramp zone)

where k = π/(1−d) and ω is the wing angular velocity from the ODE.

Aeroelastic scaling applied to PID gains:
  Kp_effective = Kp × (1.0 + aerolastic_Kp_scaling × flappingDerivative)
  Ki_effective = Ki × (1.0 + aerolastic_Ki_scaling × flappingDerivative)
  Kd_effective = Kd × (1.0 + aerolastic_Kd_scaling × flappingDerivative)
```

Default coefficients: `aeroelastic_Kp=0.01`, `Ki=0.005`, `Kd=-0.005`. This compensates for varying aerodynamic authority through the stroke — PID is more aggressive when the wing has less authority (stroke reversal/dwell) and less aggressive when authority is high (mid-ramp). During dwell zones, `flappingDerivative = 0` so no scaling is applied — the wing is at the aerodynamic extreme and PID operates at nominal gains.

## Glide Mode

When throttle drops below `GLIDE_MODE_THRESHOLD` (1040 µs):

```
if (rc_throttle > GLIDE_MODE_THRESHOLD):
    // Normal flapping — ODE + ferocity + ONDAS all active
    flappingSinusoid = sin(theta)
    ornithopterFlapping = shapedWave × amplitude
else:
    // Glide mode — all flapping outputs zeroed
    shapedFlappingSinusoid = 0.0
    flappingDerivative = 0.0
    ornithopterFlapping = 0.0
```

The wing ODE continues running but its output is zeroed. Servos can be configured to hold glide position via `ornithopter_glide_deg` parameter.