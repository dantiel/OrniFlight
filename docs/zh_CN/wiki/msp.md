# MSP 协议

> *MultiWii Serial Protocol — how the Configurator talks to OrniFlight.*

## 概述

OrniFlight 通过扑翼机特定消息扩展了 Betaflight MSP。 The authoritative specification lives in the firmware repository at `src/main/msp/`.

**Current version:** apiVersion 1.46 (OrniFlight v0.4.6)

## 关键信息

### MSP_PID_ADVANCED (112 / 0x70)

主要 ONDAS 调整消息。从 48 字节（旧版）增长到 87 字节 (1.46)。

| API 版本 |尺寸|新内容 |
|-------------|---------|-------------|
| 1.33 | 1.33 48 | 48旧版 PID 高级 |
| 1.42 | 1.42 59 | 59 + itermRelaxCutoff，10 ONDAS v2 增益 |
| 1.43 | 1.43 71 | 71 + servo_mount_angle[4], phase_shift[4], prescience, espelho, saudade, ssff |
| 1.44 | 1.44 75 | 75 + servo_speed, max_amplitude, flap_magnitude, wing_origin_offset[4] |
| 1.45 | 1.45 82 | 82 + freq_channel, freq_min_hz, freq_max_hz, flight_mode, flutter_gain, flutter_hz, throttle_bypass |
| 1.46 | 1.46 87 | 87 + profile_index, ferocity_downstroke, ferocity_upstroke, aeroelastic_glide, aeroelastic_flap |

### MSP_SERVO_CONFIGURATIONS (120 / 0x78)

Servo configuration with 4 ONDAS trailing bytes: glide_deg + ONDAS v1 triplet.

## 向后兼容性

所有 API 版本均向后兼容。 A 48-byte sender talks to a 1.46 receiver — extra fields default to sensible values.

## 电汇格式

所有多字节值都是小端字节序。有符号值在线路上存储为 `value + 128`。无符号增益值 (0–100) 是直接的。数组长度前面带有 u8 计数。

---

*请参阅固件存储库中的 `docs/MSP_FIRMWARE_INTERFACE.md` 了解完整规范。*