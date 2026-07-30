# 01 — Architecture: System Topology & Data Flow

## Component Graph

```mermaid
graph TD
    subgraph Sensors
        GYRO[GYRO - ICM-20602/MPU6000]
        ACC[ACC - on-chip]
        BARO[BARO - BMP280/DPS310]
        MAG[MAG - HMC5883/QMC5883]
    end

    subgraph RX
        RC[RC Receiver - SBUS/CRSF/IBUS]
    end

    subgraph Filters
        GYRO_LPF[Gyro LPF - PT1/BIQUAD]
        RPM_N[RPM Notch Filter]
        D_LP[D-term LPF Cascade]
        NOTCH[D-term Notch]
    end

    subgraph Control
        SETPOINT[Setpoint Generation - Rates/Expo]
        PID[PID Controller - pid.c]
        ONDAS[ONDAS Gate]
        FEROCITY[Ferocity Wave Shaping]
        SSFF[Stroke-Sync Feed-Forward]
    end

    subgraph Flapping
        WING_ODE[Wing Phase ODE - θ̈=k₀·T−k₂·ω]
        SHAPER[Wave Shaper - tanh(F·sinθ)/tanh(F)]
        DERIV[Shaped Derivative]
    end

    subgraph Output
        MIXER[Servo Mixer - mixer.c]
        SERVO_PWM[Servo PWM Output - servos.c]
    end

    subgraph Telemetry
        MSP[MSP Protocol - msp.c]
        SMART[SmartPort/CRSF Telemetry]
        OSD[OSD Overlay]
    end

    GYRO --> GYRO_LPF --> RPM_N --> PID
    ACC --> PID
    RC --> SETPOINT --> PID
    RC --> WING_ODE

    PID -->|Pitch Error| ONDAS
    PID -->|3-Channel Modulation| FEROCITY
    PID -->|Pitch Error Rate| SSFF
    SSFF -->|Ferocity Bias| FEROCITY

    WING_ODE -->|sinθ, cosθ| SHAPER
    FEROCITY -->|dMod, iBias| SHAPER
    SHAPER -->|shapedWave| ONDAS
    SHAPER -->|ornithopterFlapping| MIXER
    DERIV -->|flappingDerivative| PID

    PID -->|Servo Commands| MIXER
    MIXER --> SERVO_PWM

    PID --> MSP
    PID --> SMART
    PID --> OSD
```

## Data Flow: One PID Iteration

