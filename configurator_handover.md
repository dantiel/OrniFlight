# ONDAS Handover — July 2026

For: **Configurator** (GUI project) and **PteronautOS** (ESP8285 simpler-hardware fork)
Source: OrniFlight `de11518` (STMF4 flight controller, Betaflight-derived)

---

## 1. Naming Rename (BREAKING)

All `ondas_gain*` parameters renamed. Old configs will need migration:

| Old CLI Name | New CLI Name | Range | Feeds | Modulates |
|---|---|---|---|---|
| `ondas_gain` | `cadence_gain` | -100..100 | P → k₀ spring | Phase timing |
| `ondas_gain2` | `ferocity_d_gain` | -100..100 | D → dwell ratio | Wave sharpness (rate) |
| `ondas_gain3` | `balance_gain` | -100..100 | I → up/down | Thrust symmetry |
| *(none)* | `ferocity_p_gain` | 0..100 | P → dwell ratio | Wave sharpness (proportional) |
| *(none)* | `ferocity_roll_gain` | 0..100 | Roll P → common ferocity | Roll inertia gate |
| *(none)* | `ferocity_yaw_gain` | 0..100 | Yaw P → common ferocity | Yaw inertia gate |
| *(none)* | `warp_gain` | -100..100 | Roll P → L/R ferocity diff | Bank differential |
| *(none)* | `warp_yaw_gain` | -100..100 | Yaw P → fore/aft ferocity diff | Turn differential |
| *(none)* | `anchor_gain` | 0..100 | Static → k₂ damping | Frequency lock |
| *(none)* | `resonance_gain` | 0..100 | Error×sin(θ) → I boost | Flap-coherent filter |
| `ssff_gain` | `ssff_gain` | 0..100 | *(unchanged)* | Per-stroke learning |

**Configurator action**: Add 6 new parameters to the ONDAS tab. Rename the existing 3. Map old names → new names in config migration.

**PteronautOS action**: Rename `ORNI_ONDAS_GAIN` → `ORNI_CADENCE_GAIN`, etc. in `OrnithopterConfig.h`. Add the 6 new defines. Update `Ornithopter.h` member names (`ondasGain` → `cadenceGain`, `ondasGain2` → `ferocityDGain`, `ondasGain3` → `balanceGain`).

---

## 2. Conceptual Map

```
PID Error Decomposition         Wing Property (ONDAS Channel)
══════════════════════         ═══════════════════════════════
                              ┌─────────────────────────────┐
  P (present)  ──────┬──────► │ CADENCE     phase timing    │  k₀ spring constant
                     │        │ FEROCITY    wave sharpness   │  dwell ratio d
  D (velocity) ──────┤        ├─────────────────────────────┤
                     └──────► │ FEROCITY    wave sharpness   │  dwell ratio d
                              ├─────────────────────────────┤
  I (integral) ─────────────► │ BALANCE     thrust symmetry  │  up/down bias
                              ├─────────────────────────────┤
  ROLL P ────────┬──────────► │ WARP        L/R ferocity Δ   │  bank differential
                 └──────────► │ FEROCITY    common-mode       │  inertia gate
                              ├─────────────────────────────┤
  YAW P  ────────┬──────────► │ WARP YAW    fore/aft Δ       │  turn differential
                 └──────────► │ FEROCITY    common-mode       │  inertia gate
                              ├─────────────────────────────┤
  (static)                    │ ANCHOR      k₂ damping        │  freq lock strength
  error×sin(θ)                │ RESONANCE   lock-in filter    │  flap-coherent boost
                              └─────────────────────────────┘
```

**Ferocity** is now a PD-blend: both P and D feed dwell ratio with independent gains. This lets the pilot decide whether wave sharpness responds to error magnitude, error rate, or both.

**WARP** generates dual waveforms (left/right wings) with a ferocity differential driven by roll and yaw P-terms. Left wing = base + warpRoll - warpYaw; Right wing = base - warpRoll + warpYaw.

**ANCHOR** varies the wing ODE's k₂ damping coefficient from 10.0 (default tight) down to 0.0 (loose). Higher → tighter frequency lock, more stable but less responsive to throttle transients.

**RESONANCE** is a phase-locked error amplifier — multiplies pitch error by sin(θ), leaky-integrates (τ=0.15s) to extract flap-coherent DC, remodulates and amplifies. Errors that beat with the wing get boosted. Applied to I-term error before ONDAS.

---

## 3. New Waveform Architecture (Trapezoidal)

The old `tanh(F·sinθ)/tanh(F)` wave shaper is replaced with trapezoidal shaping (dwell + cos ramp), ported from GralhaAzul. `f ∈ [0,8]`, dwell ratio `d = f/8`.

`applyFerocityWaveShaping()` now takes dual output pointers (`*outShaped`, `*outDerivative`) and generates independent left/right waveforms for WARP.

---

## 4. Per-Axis Ferocity Accumulation

The ferocity modulation signal is now accumulated across all three axes before the wave shaper:

```
ferocityModulation = clamp(
    pitch_PD_blend ± 0.35  +  roll_P ± 0.15  +  yaw_P ± 0.15,
    ± 0.5
)
```

Each axis independently gates how much wing inertia passes through to the airframe. A sudden yaw demand sharpens the wing stroke, increasing its "bite" against air resistance.

---

## 5. Quadcopter Feature Stripping (commit 6221913)

16 Betaflight quadcopter/propeller features disabled for ornithopter builds:

