# Mixer

The mixer translates flight controller outputs (roll, pitch, yaw, throttle) into servo and motor signals for your ornithopter.

## Ornithopter Mixer

OrniFlight extends Betaflight's mixer system with ornithopter-specific configurations. The mixer handles:

- **Wing servos**: Convert PID output to wing stroke modulation
- **Tail servos** (optional): Control elevator/rudder surfaces
- **ESCs**: Motor speed for non-flapping thrust (if hybrid setup)

## Mixer Types

| Mixer | Use Case |
|-------|----------|
| **ORNITHOPTER** | Standard dual-wing ornithopter with 2 wing servos |
| **ORNITHOPTER_4S** | 4-servo ornithopter (independent left/right wing control) |
| **ORNITHOPTER_TAIL** | Dual-wing + tail elevator + rudder |

## Servo Configuration

Configured in the **Servos** tab or via CLI:

```
smix reverse 0 2 r       # Reverse servo 2
smix 0 0 0 100 0 0 100   # Servo 0: roll mixing
smix 1 1 1 100 0 0 100   # Servo 1: pitch mixing
```

## ONDAS Integration

The mixer works in concert with ONDAS (Ornithopter Nonlinear Dynamic Aerodynamic System):

- **Throttle** → sets base flapping amplitude
- **ONDA Cadence** → shifts the modulation window within each stroke
- **ONDA Ferocity** → modifies stroke waveform shape (sinusoidal ↔ trapezoidal)
- **ONDA Balance** → left/right wing symmetry correction

For detailed ONDAS theory, see the [ONDAS Wiki](../wiki/ondas.html).

## CLI Settings

```
mixer = ORNITHOPTER
set servo_pwm_rate = 330     # Servo update frequency
set servo_center_pulse = 1500
set flap_spread = 20         # Wing angle amplitude in degrees
```