```
┌─────────────────────────────────────────────────────────────┐
│                     pidController()                          │
│  (Called at 4-8 kHz via scheduler)                          │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  1. Read gyro → apply RPM notch + lowpass cascade           │
│  2. Compute D-term from filtered gyro (2-stage LPF)         │
│  3. calculateFlappingFromThrottle(rc_throttle)              │
│     ├─ Wing ODE step: θ̈ = k₀·P_mod·T_cmd − k₂·ω           │
│     ├─ Euler integrate: θ += ω·dt, ω += θ̈·dt              │
│     ├─ sin(θ), cos(θ)                                       │
│     ├─ applyFerocityWaveShaping(sinθ, dMod, iBias)          │
│     │   └─ tanh(F·sinθ)/tanh(F) with per-stroke blend       │
│     └─ Compute shaped derivative for aeroelastic scaling     │
│  4. Per-axis PID loop (ROLL, PITCH, YAW)                    │
│     ├─ Setpoint rate calc → accel limit → level/horizon    │
│     ├─ Error rate = setpoint − gyro (deg/s)                 │
│     ├─ P-term, I-term (with relax/windup), D-term           │
│     ├─ On PITCH: applyStrokeSynchronousFF(errorRate)        │
│     └─ On PITCH: three-channel breathing-pause modulation   │
│         ├─ P × ondas_gain → flappingPhaseModulation [0.5,2]│
│         ├─ D × ondas_gain2 → flappingFerocityMod [-0.5,0.5]│
│         └─ I × ondas_gain3 → flappingAsymmetryBias [-3,3]  │
│  5. ONDAS gate: scale PID output by -|shapedWave| + 0.5     │
│  6. Mix to servo outputs, apply rate limits, write PWM      │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

## File Map: Key Components

| File | Role | Lines |
|------|------|-------|
| `src/main/flight/pid.c` | PID controller, wing ODE, ferocity, ONDAS, SSFF, three-channel | ~1800 |
| `src/main/flight/pid.h` | PID struct, PG config, function signatures | ~220 |
| `src/main/flight/mixer.c` | Throttle→servo mixing, ornithopter mixer path, glide mode | ~800 |
| `src/main/flight/servos.c` | Servo PWM output, config PG, ferocity/glide/wing params | ~600 |
| `src/main/flight/servos.h` | `servoConfig_t` structure, all orni-specific fields | ~170 |
| `src/main/cli/settings.c` | All CLI-visible parameters, valueTable | ~1500 |
| `src/main/msp/msp.c` | MSP protocol, message handlers | ~2200 |
| `src/main/target/common_pre.h` | Feature defines, `USE_ORNI_MIXER_ONLY` cascade | ~330 |
| `src/main/target/common_post.h` | Cascaded feature logic | ~200 |
| `sim_ferocity.rb` | Ruby simulation harness (6 modes) | ~600 |
| `ONDAS.md` | Project documentation of ONDAS+Ferocity+SSFF | ~80 |

## Feature Define Cascade

When `USE_ORNI_MIXER_ONLY` is defined (it always is in OrniFlight), a cascade of undefs strips Betaflight propeller features:

```
USE_ORNI_MIXER_ONLY
  → #undef USE_DSHOT
  → #undef USE_DSHOT_TELEMETRY
  → #undef USE_RPM_FILTER
  → #undef USE_BRUSHED_ESC_AUTODETECT
  → #undef USE_LAUNCH_CONTROL
  → #undef USE_THROTTLE_BOOST
  → #undef USE_SMART_FEEDFORWARD
  → #undef USE_INTEGRATED_YAW_CONTROL
```

This is sourced in `common_pre.h` line ~305 and cascades through `#ifdef`/`#ifndef` guards throughout the codebase. Notably, `USE_ORNI_MIXER_ONLY` guards are *not* universally applied — some Betaflight fields (antiGravityMode, itermAcceleratorGain) were only partially guarded until the Coagula phase fixed this.

## Three-Channel Breathing-Pause Architecture

The core innovation: PID terms modulate wing **trajectory** parameters, not servo offsets.

```
┌──────────────────────────────────────────────────┐
│              PID → Wing Trajectory                │
├──────────┬───────────────┬───────────────────────┤
│ Channel  │ PID Term      │ Modulates             │
├──────────┼───────────────┼───────────────────────┤
│ 1 (k₀)   │ P (immediate) │ Phase advance —       │
│          │               │ "Push harder NOW"     │
│          │               │ k₀ × modulation       │
│          │               │ Range: [0.5, 2.0]     │
├──────────┼───────────────┼───────────────────────┤
│ 2 (F)    │ D (velocity)  │ Ferocity —            │
│          │               │ Wave sharpness        │
│          │               │ "Delay next stroke"   │
│          │               │ Range: [-0.5, +0.5]   │
├──────────┼───────────────┼───────────────────────┤
│ 3 (Asym) │ I (persistent)│ Up/down bias —        │
│          │               │ Asymmetry correction  │
│          │               │ Range: [-3.0, +3.0]   │
└──────────┴───────────────┴───────────────────────┘
```

This is fundamentally different from quadcopter control where PID directly sets motor speeds. Here, PID shapes the wing's *motion path*, and the wing's interaction with air produces forces that stabilize the airframe.

## Memory Layout

- **OMNIBUSF7**: Flash 99.43% used, SRAM1 16.12% used
- Flash budget is critically tight for any further additions
- Parameter groups (PG) stored in flash, loaded to RAM at boot
- `servoConfig_t` lives in `PG_SERVO_CONFIG` — all orni params in one PG
