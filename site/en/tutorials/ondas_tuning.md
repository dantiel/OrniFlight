# ONDAS Tuning Guide

> *The practical companion to ONDAS Theory — how to tune each parameter by feel.*

## Tuning Order

ONDAS parameters are interdependent. Tune them in this sequence:

```
1. Cadence    →  timing
2. Ferocity D →  primary stabilization
3. Ferocity P →  response crispness
4. Balance    →  upstroke/downstroke bias
5. Warp       →  modulation width
6. Anchor     →  dry/wet mix
7. Resonance  →  cycle-to-cycle memory
8. Phase 2    →  advanced (prescience, espelho, saudade, SSFF)
```

## Step by Step

### 1. Cadence — Find Your Phase Window

**Goal**: Place modulation where your wing has the most bite.

**Method**: 
- Start at 50
- Increase to 70 — does roll response get weaker?
- Decrease to 30 — does roll response get stronger?
- The "strongest" point is where your wing's power stroke peaks

**Signs of too high**: Mushy response, craft feels "delayed"
**Signs of too low**: Jerky response, overshoot on roll

### 2. Ferocity D — Steady the Craft

**Goal**: Primary stabilization without oscillation.

**Method**:
- Start at 20
- Hover or steady forward flight
- Increase until you feel the craft "stiffen"
- Back off 5 points from where you first notice oscillation

**Signs of too high**: Fine vibration, motor-like buzz in servos
**Signs of too low**: Craft drifts, feels loose

### 3. Ferocity P — Crispness

**Goal**: Responsive but not twitchy.

**Method**:
- Start at 15
- Bump the roll stick — does the craft immediately bite?
- Increase until stick response is crisp
- Back off if you see overshoot

**Signs of too high**: Ringing after stick input, bounce-back
**Signs of too low**: Mushy, delayed response

### 4. Balance — Asymmetry Tuning

**Goal**: Equal authority in both directions.

**Method**:
- Fly straight and level
- Roll left, note response speed
- Roll right, note response speed
- Adjust balance to equalize them

### 5–7. Warp, Anchor, Resonance

Fine-tuning parameters. Only adjust after 1-4 are solid.

| Param | Start | Adjust When |
|-------|-------|-------------|
| Warp | 50 | Modulation feels too spread out or too peaky |
| Anchor | 70 | Want more/less raw PID mixed in |
| Resonance | 30 | Hovering unstable, or forward flight feels ringy |

### 8. Phase 2 — Advanced

| Param | Effect |
|-------|--------|
| Prescience | Timing advance — higher = modulation leads phase more |
| Espelho | Differential coupling — tighter roll, may reduce efficiency |
| Saudade | Stroke memory — smoother but less responsive |
| SSFF | Direct gyro→wave injection — start at 10 |

---

*The goal is a craft that flies like it wants to be in the air. If you're fighting it, back off and retune from Cadence up.*
