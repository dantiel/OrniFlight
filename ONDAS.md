## ONDAS: The Wave — Flapping Wing Control Architecture

Three control layers operating at different timescales, unified through the flapping phase θ. ONDAS is the umbrella; the channels beneath it are **Cadence**, **Ferocity**, and **Balance**.

> **Updated 2026-07-30**: Channels renamed from `ondas_gain[1-3]`. PD blend on Ferocity. Added **Warp** — roll/yaw ferocity differential. Dual wave shaping (left/right wings).

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
                    │                           │
              ┌─────▼─────┐              ┌──────▼──────┐
              │   WARP    │              │  WARP YAW   │
              │ roll diff │              │ yaw diff    │
              └───────────┘              └─────────────┘
```

### The Three Primaries

| Channel | Feeds From | Modulates | Scale | Effect |
|---------|-----------|-----------|-------|--------|
| **Cadence** | P only | k₀ (ODE spring) | `cadence_gain × 0.00005` | "Push harder now" — shifts thrust timing within stroke |
| **Ferocity** | PD blend | Dwell ratio d | `ferocity_p_gain × 0.00015` + `ferocity_d_gain × 0.0003` | "How abruptly" — wave sharpness via PD blend |
| **Balance** | I only | Up/down bias | `balance_gain × 0.0001` | "Trim the list" — persistent thrust asymmetry |

### Ferocity PD Blend

Ferocity controls how much inertia transfers from wing to airframe. A sharper wave (high ferocity) delivers more impulse per stroke; a smoother wave (low ferocity) lets the wing glide through.

The PD blend lets the pilot decide the character:

```
ferocity_modulation = constrain(ferocity_P + ferocity_D, −0.5, +0.5)

ferocity_P = P · ferocity_p_gain · FEROCITY_P_SCALE   // "I'm off by X → push X harder"
ferocity_D = D · ferocity_d_gain · FEROCITY_D_SCALE   // "I'm accelerating → dampen"
```

- Set `ferocity_p_gain = 0` for pure D→ferocity (original behavior)
- Set `ferocity_d_gain = 0` for pure P→ferocity
- Use both for blended response

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

Derivative is piecewise: 0 in dwell zones, `∓k·sin(k·(t−dh))·dt/dθ` in ramp zone where `k = π/(1−d)`.

### Layer 2: WARP — Roll/Yaw Ferocity Differential

Ferocity is the ornithopter's control surface. Differential wave sharpness between left and right wings creates roll torque — sharper right wing = more right-side thrust = roll left. No ailerons needed.

```
Left wing:  base_ferocity + roll_differential − yaw_differential
Right wing: base_ferocity − roll_differential + yaw_differential

roll_differential = roll_P · warp_gain · WARP_SCALE
yaw_differential  = yaw_P  · warp_yaw_gain · WARP_SCALE
```

The same theta feeds both wings; only the dwell ratio differs. The shared limiar (computed from raw config ferocities) keeps stroke reversal synchronized.

### Layer 3: SSFF — Stroke-Synchronous Feed-Forward

The PID loop fights the same flap-frequency error pattern every cycle. SSFF learns it:

1. **Accumulate** pitch errorRate over each half-stroke
2. **At zero crossing** (sinθ changes sign): compute mean error, bias next half-stroke's ferocity
3. **Next stroke** uses biased ferocity: `F_effective = F_base + K_ff · mean_error`

```
Downstroke completed, mean pitch error > 0 (nose drifting up)
  → Increase upstroke ferocity → stronger nose-down thrust next upstroke
Upstroke completed, mean pitch error < 0 (nose drifting down)
  → Increase downstroke ferocity → stronger nose-up thrust next downstroke
```

### CLI Parameters

| Parameter | Range | Default | Description |
|-----------|-------|---------|-------------|
| `ornithopter_ferocity_downstroke` | 1–100 | 12 | Base ferocity on downstroke (maps to f∈[0,8]) |
| `ornithopter_ferocity_upstroke` | 1–100 | 12 | Base ferocity on upstroke (maps to f∈[0,8]) |
| `ssff_gain` | 0–100 | 0 | SSFF gain (0=off, start with 20-40) |
| `cadence_gain` | −100–100 | 20 | P→phase advance (k₀ scaling) |
| `ferocity_p_gain` | 0–100 | 10 | P→ferocity — proportional push |
| `ferocity_d_gain` | −100–100 | 20 | D→ferocity — damping |
| `balance_gain` | −100–100 | 10 | I→thrust symmetry (up/down bias) |
| `warp_gain` | −100–100 | 0 | Roll P→L/R ferocity differential |
| `warp_yaw_gain` | −100–100 | 0 | Yaw P→fore/aft ferocity differential |

### New Frontiers (Roadmap)

| Concept | What It Does | Status |
|---------|-------------|--------|
| **Warp** | Roll/yaw ferocity differential | ✅ Implemented |
| **Anchor** | Variable k₂ damping — tighter/looser frequency lock | Planned |
| **Resonance** | Phase-locked error filter — only in-phase corrections pass | Planned |
| **Prescience** | Stroke-ahead prediction — pre-compute modulation for next reversal | Planned |
| **Espelho** | Wing-self-noise cancellation — subtract wing-coupled gyro signal | Planned |
| **Saudade** | Per-stroke online learning — optimal cadence/ferocity/balance per condition | Planned |

### Simulation

`ruby sim_ferocity.rb prize [F_down] [F_up]` — velocity-based physics demo
`ruby sim_ferocity.rb compare [F_down] [F_up]` — fixed vs SSFF comparison
