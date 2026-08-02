# PID Tuning

OrniFlight uses a PID (Proportional-Integral-Derivative) controller adapted for flapping-wing flight. Tuning differs significantly from multirotors due to the periodic nature of flapping thrust.

## Ornithopter PID Basics

Unlike multirotors where thrust is nearly instantaneous, ornithopter thrust oscillates with each wing stroke. This creates:

- **Thrust ripple** at flapping frequency (typically 5–15 Hz)
- **Phase-dependent control authority** — same PID output has different effect depending on where in the stroke cycle it's applied
- **Coupled roll-yaw dynamics** — asymmetric wing thrust affects both axes simultaneously

## PID Terms

| Term | Effect | Ornithopter Note |
|------|--------|-----------------|
| **P** | Proportional — immediate correction | Use lower values than multirotors; oscillation is flapping-synchronous |
| **I** | Integral — persistent error correction | Essential for maintaining attitude during glides |
| **D** | Derivative — dampens oscillations | Tuned to wing stroke rate, not frame oscillations |
| **F** | Feed-forward — direct stick-to-output | Useful for crisp response on roll axis |

## Starting Values

For a medium-sized ornithopter (1–1.5m wingspan):

| Axis | P | I | D | F |
|------|---|---|---|---|
| Roll | 25 | 30 | 15 | 30 |
| Pitch | 30 | 35 | 20 | 35 |
| Yaw | 40 | 35 | 10 | 20 |

## Tuning Procedure

### 1. Rate Tuning First

Before PID tuning, set rates that feel comfortable:
- Start with RC Rate 0.90, Super Rate 0.65, Expo 0.30
- Adjust for your flying style and ornithopter size

### 2. P Gain

Increase P until you see oscillation at flapping frequency, then back off 20%:
- Roll oscillation: wing wobble at stroke rate
- Pitch oscillation: fore-aft bobbing
- Yaw oscillation: tail wag synchronized with strokes

### 3. D Gain

Increase D to dampen bounce-back after sharp stick inputs:
- Too much: servo jitter, overheating
- Too little: ringing after roll/pitch stops

### 4. I Gain

I gain counters persistent drift:
- Increase until drift is eliminated
- Too much: slow oscillation at 1–2 Hz (below flapping rate)

## ONDAS Integration

ONDAS (Ornithopter Nonlinear Dynamic Aerodynamic System) modulates the PID output within each wing stroke. After basic PID tuning:

1. Set **Cadence Gain** — shifts modulation window to aerodynamically optimal phase
2. Set **Ferocity P** — immediate asymmetric thrust boost
3. Set **Ferocity D** — anticipatory drag exploitation
4. Fine-tune **Balance** — left/right wing symmetry

See [ONDAS Tuning Guide](ondas_tuning.html) for detailed procedure.

## Blackbox Analysis

Enable Blackbox logging to visualize PID performance. Look for:
- **P-term oscillation** at flapping frequency → reduce P
- **I-term windup** during sustained turns → reduce I or increase I-term relax
- **D-term noise** from vibration → check mechanical balance first, then reduce D

## Flight Profiles

OrniFlight supports 3 flight profiles switchable mid-flight:

| Profile | Use Case |
|---------|----------|
| 1 | Standard cruise |
| 2 | High agility / aggressive |
| 3 | Efficiency / thermal soaring |
