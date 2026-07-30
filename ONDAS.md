## ONDAS: The Wave — Flapping Wing Control Architecture

Three control layers operating at different timescales, unified through the flapping phase θ. ONDAS is the umbrella; the channels beneath it are **Cadence**, **Ferocity**, and **Balance**.

> **Updated 2026-07-30**: Channels renamed from `ondas_gain[1-3]`. PD blend on Ferocity. Added **Warp** (roll/yaw ferocity differential), **Anchor** (variable k₂ damping), **Resonance** (phase-locked error filter), and **per-axis ferocity** (roll/yaw common-mode contributions).

### Architecture Overview

```
                        ┌──────────────────────────────────────┐
                        │           WING ODE                   │
                        │   θ̈ = k₀·T_cmd − k₂·ω               │
                        │   θ → sin(θ) → trapezoidal shaper    │
                        └──────────┬───────────────────────────┘
                                   │
        ┌──────────────────────────┼──────────────────────────┐
        │                          │                          │
   ┌────▼─────┐            ┌──────▼──────┐           ┌───────▼──────┐
   │ CADENCE  │            │  FEROCITY   │           │   BALANCE    │
   │ P→k₀     │            │ PD→dwell    │           │   I→bias     │
   │ phase    │            │ sharpness   │           │   symmetry   │
   └──────────┘            └──────┬──────┘           └──────────────┘
                                  │
                    ┌─────────────┼─────────────┐
                    │             │             │
              ┌─────▼─────┐ ┌────▼────┐  ┌──────▼──────┐
              │   WARP    │ │ ROLL P │  │   YAW P     │
              │ roll diff │ │common  │  │  common     │
              └───────────┘ └────────┘  └─────────────┘
```

### The Three Primaries

| Channel | Feeds From | Modulates | Scale | Effect |
|---------|-----------|-----------|-------|--------|
| **Cadence** | P only | k₀ (ODE spring) | `cadence_gain × 0.00005` | "Push harder now" — shifts thrust timing within stroke |
| **Ferocity** | PD blend + roll P + yaw P | Dwell ratio d | `ferocity_p_gain × 0.00015` + `ferocity_d_gain × 0.0003` | "How abruptly" — wave sharpness, per-axis inertia gate |
| **Balance** | I only | Up/down bias | `balance_gain × 0.0001` | "Trim the list" — persistent thrust asymmetry |

### Ferocity: The Inertia Gate

Ferocity controls how much inertia transfers from wing to airframe. A sharper wave (high ferocity) delivers more impulse per stroke; a smoother wave (low ferocity) lets the wing glide through. **Each axis contributes independently** — ferocity is the gate through which each axis's correction passes from wing motion to airframe response.

```
ferocity_modulation = clamp(pitch_PD + roll_P + yaw_P, −0.5, +0.5)

pitch_PD = clamp(P·ferocity_p_gain·P_SCALE + D·ferocity_d_gain·D_SCALE, −0.35, +0.35)
roll_P   = clamp(P·ferocity_roll_gain·P_SCALE, −0.15, +0.15)   [NEW]
yaw_P    = clamp(P·ferocity_yaw_gain·P_SCALE, −0.15, +0.15)    [NEW]
```

- Set `ferocity_p_gain = 0` for pure D→ferocity
- Set `ferocity_d_gain = 0` for pure P→ferocity
- Set `ferocity_roll_gain / ferocity_yaw_gain = 0` (default) to isolate pitch-only ferocity

### Layer 1: Ferocity — Trapezoidal Wave Shaping

```
shapedWave(θ) = ±1                                   (dwell zones, t ∈ [0, dh] ∪ [1−dh, 1])
              = ±cos(π·(t−dh)/(1−d))                 (cos ramp, t ∈ [dh, 1−dh])

where:
  f ∈ [0, 8]         ferocity
  d = f/8            dwell ratio ∈ [0, 1]
  dh = d/2           half-dwell per extreme
  t ∈ [0, 1]         normalized position within half-stroke
```

- **f=0**: Pure cosine — no dwell, smooth sinusoidal flapping
- **f=4**: 50% dwell — pronounced breathing pause at extremes
- **f=8**: Pure square wave — instant reversal, maximum thrust

### Layer 2: WARP — Roll/Yaw Ferocity Differential

Ferocity is the ornithopter's control surface. Differential wave sharpness between left and right wings creates roll torque; fore/aft differential creates yaw.

```
Left wing:  base_ferocity + roll_differential − yaw_differential
Right wing: base_ferocity − roll_differential + yaw_differential

roll_differential = roll_P · warp_gain · WARP_SCALE
yaw_differential  = yaw_P  · warp_yaw_gain · WARP_SCALE
```

The same theta feeds both wings; only the dwell ratio differs. Shared limiar keeps stroke reversal synchronized.

### Layer 3: SSFF — Stroke-Synchronous Feed-Forward

The PID loop fights the same flap-frequency error pattern every cycle. SSFF learns it:

1. **Accumulate** pitch errorRate over each half-stroke
2. **At zero crossing**: compute mean error, bias next half-stroke's ferocity
3. **Next stroke** uses biased ferocity

### Layer 4: Resonance — Phase-Locked Error Filter 🔮

