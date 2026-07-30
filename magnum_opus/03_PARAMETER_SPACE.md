# 03 — Parameter Space: Complete Reference

## servoConfig_t — All Orni-Specific Fields

Defined in <file>src/main/flight/servos.h</file>, stored in `PG_SERVO_CONFIG`.

| Field | Type | CLI Name | Range | Default | MSP |
|-------|------|----------|-------|---------|-----|
| `flap_base_frequency` | `uint8_t` | `flap_base_frequency` | 0–255 | — | ✅ MSP_SET_PID_ADVANCED |
| `flap_base_amplitude` | `int8_t` | `flap_base_amplitude` | −128–127 | — | ✅ MSP_SET_PID_ADVANCED |
| `ornithopter_glide_deg` | `int8_t` | `ornithopter_glide_deg` | −128–127 | — | ✅ (own slot) |
| `ondas_gain` | `int8_t` | `ondas_gain` | −100–100 | 10 | ✅ MSP_FILTER_CONFIG (bias-128) |
| `ondas_gain2` | `int8_t` | `ondas_gain2` | −100–100 | 10 | ❌ **NO MSP SLOT** |
| `ondas_gain3` | `int8_t` | `ondas_gain3` | −100–100 | 10 | ❌ **NO MSP SLOT** |
| `aeroelastic_glide_coefficient` | `int8_t` | `aeroelastic_glide_coefficient` | −128–127 | — | ❌ |
| `aeroelastic_flap_coefficient` | `int8_t` | `aeroelastic_flap_coefficient` | −128–127 | — | ❌ |
| `ornithopter_ferocity_downstroke` | `int8_t` | `ornithopter_ferocity_downstroke` | 1–100 | 12 | ❌ |
| `ornithopter_ferocity_upstroke` | `int8_t` | `ornithopter_ferocity_upstroke` | 1–100 | 12 | ❌ |
| `ssff_gain` | `int8_t` | `ssff_gain` | 0–100 | 0 | ❌ |

### ⚠️ MSP Exposure Gaps

**Critical**: `ondas_gain2` (D→ferocity) and `ondas_gain3` (I→asymmetry) have NO MSP message slot. The three-channel architecture cannot be fully tuned in-flight via Configurator — only via CLI. This is a first-order limitation for real-time tuning.

**Encoding note**: `ondas_gain` uses bias-128 encoding in MSP_FILTER_CONFIG:
- Serialize: `(uint8_t)(value + 128)` → maps [−100,100] to [28,228]
- Deserialize: `(int8_t)(raw − 128)` → correct roundtrip

However, the range accepted over MSP is [−128,127] (full int8_t range from uint8_t), bypassing the CLI [−100,100] guard. Downstream clamping in the modulation path mitigates this, but validation should happen at ingestion.

### ferocityParamToFloat Mapping

CLI range [1, 100] maps to ferocity [0, 8]:

```
F = (param − 1) × 8.0 / 99.0   → ferocity ∉ [0, 8]
```

| CLI Value | Ferocity F |
|-----------|------------|
| 1 | 0.00 (pure cosine) |
| 12 | 0.89 (default) |
| 25 | 1.94 |
| 50 | 3.96 |
| 75 | 5.98 |
| 100 | 8.00 (pure square wave) |

**F = 0**: Pure cosine wave — symmetric, no dwell. **F = 8**: Pure square wave via `sign(sinθ)` — maximum breathing pause with infinite cos ramp slope. The dwell ratio `d = F/8` ∈ [0,1] determines the portion of each half-stroke spent at ±1 before the cos ramp begins.

## PID Profile Parameters (pidProfile_t)

From <file>src/main/flight/pid.h</file>, stored in `PG_PID_PROFILE`.

All standard Betaflight PID parameters are available (P/I/D/F per axis, filter settings, anti-gravity, iterm relax, etc.) with the following OrniFlight modifications:

