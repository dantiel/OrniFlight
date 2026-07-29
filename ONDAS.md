## ONDAS + Ferocity + SSFF: Unified Three-Layer Flapping Stabilization

Three control layers operating at different timescales, unified through the flapping phase θ.

### The Three Layers

| Layer | Timescale | Mechanism | What It Does |
|-------|-----------|-----------|--------------|
| **Ferocity** | Instantaneous | `tanh(F·sinθ)/tanh(F)` | Shapes wing velocity at any phase — higher F = wing snaps earlier, harder |
| **ONDAS** | Intra-stroke (~1 ms) | `−\|shapedWave\| + 0.5` | Gates PID authority to the aerodynamic power phase |
| **SSFF** | Stroke boundary (~40 ms) | Per-half-stroke error integration | Biases next stroke's ferocity to cancel repetitive flap-frequency error |

### Layer 1: Ferocity — Instantaneous Velocity Amplifier

```
shapedWave(θ) = tanh(F · sinθ) / tanh(F)      F ∈ [1.0, 8.0]

d(shapedWave)/dt = F·sech²(F·sinθ)·cosθ·ω / tanh(F)
                   └───────────┬───────────┘
                     velocity gain factor
```

At θ=6° (stroke start) with ω=30 rad/s:
- F=1.0: wing velocity = 38 rad/s
- F=4.0: wing velocity = 90 rad/s (2.4×)
- F=8.0: wing velocity = 89 rad/s (2.3×)

**Thrust ∝ velocity²** — ferocity gives nonlinear force boost at stroke start. At mid-stroke the wing is already near extreme → velocity drops. Ferocity shifts force to the **beginning** of the stroke where it matters most.

### Layer 2: ONDAS — Phase-Gated PID Authority

```
ondasAttenuation = −|shapedWave| + 0.5        range [−0.5, +0.5]
```

| shapedWave | Phase | Attenuation | PID Effect |
|-----------|-------|-------------|------------|
| ≈ 0 | Midstroke | +0.5 | Amplified |
| ≈ ±1 | Stroke reversal | −0.5 | Suppressed |

Higher ferocity automatically sharpens the ONDAS window — the shaped wave saturates faster, so the transition from "gate open" to "gate closed" is tighter. **No separate tuning required.**

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

This eliminates the **phase lag** inherent in PID-only control at the flap frequency. The PID only handles residuals — not the repetitive 12 Hz battle.

### Asymmetric Ferocity for Pitch Authority

- **Higher downstroke ferocity** → wing snaps harder on downstroke → stronger pitch-up impulse
- **Higher upstroke ferocity** → wing snaps harder on upstroke → stronger pitch-down impulse

SSFF modulates this asymmetry stroke-by-stroke based on measured pitch error.

### CLI Parameters

| Parameter | Range | Default | Description |
|-----------|-------|---------|-------------|
| `ornithopter_ferocity_downstroke` | 1–100 | 12 | Base ferocity on downstroke |
| `ornithopter_ferocity_upstroke` | 1–100 | 12 | Base ferocity on upstroke |
| `ssff_gain` | 0–100 | 0 | SSFF gain (0=off, start with 20-40) |
| `ondas_gain` | -100–100 | 10 | ONDAS attenuation gain (0=off) |
| `ondas_gain2` | -100–100 | 10 | I-term scaling factor |

### Simulation

`ruby sim_ferocity.rb prize [F_down] [F_up]` — velocity-based physics demo
`ruby sim_ferocity.rb compare [F_down] [F_up]` — fixed vs SSFF comparison