A lock-in amplifier for attitude error. Multiplies error by sin(θ), leaky-integrates to extract the flap-coherent component, then amplifies it. Errors that beat WITH the wing get a resonance boost; errors at other frequencies pass through unchanged. This is signal *enhancement*, not noise rejection — the wing "resonates" with corrections at its own rhythm.

```
modulated = error · sin(θ)
lockInState += (modulated − lockInState) · dT / τ   (τ = 0.15s, ~1.5 flap periods)
resonance_boost = lockInState · sin(θ) · gain
effective_error = error + resonance_boost
```

Applied to I-term error on PITCH axis before SSFF and ONDAS modulation.

### Layer 5: Prescience — Stroke-Ahead Prediction 🔮

Eliminates SSFF's half-stroke measurement delay. At every PID iteration, uses wing ODE state (ω) to predict error at the next reversal: `error_future = errorRate · π/|ω|`. When `prescience_gain ≠ 0`, this predicted error is blended with SSFF's accumulated mean error at each half-stroke boundary.

- `prescience_gain = 0`: SSFF only (default, learned correction)
- `prescience_gain > 0`: predicted + learned blended — faster response to transients
- `prescience_gain > 0, ssff_gain = 0`: pure prediction — no learning, minimal delay

```
dt_to_reversal = π / |ω|
predictedError = errorRate · dt_to_reversal
prescience_bias = prescience_gain · 0.001 · predictedError

total_bias = ssff_bias + prescience_bias   (at each half-stroke boundary)
```

### Layer 6: Espelho — Wing-Self-Noise Cancellation 🪞

Resonance's inverse sibling. A reverse lock-in amplifier that learns the gyro component phase-coherent with flapping and *subtracts* it. The wing's mechanical motion couples into the gyro — Espelho removes this "self-image," leaving only external disturbances and actual attitude response. Where Resonance amplifies the coherent signal, Espelho cancels it.

```
modulated = gyro · sin(θ)
espelhoState[axis] += (modulated − espelhoState) · dT / τ    (τ = 0.4s)
gyro_self = gain · espelhoState · sin(θ)
gyro_clean = gyro_raw − gyro_self
```

Applied to all three axes before error computation. `espelho_gain = 0` (default) disables it.

### Layer 7: Anchor — Variable k₂ Damping ⚓

Controls the wing ODE's frequency lock strength. Higher k₂ means the wing snaps to commanded frequency faster (agile, energy-hungry). Lower k₂ lets the wing resonate freely (efficient cruise, sluggish transients).

```
k₂ = ANCHOR_BASE_K2 + anchor_gain · ANCHOR_SCALE
   = 10.0 + anchor_gain · 0.1
```

`anchor_gain = 0` → k₂ = 10.0 (default tight lock)
`anchor_gain = 100` → k₂ = 20.0 (ultra-tight, high energy cost)

### CLI Parameters

| Parameter | Range | Default | Description |
|-----------|-------|---------|-------------|
| `ornithopter_ferocity_downstroke` | 1–100 | 12 | Base ferocity on downstroke (maps to f∈[0,8]) |
| `ornithopter_ferocity_upstroke` | 1–100 | 12 | Base ferocity on upstroke (maps to f∈[0,8]) |
| `ssff_gain` | 0–100 | 0 | SSFF gain (0=off) |
| `cadence_gain` | −100–100 | 20 | P→phase advance (k₀ scaling) |
| `ferocity_p_gain` | 0–100 | 10 | P→ferocity — proportional push |
| `ferocity_d_gain` | −100–100 | 20 | D→ferocity — damping |
| `ferocity_roll_gain` | 0–100 | 0 | Roll P→common-mode ferocity |
| `ferocity_yaw_gain` | 0–100 | 0 | Yaw P→common-mode ferocity |
| `balance_gain` | −100–100 | 10 | I→thrust symmetry (up/down bias) |
| `warp_gain` | −100–100 | 0 | Roll P→L/R ferocity differential |
| `warp_yaw_gain` | −100–100 | 0 | Yaw P→fore/aft ferocity differential |
| `anchor_gain` | 0–100 | 0 | k₂ damping: frequency lock strength |
| `resonance_gain` | 0–100 | 0 | Phase-locked error filter (0=off) |
| `prescience_gain` | 0–100 | 0 | Stroke-ahead prediction (0=off, blends with ssff_gain) |
| `espelho_gain` | 0–100 | 0 | Wing-self-noise cancellation (0=off) |

### New Frontiers (Roadmap)

| Concept | What It Does | Status |
|---------|-------------|--------|
| **Warp** | Roll/yaw ferocity differential | ✅ Implemented |
| **Anchor** | Variable k₂ damping — tighter/looser frequency lock | ✅ Implemented |
| **Resonance** | Phase-locked error filter — amplify flap-coherent corrections | ✅ Implemented |
| **Per-axis Ferocity** | Roll/Yaw P→common-mode ferocity — inertia gate per axis | ✅ Implemented |
| **Prescience** | Stroke-ahead prediction — pre-compute modulation for next reversal | ✅ Implemented |
| **Espelho** | Wing-self-noise cancellation — subtract wing-coupled gyro signal | ✅ Implemented |
| **Saudade** | Per-stroke online learning — optimal cadence/ferocity/balance per condition | 🔜 Next |

### Simulation

`ruby sim_ferocity.rb prize [F_down] [F_up]` — velocity-based physics demo
`ruby sim_ferocity.rb compare [F_down] [F_up]` — fixed vs SSFF comparison