# MSP Firmware ↔ Configurator Interface — Cross-Reference

> *"As above, so below" — the wire protocol must mirror the firmware's soul.*

---

## 1. File Responsibility Map

| MSP Code | Direction | Send Handler | Receive Handler | Config Source |
|----------|-----------|-------------|-----------------|---------------|
| 1 `MSP_API_VERSION` | FC→GUI | <file>msp.c:351</file> | — | `msp_protocol.h:72` |
| 2 `MSP_FC_VARIANT` | FC→GUI | <file>msp.c:355</file> | — | `msp_protocol.h:78` |
| 42/43 `MSP_MIXER_CONFIG` | R/W | <file>msp.c:800</file> | <file>msp.c:2138</file> | `mixerConfig()->mixerMode` |
| 92/93 `MSP_FILTER_CONFIG` | R/W | <file>msp.c:1000</file> | <file>msp.c:2205</file> | `gyroConfig()`, `currentPidProfile`, `servoConfig()` |
| **94/95 `MSP_PID_ADVANCED`** | **R/W** | <file>msp.c:1030</file> | <file>msp.c:2249</file> | `currentPidProfile`, `servoConfig()` |
| 120/212 `MSP_SERVO_CONFIGURATIONS` | R/W | <file>msp.c:693</file> | <file>msp.c:1931</file> | `servoParams()`, `servoConfig()` |
| 244 `MSP_SET_ORNITHOPTER_GLIDE_DEGREE` | GUI→FC | — | <file>msp.c:2631</file> | ⛔ **NO-OP** (empty handler) |

---

## 2. API Version

| Location | Field | Current Value | Expected |
|----------|-------|---------------|----------|
| <file>msp_protocol.h:73</file> | `API_VERSION_MAJOR` | `1` | `1` ✅ |
| &lt;file&gt;msp_protocol.h:74&lt;/file&gt; | `API_VERSION_MINOR` | **`45`** | **`45`** ??? |
| FC Identifier | `ORNIFLIGHT_IDENTIFIER` | `&quot;ORNI&quot;` | `&quot;ORNI&quot;` ??? |

**Independent mode**: apiVersion reports `1.45.0`. `MSP_PID_ADVANCED` at **82 bytes**.

---

## 3. MSP_PID_ADVANCED (94/95) — Byte-Level Reference

**Current payload**: **82 bytes** (Independent mode via BOX, not parameter byte).

### 3.1 Send (Firmware → Configurator)

