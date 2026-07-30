## ONDAS + Ferocity + SSFF: Unified Three-Layer Flapping Stabilization

Three control layers operating at different timescales, unified through the flapping phase θ.

> **Updated 2026-07-29**: Wave shaping ported from GralhaAzul `formaDoBaterDasAsas()` — now trapezoidal (dwell + cos ramp), not tanh.

### The Three Layers

| Layer | Timescale | Mechanism | What It Does |
|-------|-----------|-----------|--------------|
| **Ferocity** | Instantaneous | Trapezoidal: dwell + cos ramp | Shapes wing trajectory — higher F = longer dwell (breathing pause), sharper transitions |
| **Three-Channel** | Intra-stroke (~1 ms) | P→phase, D→dwell depth, I→asymmetry | PID modulates wing trajectory parameters, not servo offset |
| **SSFF** | Stroke boundary (~40 ms) | Per-half-stroke error integration | Biases next stroke's ferocity to cancel repetitive flap-frequency error |

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

### Layer 2: Three-Channel Breathing-Pause Modulation

The old ONDAS gate (`−|shapedWave|+0.5`) has been replaced. PID terms now directly modulate wing trajectory parameters:

| Channel | PID Term | Target | Scale | Effect |
|---------|----------|--------|-------|--------|
| 1 | P | Phase advance (k₀) | `ondas_gain × 0.00005` | "Push harder now" — compresses/stretches current ramp |
| 2 | D | Breathing pause depth | `ondas_gain2 × 0.0003` | "Delay next stroke" — deepens/shallows dwell |
| 3 | I | Up/down asymmetry | `ondas_gain3 × 0.0001` | "Shift center" — biases down vs up ferocity |

The ferocity waveform's dwell zones naturally gate aerodynamic authority — during dwell the wing is at ±1 with zero derivative, functionally identical to the old ONDAS "gate closed" state. The cos ramp provides smooth transition to the power phase.

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

- **Higher downstroke ferocity** → longer dwell on downstroke → stronger pitch-up impulse
- **Higher upstroke ferocity** → longer dwell on upstroke → stronger pitch-down impulse

SSFF modulates this asymmetry stroke-by-stroke based on measured pitch error.

### CLI Parameters

| Parameter | Range | Default | Description |
|-----------|-------|---------|-------------|
| `ornithopter_ferocity_downstroke` | 1–100 | 12 | Base ferocity on downstroke (maps to f∈[0,8]) |
| `ornithopter_ferocity_upstroke` | 1–100 | 12 | Base ferocity on upstroke (maps to f∈[0,8]) |
| `ssff_gain` | 0–100 | 0 | SSFF gain (0=off, start with 20-40) |
| `ondas_gain` | -100–100 | 20 | P→phase advance gain |
| `ondas_gain2` | -100–100 | 20 | D→breathing pause depth gain |
| `ondas_gain3` | -100–100 | 10 | I→asymmetry bias gain |

### Simulation

`ruby sim_ferocity.rb prize [F_down] [F_up]` — velocity-based physics demo
`ruby sim_ferocity.rb compare [F_down] [F_up]` — fixed vs SSFF comparison

**Note:** sim_ferocity.rb currently models the old tanh algorithm — needs update to trapezoidal model.