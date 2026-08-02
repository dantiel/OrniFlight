# Flight Profiles

> *4 independent tuning slots, switchable in-flight.*

## Concept

OrniFlight stores 4 complete `ornithopterProfile_t` structs — each containing all 19 ONDAS and wing-dynamics parameters. A BOX mode (`BOXORNITHOPTERPROFILE`, permanentId 52) selects the active profile via a 2-position RC switch mapped to 4 slots (0–3).

## Why Profiles?

Different flight regimes demand different tuning:

| Profile | Use Case | Cadence | Ferocity | Notes |
|---------|----------|---------|----------|-------|
| 0 | **Cruise** | Mid (50) | Low (30) | Efficient forward flight |
| 1 | **Aerobatic** | Low (20) | High (80) | Maximum authority |
| 2 | **Hover/Loiter** | High (70) | Mid (50) | Stability over speed |
| 3 | **Glide** | Mid (50) | Low (10) | Minimal intervention |

## What's In a Profile

All 19 fields of `ornithopterProfile_t`:

- **Glide geometry**: glide_angle
- **ONDAS v2 (10)**: cadence, ferocity_d/p/roll/yaw, balance, warp, warp_yaw, anchor, resonance
- **Phase 2 (4)**: prescience, espelho, saudade, ssff
- **Wave shape (2)**: ferocity_downstroke, ferocity_upstroke
- **Aeroelastic (2)**: aeroelastic_glide_coefficient, aeroelastic_flap_coefficient

## What's Global (Not Per-Profile)

- Frequency channel (one RC channel, works in both INDEPENDENT and GLIDE)
- Servo mount angles
- Flapping phase shifts
- GralhaAzul geometry (servo_speed, max_amplitude, flap_magnitude, wing_origin)

These are physical constants of the airframe — they don't change with flight regime.

## Switching In Flight

1. Assign a 2-position or 3-position switch to a spare channel
2. In the Configurator Modes tab, map that range to `ORNITHOPTER PROFILE`
3. Each switch position selects one of the 4 slots
4. The Configurator's profile dropdown edits the *currently selected* slot via MSP

---

*See `src/main/flight/ornithopter_profile.h` for the struct definition.*
