# 04 — Identity: What OrniFlight IS

## Project Genesis

OrniFlight is a **fork of Betaflight 4.0.6**, created specifically for servo-flapping ornithopters. While Betaflight targets multirotors (quadcopters), OrniFlight replaces motor outputs with oscillating servo-driven wings. The project is licensed under **GPLv3**.

## Core Design Philosophy

### "PID Modulates Wing Trajectory, Not Servo Offset"

This is the fundamental paradigm shift. In a quadcopter, PID directly sets motor speeds — the output is a single scalar per motor. In OrniFlight, PID shapes the wing's **motion path** — the phase, sharpness, and asymmetry of an entire oscillatory trajectory. The wing's interaction with aerodynamics then produces stabilizing forces.

### Three Principles

1. **Trajectory over Torque**: The wing ODE generates a continuous flapping cycle. PID modulates the parameters of this trajectory, not the instantaneous servo position. This means PID corrections are inherently smooth and phase-coherent.

2. **Breathing with the Wing**: ONDAS gates PID authority to the aerodynamic power phase of each stroke. The controller "breathes" with the wing — pushing when there's air to push against, relaxing at stroke reversal when the wing has no authority.

3. **Layered Timescales**: Three control layers operate at different timescales synchronized to flapping phase θ:
   - **Ferocity** (~0 ms): Instantaneous wave shaping at every phase point
   - **ONDAS** (~1 ms): Intra-stroke PID gating
   - **SSFF** (~40 ms): Stroke-to-stroke learning

### What OrniFlight Is NOT

- **Not a quadcopter firmware** — it does not control ESCs, BLDC motors, or propeller thrust
- **Not a generic fixed-wing autopilot** — it's specifically optimized for flapping-wing aerodynamics
- **Not Betaflight-compatible** — while derived from Betaflight, the `USE_ORNI_MIXER_ONLY` cascade strips propeller-specific features

## Target Hardware

- **MCUs**: STM32F3, STM32F4, STM32F7
- **Actuators**: PWM servos (4 ornithopter channels defined: SERVO_ORNITHOPTER_1 through _4)
- **Sensors**: Gyro (required), Accel (optional, for level mode), Baro/Mag (optional)
- **RX Protocols**: SBUS, CRSF, IBUS, and all Betaflight-supported serial receivers

## Feature Identity

### OrniFlight Innovations

| Feature | Description | Novelty |
|---------|-------------|---------|
| **ONDAS** | Oscillating Normalized Dynamic Adaptive Stabilization — phase-gated PID authority | **Original** — novel control paradigm |
| **Ferocity Wave-Shaping** | `tanh(F·sinθ)/tanh(F)` — tunable wave sharpness from sine to near-square | **Original** — physically meaningful nonlinearity |
| **Three-Channel Breathing-Pause** | P→phase advance, D→wave sharpness, I→up/down asymmetry | **Original** — each PID term has distinct physical role |
| **SSFF** | Stroke-synchronous feed-forward learning flap-frequency error patterns | **Adapted** — repurposed feed-forward concept for oscillatory systems |
| **Glide Mode** | Wings hold position when throttle below threshold | **Original** — natural for ornithopters |
| **Aeroelastic PID Scaling** | Velocity-dependent PID gain modulation via shaped derivative | **Original** — compensates for varying aerodynamic authority |

### Inherited from Betaflight (Active)

- PID controller structure (P/I/D/F per axis)
- Gyro filtering cascade (PT1, BIQUAD, RPM notch)
- Rate profiles and expo
- MSP protocol (with OrniFlight extensions)
- OSD, telemetry (SmartPort, CRSF)
- CLI configuration system
- Parameter group (PG) storage system

### Inherited from Betaflight (Stripped by USE_ORNI_MIXER_ONLY)

- DShot motor protocol
- RPM filters
- Launch control
- Throttle boost
- Smart feedforward
- Integrated yaw control
- Brushed ESC autodetect

## Community & Ecosystem

- **Repository**: https://github.com/dantiel/OrniFlight
- **License**: GPLv3
- **Build**: `make TARGET=OMNIBUSF7` (or other target)
- **Configurator**: Betaflight Configurator (with partial OrniFlight parameter support)
- **Simulation**: `ruby sim_ferocity.rb [mode]` — offline physics validation

## Naming Conventions

- **`ornithopter_*`**: Parameters specific to ornithopter flight mode
- **`flap_*`**: Parameters related to flapping mechanics (frequency, amplitude)
- **`ondas_*`**: Parameters for the ONDAS stabilization system
- **`ssff_*`**: Stroke-synchronous feed-forward parameters
- **`aeroelastic_*`**: Aeroelastic compensation coefficients
- **`SERVO_ORNITHOPTER_*`**: Servo channel enum values for wing servos
- **`INPUT_STABILIZED_FLAPPING_*`**: Input source enum values for flapping mixer rules
