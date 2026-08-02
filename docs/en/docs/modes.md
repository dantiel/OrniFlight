# Flight Modes

Modes are toggled via AUX switches on your transmitter. Each mode can be assigned to a specific AUX channel range in the **Modes** tab of OrniFlight Configurator.

## Standard Modes

| Mode | Function |
|------|----------|
| **ARM** | Enable flight control (motors/servos active) |
| **ANGLE** | Auto-level — craft returns to level when sticks centered |
| **HORIZON** | Hybrid — angle mode near center, acro at full stick |
| **ACRO** | Default — no auto-level, pure rate control |
| **AIRMODE** | Keeps PID loop active at zero throttle for full authority |

## OrniFlight-Specific Modes

| ID | Mode | Function |
|----|------|----------|
| 50 | **INDEPENDENT** | Independent wing control — each wing responds to its own servo channel |
| 51 | **GLIDE** | Glide mode — wings locked in horizontal position for soaring |
| 52 | **PROFILE** | Flight profile selection — switch between 3 PID/ONDAS profiles |

## Utility Modes

| Mode | Function |
|------|----------|
| **BEEPER** | Activate buzzer for locating lost aircraft |
| **BLACKBOX** | Start/stop Blackbox logging |
| **FAILSAFE** | Manually trigger failsafe stage 2 (panic switch) |
| **OSD** | Toggle OSD display |
| **TELEMETRY** | Enable/disable telemetry output |

## Ornithopter Notes

- **INDEPENDENT** mode is unique to OrniFlight — it enables per-wing servo mapping for asymmetric thrust and differential wing control
- **GLIDE** mode holds wings at neutral position, useful for thermal soaring and energy-efficient descent
- **PROFILE** switching allows in-flight ONDAS parameter changes for varying flight conditions (e.g., cruise vs. aggressive maneuvering)