| Category | Features #undef'd |
|---|---|
| Motor protocols | USE_DSHOT, USE_DSHOT_DMAR, USE_ESCSERIAL_SIMONK, USE_SERIAL_4WAY_SK_BOOTLOADER, USE_SERIAL_4WAY_BLHELI_BOOTLOADER |
| ESC sensors | USE_ESC_SENSOR, USE_ESC_SENSOR_INFO, USE_ESC_SENSOR_TELEMETRY |
| Quad PID | USE_TPA_MODE, USE_THRUST_LINEARIZATION, USE_D_MIN, USE_AIRMODE_LPF, USE_DYN_LPF |
| Metering | USE_VIRTUAL_CURRENT_METER |
| (prior) | USE_DSHOT_TELEMETRY, USE_RPM_FILTER, USE_BRUSHED_ESC_AUTODETECT, USE_LAUNCH_CONTROL, USE_THROTTLE_BOOST, USE_SMART_FEEDFORWARD, USE_INTEGRATED_YAW_CONTROL |

Motor output path neutered (#ifndef USE_ORNI_MIXER_ONLY):
- `writeMotors()`, `stopMotors()`, `stopPwmAllMotors()` → no-ops
- `applyFlipOverAfterCrashModeToMotors()`, `applyMotorStop()` → no-ops
- 3D mode stripped from `calculateThrottleAndCurrentMotorEndpoints()`
- `mixerConfigureOutput()` / `mixerLoadMix()` use orni-only path (ORNI_MOTOR_COUNT=4)

### PteronautOS / Configurator impact:
- **PteronautOS**: No impact — these were already BF-specific features.
- **Configurator**: If GUI exposes TPA, Thrust Linearization, D_MIN, or DSHOT settings, they can be hidden for OrniFlight targets (detected via `mixerMode == MIXER_ORNI` or firmware name).

---

## 6. Files Changed (OrniFlight — for reference)

| File | Change |
|---|---|
| `src/main/flight/pid.c` | ONDAS rename, PD-blend, WARP dual-wave, Anchor k₂, Resonance filter, per-axis ferocity |
| `src/main/flight/pid.h` | Extern declarations for `shapedFlappingSinusoidLeft/Right` |
| `src/main/flight/servos.h` | 10 new `int8_t` fields in `servoConfig_t` |
| `src/main/flight/servos.c` | Left/right wing servo mapping, `anchor_k2` computation |
| `src/main/cli/settings.c` | 10 CLI parameters |
| `src/main/msp/msp.c` | MSP get/set for all 10 params |
| `src/main/flight/mixer.c` | Motor output no-ops, 3D strip, orni-only mixer config |
| `src/main/flight/mixer.h` | ORNI_MOTOR_COUNT define |
| `src/main/target/common_pre.h` | 14 additional #undefs for quad features |
| `ONDAS.md` | Full architecture documentation |

---

## 7. PteronautOS Porting Guide

### What to rename in `OrnithopterConfig.h`:
```
ORNI_ONDAS_GAIN     → ORNI_CADENCE_GAIN      (default 20)
ORNI_ONDAS_GAIN2    → ORNI_FEROCITY_D_GAIN   (default 20)
ORNI_ONDAS_GAIN3    → ORNI_BALANCE_GAIN      (default 10)
```

### What to add (new defines):
```c
#define ORNI_FEROCITY_P_GAIN    10   // P→ferocity blend
#define ORNI_FEROCITY_ROLL_GAIN 0
#define ORNI_FEROCITY_YAW_GAIN  0
#define ORNI_WARP_GAIN           0
#define ORNI_WARP_YAW_GAIN       0
#define ORNI_ANCHOR_GAIN         0    // 0=default tightness
#define ORNI_RESONANCE_GAIN      0
```

### What to rename in `Ornithopter.h` members:
```cpp
float ondasGain;      → float cadenceGain;
float ondasGain2;     → float ferocityDGain;
float ondasGain3;     → float balanceGain;
// Add:
float ferocityPGain;
float ferocityRollGain;
float ferocityYawGain;
float warpGain;
float warpYawGain;
float anchorGain;
float resonanceGain;
```

### What to upgrade in the waveform kernel (`Ornithopter.cpp`):
1. Trapezoidal wave shaping (replace tanh)
2. PD-blend on ferocity (P + D → dwell ratio)
3. Optional: per-axis ferocity accumulation
4. Optional: Anchor (variable k₂)
5. Optional: Resonance lock-in filter

### What PteronautOS can skip (ESP8285 too constrained):
- Dual left/right waveform generation (WARP) — unless using ≥2 servo profile
- Full per-axis ferocity — the ESP8285 doesn't have a full PID loop on all axes; Zephyrus provides limited stabilization

---

## 8. Simulator Note

`sim_ferocity.rb` still uses the old tanh wave shaping. Needs updating to match the trapezoidal shaper in firmware. Add mode for PD-blend and per-axis ferocity testing.

---

## 9. Build Status (OrniFlight)

- Flash: **95.55%** (~1484 bytes remaining on TINYFISH, 252 KB flash)
- Build: clean, commit `6221913`

---

## 10. Future Frontiers (Not Yet Implemented)

| Name | Concept | Priority |
|---|---|---|
| **Prescience** | Stroke-ahead prediction — estimate craft position at next reversal, pre-compute modulation | High |
| **Espelho** | Wing-self-noise cancellation — model gyro coupling from wing motion, subtract predicted signal | Medium |
| **Saudade** | Per-stroke online learning — each half-stroke is a training sample | Low |