| Offset | Configurator Expects | Firmware Writes | Status |
|--------|---------------------|-----------------|--------|
| 0–1 | `rollPitchItermIgnoreRate` (u16) | `0` (u16) | ✅ |
| 2–3 | `yawItermIgnoreRate` (u16) | `0` (u16) | ✅ |
| 4–5 | `yaw_p_limit` (u16) | `0` (u16) | ✅ |
| 6 | `deltaMethod` (u8) | `0` ("reserved") | ✅ |
| 7 | `vbatPidCompensation` (u8) | `vbatPidCompensation` | ✅ |
| 8 | `feedforwardTransition` (u8) | `feedForwardTransition` | ✅ |
| 9 | `dtermSetpointWeight` (u8) | `0` | ✅ (deprecated field) |
| 10 | `toleranceBand` (u8) | `0` | ✅ (deprecated) |
| 11 | `toleranceBandReduction` (u8) | `0` | ✅ (deprecated) |
| 12 | `itermThrottleGain` (u8) | `0` | ✅ (deprecated) |
| 13–14 | `pidMaxVelocity` (u16) | `rateAccelLimit` | ✅ |
| 15–16 | `pidMaxVelocityYaw` (u16) | `yawRateAccelLimit` | ✅ |
| 17 | `levelAngleLimit` (u8) | `levelAngleLimit` | ✅ |
| 18 | `levelSensitivity` (u8) | `0` | ✅ (deprecated) |
| 19–20 | `itermThrottleThreshold` (u16) | `itermThrottleThreshold` | ✅ |
| 21–22 | `itermAcceleratorGain` (u16) | `itermAcceleratorGain` | ✅ |
| 23–24 | `dtermSetpointWeight` (u16) | `0` | ✅ (deprecated) |
| 25 | `itermRotation` (u8) | `iterm_rotation` | ✅ |
| 26 | `smartFeedforward` (u8) | `smart_feedforward` or `0` | ✅ |
| 27 | `itermRelax` (u8) | `iterm_relax` or `0` | ✅ |
| 28 | `itermRelaxType` (u8) | `iterm_relax_type` or `0` | ✅ |
| 29 | `absoluteControlGain` (u8) | `abs_control_gain` or `0` | ✅ |
| 30 | `throttleBoost` (u8) | `throttle_boost` or `0` | ✅ |
| 31 | `acroTrainerAngleLimit` (u8) | `acro_trainer_angle_limit` or `0` | ✅ |
| 32–33 | `feedforwardRoll` (u16) | `pid[ROLL].F` | ✅ |
| 34–35 | `feedforwardPitch` (u16) | `pid[PITCH].F` | ✅ |
| 36–37 | `feedforwardYaw` (u16) | `pid[YAW].F` | ✅ |
| 38 | `antiGravityMode` (u8) | `antiGravityMode` | ✅ |
| 39 | `dMinRoll` (u8) | `d_min[ROLL]` or `0` | ✅ |
| 40 | `dMinPitch` (u8) | `d_min[PITCH]` or `0` | ✅ |
| 41 | `dMinYaw` (u8) | `d_min[YAW]` or `0` | ✅ |
| 42 | `dMinGain` (u8) | `d_min_gain` or `0` | ✅ |
| 43 | `dMinAdvance` (u8) | `d_min_advance` or `0` | ✅ |
| 44 | `useIntegratedYaw` (u8) | `use_integrated_yaw` or `0` | ✅ |
| 45 | `integratedYawRelax` (u8) | `integrated_yaw_relax` or `0` | ✅ |
| 46 | `flapBaseFrequency` (u8) | `flap_base_frequency` | ✅ |
| 47 | `flapBaseAmplitude` (u8, wire:val+128) | `flap_base_amplitude + 128` | ✅ |
| **48** | **`itermRelaxCutoff`** (u8) | `currentPidProfile->iterm_relax_cutoff` | ✅ **PHASE 1** |
| **49** | **`cadence_gain`** (u8, val+128) | `servoConfig()->cadence_gain` | ✅ **PHASE 1** |
| **50** | **`ferocity_d_gain`** (u8, val+128) | `servoConfig()->ferocity_d_gain` | ✅ **PHASE 1** |
| **51** | **`balance_gain`** (u8, val+128) | `servoConfig()->balance_gain` | ✅ **PHASE 1** |
| **52** | **`ferocity_p_gain`** (u8, direct 0–100) | `servoConfig()->ferocity_p_gain` | ✅ **PHASE 1** |
| **53** | **`ferocity_roll_gain`** (u8, direct 0–100) | `servoConfig()->ferocity_roll_gain` | ✅ **PHASE 1** |
| **54** | **`ferocity_yaw_gain`** (u8, direct 0–100) | `servoConfig()->ferocity_yaw_gain` | ✅ **PHASE 1** |
| **55** | **`warp_gain`** (u8, val+128) | `servoConfig()->warp_gain` | ✅ **PHASE 1** |
| **56** | **`warp_yaw_gain`** (u8, val+128) | `servoConfig()->warp_yaw_gain` | ✅ **PHASE 1** |
| **57** | **`anchor_gain`** (u8, direct 0–100) | `servoConfig()->anchor_gain` | ✅ **PHASE 1** |
| **58** | **`resonance_gain`** (u8, direct 0–100) | `servoConfig()->resonance_gain` | ✅ **PHASE 1** |

| **59–62** | **`servo_mount_angle[0..3]`** (u8, val+128) | `servoConfig()->servo_mount_angle` | ✅ **PHASE 2** |
| **63–66** | **`flapping_phase_shift[0..3]`** (u8, val+128) | `servoConfig()->flapping_phase_shift` | ✅ **PHASE 2** |
| **67** | **`prescience_gain`** (u8, direct 0–100) | `servoConfig()->prescience_gain` | ✅ **PHASE 2** |
| **68** | **`espelho_gain`** (u8, direct 0–100) | `servoConfig()->espelho_gain` | ✅ **PHASE 2** |
| **69** | **`saudade_gain`** (u8, direct 0–100) | `servoConfig()->saudade_gain` | ✅ **PHASE 2** |
| **70** | **`ssff_gain`** (u8, direct 0–100) | `servoConfig()->ssff_gain` | ✅ **PHASE 2** |
| **71–72** | **`servo_speed_deg_s`** (u16) | `servoConfig()->servo_speed_deg_s` | ✅ **PHASE 3 (GralhaAzul)** |
| **73** | **`servo_max_amplitude`** (u8, direct) | `servoConfig()->servo_max_amplitude` | ✅ **PHASE 3 (GralhaAzul)** |
| **74** | **`flap_magnitude`** (u8, direct) | `servoConfig()->flap_magnitude` | ✅ **PHASE 3 (GralhaAzul)** |
| **75–78** | **`wing_origin_offset[0..3]`** (u8, val+128) | `servoConfig()->wing_origin_offset` | ✅ **PHASE 3 (GralhaAzul)** |
| **79** | **`independent_freq_channel`** (u8, AUX index) | `servoConfig()->independent_freq_channel` | ✅ **PHASE 4 (Independent)** |
| **80** | **`independent_freq_min`** (u8, Hz) | `servoConfig()->independent_freq_min` | ✅ **PHASE 4 (Independent)** |
| **81** | **`independent_freq_max`** (u8, Hz) | `servoConfig()->independent_freq_max` | ✅ **PHASE 4 (Independent)** |

