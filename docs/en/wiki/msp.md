# MSP Protocol

> *MultiWii Serial Protocol — how the Configurator talks to OrniFlight.*

## Overview

OrniFlight extends the Betaflight MSP with ornithopter-specific messages. The authoritative specification lives in the firmware repository at `src/main/msp/`.

**Current version:** apiVersion 1.46 (OrniFlight v0.4.6)

## Key Messages

### MSP_PID_ADVANCED (112 / 0x70)

The main ONDAS tuning message. Grown from 48 bytes (legacy) to 87 bytes (1.46).

| API Version | Size | New Contents |
|-------------|------|-------------|
| 1.33 | 48 | Legacy PID advanced |
| 1.42 | 59 | + itermRelaxCutoff, 10 ONDAS v2 gains |
| 1.43 | 71 | + servo_mount_angle[4], phase_shift[4], prescience, espelho, saudade, ssff |
| 1.44 | 75 | + servo_speed, max_amplitude, flap_magnitude, wing_origin_offset[4] |
| 1.45 | 82 | + freq_channel, freq_min_hz, freq_max_hz, flight_mode, flutter_gain, flutter_hz, throttle_bypass |
| 1.46 | 87 | + profile_index, ferocity_downstroke, ferocity_upstroke, aeroelastic_glide, aeroelastic_flap |

### MSP_SERVO_CONFIGURATIONS (120 / 0x78)

Servo configuration with 4 ONDAS trailing bytes: glide_deg + ONDAS v1 triplet.

## Backward Compatibility

All API versions are backward-compatible. A 48-byte sender talks to a 1.46 receiver — extra fields default to sensible values.

## Wire Format

All multi-byte values are little-endian. Signed values stored as `value + 128` on the wire. Unsigned gain values (0–100) are direct. Array lengths preceded by u8 count.

---

*See `docs/MSP_FIRMWARE_INTERFACE.md` in the firmware repository for the complete specification.*