| Parameter | Status | Notes |
|-----------|--------|-------|
| `antiGravityMode` | **Guarded** | Available only when `USE_ORNI_MIXER_ONLY` is NOT defined (i.e., never in OrniFlight). Default = 0 in OrniFlight branch. |
| `itermAcceleratorGain` | **Guarded** | Available only when `USE_ORNI_MIXER_ONLY` is NOT defined. OrniFlight never needs this. |
| `throttle_boost` | **Undef'd** | `USE_THROTTLE_BOOST` is undef'd by `USE_ORNI_MIXER_ONLY` cascade |
| `smart_feedforward` | **Undef'd** | `USE_SMART_FEEDFORWARD` is undef'd by `USE_ORNI_MIXER_ONLY` cascade |
| `use_integrated_yaw` | **Undef'd** | `USE_INTEGRATED_YAW_CONTROL` is undef'd |
| `launchControlMode` | **Undef'd** | `USE_LAUNCH_CONTROL` is undef'd |

## controlRateConfig_t — Rate Profile Extensions

From <file>src/main/fc/controlrate_profile.h</file>:

| Field | Type | Range | Purpose |
|-------|------|-------|---------|
| `flap_speed_modificator` | `uint16_t` | — | Offsets the throttle→frequency mapping. Center at 1500. Fed into `T_cmd` formula. |

## Three-Channel Gain Parameters

| Parameter | Channel | Feeds Into | Scale Factor | Output Range |
|-----------|---------|------------|--------------|--------------|
| `ondas_gain` (−100..100) | P → Phase | `flappingPhaseModulation` | × 0.00005 | [0.5, 2.0] |
| `ondas_gain2` (−100..100) | D → Ferocity | `flappingFerocityModulation` | × 0.0003 | [−0.5, +0.5] |
| `ondas_gain3` (−100..100) | I → Asymmetry | `flappingAsymmetryBias` | × 0.0001 | [−3.0, +3.0] |

### Gain Interaction Effects

```
ondas_gain dominant (P → phase):
  • Higher → wing accelerates faster on error → more aggressive correction
  • Too high → overshoot, wing racing through strokes
  • Zero → neutral phase (k₀ = 1.0, no modulation)

ondas_gain2 dominant (D → ferocity):
  • Higher → sharper wave → deeper breathing pause → more damping
  • Good for gust rejection and fast stabilization
  • Too high → sluggish response, wing dwell excessive

ondas_gain3 dominant (I → asymmetry):
  • Higher → persistent up/down bias → corrects sustained imbalance
  • Good for CG offset or manufacturing asymmetry
  • Too high → trimmed condition overshoot, oscillation at bias frequency
```

## Simulation Parameters (Hardcoded in sim_ferocity.rb)

| Parameter | Value | Description |
|-----------|-------|-------------|
| `Kp` | 8.0 | Pitch P gain |
| `Ki` | 0.5 | Pitch I gain |
| `Kd` | 2.0 | Pitch D gain |
| `I_YY` | 0.02 | Pitch moment of inertia |
| `PITCH_DAMP` | 0.3 | Aerodynamic pitch damping |
| `dT` | 0.000125 | Integration timestep (8 kHz) |

## Build-Time Constants (pid.c)

| Constant | Value | Usage |
|----------|-------|-------|
| `ONDAS_K0` | 1.0f | Wing ODE drive gain |
| `ONDAS_K2` | 10.0f | Wing ODE damping |
| `ONDAS_PHASE_SCALE` | 0.00005f | P→phase scaling |
| `ONDAS_FEROCITY_SCALE` | 0.0003f | D→ferocity scaling |
| `ONDAS_ASYMMETRY_SCALE` | 0.0001f | I→asymmetry scaling |
| `GLIDE_MODE_THRESHOLD` | 1040 | Throttle value below which glide engages |

## CLI Value Table Entry Format

All orni-specific parameters in `valueTable[]` (<file>src/main/cli/settings.c</file>):

```c
// Standard format: {name, type_flags, .config.minmax, PG_ID, offset}
{"flap_base_frequency",   VAR_UINT8  | MASTER_VALUE, .config.minmaxUnsigned = {0,255}, PG_SERVO_CONFIG, offsetof(servoConfig_t, flap_base_frequency)},
{"ondas_gain",            VAR_INT8   | MASTER_VALUE, .config.minmax = {-100,100},      PG_SERVO_CONFIG, offsetof(servoConfig_t, ondas_gain)},
// etc.
```

⚠️ `flap_base_frequency` minimum of 0 is a **critical bug** — causes division by zero in the wing ODE. Should be `{1, 255}`.