**Send payload**: **82 bytes** ✅. Mode activated via `BOXORNITHOPTERINDEPENDENT` (RC Modes tab).

### 3.2 Receive (Configurator → Firmware)

Firmware reads up to 79 bytes in four gated tiers:
- Base: 48 bytes (Betaflight 4.0 baseline) — always read.
- Phase 1: if `sbufBytesRemaining(src) >= 11`, reads itermRelaxCutoff + 10 ONDAS v2 (apiVersion ≥ 1.42).
- Phase 2: if `sbufBytesRemaining(src) >= 12`, reads per-pair geometry + 4 advanced params (apiVersion ≥ 1.43).
- Phase 3 (GralhaAzul): if `sbufBytesRemaining(src) >= 8`, reads physical servo params + wing trim (apiVersion ≥ 1.44).

Backward-compatible — a 48-, 59-, or 71-byte sender still works.

**Receive payload handled**: **79 bytes** (gated on available bytes). ✅

### 3.3 Phase 3 — GralhaAzul Port (New) ✅

| Offset | Field | Wire | Default | Range |
|--------|-------|------|---------|-------|
| 71–72 | `servo_speed_deg_s` | u16 LE | 857 | 100–2000 °/s |
| 73 | `servo_max_amplitude` | u8 direct | 55 | 20–90 ° |
| 74 | `flap_magnitude` | u8 direct | 4 | 1–20 centi-°/µs |
| 75–78 | `wing_origin_offset[0..3]` | u8 = val+128 | 0 | –30..+30° per pair |
| 70 | `ssff_gain` | u8 direct | 0–100 |
| 79 | `independent_freq_channel` | u8 direct | 1 | AUX index (0=AUX1) |
| 80 | `independent_freq_min` | u8 direct | 1 | Hz at RC=1000 |
| 81 | `independent_freq_max` | u8 direct | 25 | Hz at RC=2000 |

**Mode activation**: Not a parameter byte. Independent mode is engaged via `BOXORNITHOPTERINDEPENDENT` — configure in the RC Modes tab like ARM, ANGLE, etc.

---

## 4. MSP_SERVO_CONFIGURATIONS (120/212)

### 4.1 Send (Firmware → Configurator)

Firmware sends per-servo records (12 bytes each for `MAX_SUPPORTED_SERVOS` servos) followed by **4 trailing bytes**:

| Offset after servos | Field | Wire | Status |
|---------------------|-------|------|--------|
| +0 | `ornithopter_glide_deg` | u8 = val+128 | ✅ |
| +1 | `cadence_gain` | u8 = val+128 | ✅ **PHASE 1** |
| +2 | `ferocity_d_gain` | u8 = val+128 | ✅ **PHASE 1** |
| +3 | `balance_gain` | u8 = val+128 | ✅ **PHASE 1** |

### 4.2 Receive (Configurator → Firmware)

If `dataSize <= 4`: reads glide_deg + ONDAS v1 triplet (cadence, ferocity_d, balance).
If `dataSize == 1` (legacy): reads only glide_deg — backward compatible.

**Note**: The full servo write path (`dataSize >= 12`) also now reads the ONDAS v1 triplet from the last 3 bytes after the servo records. ✅

---

## 5. MSP_FILTER_CONFIG (92/93) — Legacy cadence_gain

`cadence_gain` is appended as last byte after all filter fields:

```c
sbufWriteU8(dst, (uint8_t)(servoConfigMutable()->cadence_gain + 128));
```

On receive: `sbufReadU8(src) - 128` after the `USE_DYN_LPF` block.

| Condition | Status |
|-----------|--------|
| apiVersion ≥ 1.41, cadence_gain at end of FILTER_CONFIG | ✅ |
| Wire format: u8 = value+128 | ✅ |

---

## 6. MSP_MIXER_CONFIG (42/43) & FC_VARIANT

`MSP_FC_VARIANT` returns `"ORNI"` (4 bytes). Configurator identifies OrniFlight by:
- `apiVersion` matches `1.42.x`
- `fcVariant` equals `"ORNI"`
- Primary protocol gate: `apiVersion >= "1.42.0"` unlocks ONDAS v2 UI

Firmware sends `mixerConfig()->mixerMode` (u8) — value **27** for `MIXER_SERVO_ORNITHOPTER`. Configurator's `mixerList` only has entries 1–26 (Betaflight types). Ornithopter mixer type 27 has no 3D model — configurator feature gap.

