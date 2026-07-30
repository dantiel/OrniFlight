# 06 — Improvement Vision: Roadmap

## 🔴 Immediate (Fix Now — Already Identified in Validatio)

### C1: MSP Buffer Over-Read Fix
**File**: <file>src/main/msp/msp.c</file> line 2169
**Change**: Guard `sbufBytesRemaining(src) >= 7` → `sbufBytesRemaining(src) >= 9`
**Impact**: Prevents buffer over-read on malformed MSP_SET_PID_ADVANCED packets
**Risk**: Zero — purely a safety fix

### C2: Division-by-Zero Fix
**Files**: <file>src/main/cli/settings.c</file> line 1426, <file>src/main/flight/pid.c</file> line 698
**Changes**:
1. CLI: `{0, 255}` → `{1, 255}` for `flap_base_frequency`
2. Runtime guard: `if (servoConfig()->flap_base_frequency == 0) return;` in `calculateFlappingFromThrottle`
**Impact**: Prevents NaN cascade → flight controller lockup
**Risk**: Zero — frequency of 1 is effectively "near-zero" but safe

## 🟡 Short-term (Next Release)

### 1. MSP Exposure for ondas_gain2 & ondas_gain3
Add these to an existing MSP message (or create a new one). The three-channel architecture cannot be fully tuned in-flight without this.
- **Suggested slot**: Extend MSP_FILTER_CONFIG or create MSP_ORNI_CONFIG
- **Encoding**: Same bias-128 as `ondas_gain`
- **Configurator**: Coordinate with Configurator team to expose the new fields in the UI

### 2. ferocityParamToFloat Range Fix
Either:
- (A) Change CLI range to `{1, 81}` (last value before saturation)
- (B) Change mapping to `1.0 + (param-1)*7.0/80.0` with clamp at 8.0
- (C) Extend upper clamp to 9.0 or 10.0 to give the full CLI range meaning

Option A is simplest and doesn't change existing tuning behavior for values ≤80.

### 3. NaN-Safe Clamping
Replace `if (fDown < 1.0f)` with `if (!(fDown >= 1.0f))` in `applyFerocityWaveShaping`. This catches NaN (NaN comparisons always return false, but `!(NaN >= 1.0f)` is true). Or add explicit `isnan()` checks.

### 4. CLI Parameter Validation
Add interdependent constraint validation:
- Warn if `flap_base_frequency == 0` (before fixing range)
- Warn if `ondas_gain2` is set but `ondas_gain` is zero (D→ferocity channel active without P→phase)
- Suggest `ssff_gain` values based on measured pitch oscillations

### 5. Code Cleanup
- Remove dead `if (fabsf(tanhF) < 1e-6f)` guard in `applyFerocityWaveShaping`
- Deduplicate blend zone interpolation
- Extract `flappingState_t` struct to replace 5+ globals
- Add explicit casts to `flap_base_amplitude` MSP encoding

### 6. Fix Pre-existing Linker Error
Resolve `undefined reference to 'mixers'` — affects all build targets.

## 🟠 Medium-term (1-3 Releases)

### 1. Autotune: Automated Gain Discovery
Leverage `sim_ferocity.rb` as the foundation for automated PID and ONDAS gain tuning:
- Fly a test pattern, log gyro + RC data
- Replay log through simulation, sweep parameter space
- Report optimal gain set
- Write back via MSP

### 2. Blackbox Logging Enhancement
Add orni-specific signals to blackbox:
- `flappingPhaseModulation`, `flappingFerocityModulation`, `flappingAsymmetryBias` — three-channel internals
- `shapedFlappingSinusoid` — actual wave shape
- `ssffFerocityUpBias`, `ssffFerocityDownBias` — SSFF state
- `ferocityEffective` — per-stroke effective ferocity after all modulation

### 3. Improved Failsafe Behavior
- **Glide-to-land**: On RC loss, enter glide mode with gradual descent profile
- **Phase-coherent shutdown**: Stop flapping at a consistent phase (e.g., wings level) rather than abruptly

### 4. Configurator Integration
- **Three-channel UI**: Visualize P→phase, D→sharpness, I→asymmetry in real time
- **Wave shape preview**: Show the `tanh(F·sinθ)/tanh(F)` output for current ferocity settings
- **ONDAS gate visualization**: Overlay the `-|shapedWave|+0.5` gate on the flapping cycle

### 5. Migrate pid.c → orni_flight.c
Extract orni-specific code into dedicated module:
- `orni_flight.c`: Wing ODE, ferocity, ONDAS, SSFF
- `pid.c`: Pure PID controller, calls into orni_flight
- Reduces pid.c from ~1800 lines to ~1200 (PID) + ~600 (orni_flight)

## 🔵 Long-term (Architecture Evolution)

### 1. Multi-Axis ONDAS
Extend three-channel modulation to ROLL axis:
- **Differential ferocity**: Left wing ferocity ≠ right wing ferocity → roll moment
- **Phase offset**: Small phase difference between wings → roll during power stroke
- Requires independent left/right wing ODE instances

### 2. Adaptive Ferocity via Airspeed Estimation
Estimate airspeed from baro + accel + wing phase and adapt ferocity dynamically:
- Low airspeed → high ferocity (need all the thrust you can get)
- High airspeed → moderate ferocity (efficiency matters more)
- Glide transition → ferocity → 1.0 (pure sine, minimize drag)

### 3. Pluggable Airframe Models
Abstract wing physics into swappable models:
- `airframe_model_t` interface: `computeForces(wingState) → (lift, drag, moment)`
- Default: empirical model based on `sim_ferocity.rb`
- User-defined: species-specific wing profiles as config presets

### 4. DSP-Based Phase Detection Without Hall Sensor
Use gyro/accel data to detect flapping phase via correlation rather than requiring a hall sensor:
- Auto-correlate gyro Z-axis with wing ODE output
- Track phase drift and adjust ODE parameters online
- Reduces hardware complexity (no sensor wiring)

### 5. Autonomous Perch/Land
- Detect suitable landing surface via optical flow / sonar
- Enter glide approach, match descent rate
- Flare at final moment (brief high-ferocity pulse for soft landing)

### 6. Flocking/Swarm Support
- Telemetry mesh via CRSF or ExpressLRS
- Leader-follower PID: follower tracks leader's phase + offset
- Collision avoidance via relative positioning

### 7. Hardware Actuator Abstraction
Support actuator types beyond PWM servos:
- BLDC-driven flapping (higher power, efficiency)
- SMA (shape memory alloy) — silent, lightweight for micro ornithopters
- Dielectric elastomers — future tech

## Flash Budget Strategy

At 99.43% flash used with OMNIBUSF7, every new feature requires budget. Options:
1. **Aggressive LTO** — link-time optimization can recover 5-10%
2. **Dead feature removal** — audit Betaflight features that are compiled but unreachable under `USE_ORNI_MIXER_ONLY`
3. **Target upgrade** — move primary target to STM32H7 (2MB flash)
4. **Modular build** — compile-time selection of features (e.g., OSD, telemetry optional)

## Priority Matrix

```
                    Urgency
                High    Med     Low
            ┌────────┬────────┬────────┐
Impact High │ C1, C2 │ MSP    │ Multi- │
            │        │ Gains  │ Axis   │
            ├────────┼────────┼────────┤
Impact Med  │  NaN   │Config. │ Flock  │
            │ Clamp  │  UI    │        │
            ├────────┼────────┼────────┤
Impact Low  │ Dead   │Blackbox│ DSP    │
            │ Guard  │        │ Phase  │
            └────────┴────────┴────────┘
```