---

## 7. MSP_SET_ORNITHOPTER_GLIDE_DEGREE (244)

Handler in <file>msp.c:2631</file> is a no-op. Command exists in protocol but unimplemented. Low priority — glide_deg is accessible via `MSP_SERVO_CONFIGURATIONS`.

---

## 8. Summary: Status Matrix

| # | Severity | Item | Status |
|---|----------|------|--------|
| 1 | 🔴 | `API_VERSION_MINOR` bumped to 42 | ✅ **DONE** |
| 2 | 🔴 | `MSP_PID_ADVANCED` offset 48 (`itermRelaxCutoff`) | ✅ **DONE** |
| 3 | 🔴 | `MSP_PID_ADVANCED` offsets 49–58 (10 ONDAS v2 params) | ✅ **DONE** |
| 4 | 🟠 | `MSP_SERVO_CONFIGURATIONS` ONDAS v1 triplet | ✅ **DONE** |
| 5 | 🟡 | `servo_mount_angle[4]` + `flapping_phase_shift[4]` + 4 advanced params on wire | ✅ **Phase 2** |
| 6 | 🟡 | `MSP_SET_ORNITHOPTER_GLIDE_DEGREE` no-op | 🔲 Legacy |
| 7 | 🔵 | Mixer type 27 not in configurator `mixerList` | 🔲 Cosmetic |
| 8 | 🔵 | ONDAS params in `servoConfig_t`, not `pidProfile_t` — architectural note | ℹ️ |

**Independent mode**: `MSP_PID_ADVANCED` sends/receives **82 bytes**. Phase 4 adds 3 bytes: `independent_freq_channel` (AUX index), `independent_freq_min`, `independent_freq_max`. Mode activation via `BOXORNITHOPTERINDEPENDENT` (RC Modes tab, permanentId 50). apiVersion — 1.45.

---

## 9. Configurator TODO

- [ ] Gate on `apiVersion >= \"1.45.0\"` to unlock Independent mode UI
- [x] `servo_mount_angle[4]`: 4 sliders per pair (–30..+30°), labeled \"Wing Pair 1–4 Incidence\" ✅
- [x] `flapping_phase_shift[4]`: 4 sliders per pair (–180..+180°), labeled \"Wing Pair 1–4 Phase Offset\" ✅
- [x] `prescience_gain`, `espelho_gain`, `saudade_gain`, `ssff_gain`: sliders 0–100 in ONDAS advanced tab ✅
- [x] `servo_speed_deg_s`: slider 100–2000 °/s, label \"Servo Speed\" — controls glide transition rate + max frequency ✅
- [x] `servo_max_amplitude`: slider 20–90°, label \"Max Amplitude\" — hard mechanical clamp ✅
- [x] `flap_magnitude`: slider 1–20, label \"Throttle→Amplitude Gain\" — centi-deg per µs above 1040 ✅
- [x] `wing_origin_offset[4]`: 4 sliders (–30..+30°), label \"Wing Trim Pair 1–4\" — mechanical asymmetry ✅
- [ ] Write `MSP_SET_PID_ADVANCED` at 82 bytes when apiVersion ≥ 1.45; 79 bytes at 1.44; 71 at 1.43; 59 at 1.42; 48 legacy
- [ ] Signed fields: decode `wire_byte - 128` for angles, phase shifts, wing offsets; direct for unsigned 0–100 params
- [ ] `independent_freq_channel`: dropdown AUX1–AUX14, label \"Frequency Channel\" (active only when BOXORNITHOPTERINDEPENDENT present)
- [ ] `independent_freq_min`: slider 1–50 Hz, label \"Frequency at RC Min\"
- [ ] `independent_freq_max`: slider 1–50 Hz, label \"Frequency at RC Max\"

---

## 10. Wire Type Convention Reference

All ONDAS params on the wire are **raw `uint8`** (0–255). Signed fields are transmitted as unsigned byte = value+128. The configurator (and firmware internally) reverses this:

| C Type | Wire | Configurator JS | Conversion |
|--------|------|-----------------|------------|
| `int8_t` (–128..127) | `u8` (0..255) | `read8()` → int | `wire - 128` |
| `uint8_t` (0..255) | `u8` (0..255) | `read8()` → int | direct |
| `int8_t` (0..100 only) | `u8` (0..100) | `read8()` → int | direct (unsigned-safe range) |

Signed fields (cadence_gain, ferocity_d_gain, balance_gain, warp_gain, warp_yaw_gain): wire byte = value + 128.
Unsigned-but-int8 fields (ferocity_p_gain, ferocity_roll_gain, ferocity_yaw_gain, anchor_gain, resonance_gain): direct wire pass-through (values 0–100, safe in u8).