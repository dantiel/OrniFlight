# MSP-protokoll

> *MultiWii seriellt protokoll — hur konfiguratorn pratar med OrniFlight.*

## Översikt

OrniFlight utökar Betaflight MSP med ornithopter-specifika meddelanden. Den auktoritativa specifikationen finns i firmware-förrådet på `src/main/msp/`.

**Aktuell version:** apiVersion 1.46 (OrniFlight v0.4.6)

## Nyckelmeddelanden

### MSP_PID_ADVANCED (112 / 0x70)

Det huvudsakliga ONDAS-inställningsmeddelandet. Växt från 48 byte (legacy) till 87 byte (1,46).

| API Version | Storlek | Nytt innehåll |
|-------------|------|------------|
| 1,33 | 48 | Legacy PID avancerad |
| 1,42 | 59 | + itermRelaxCutoff, 10 ONDAS v2 vinster |
| 1,43 | 71 | + servo_mount_angle[4], phase_shift[4], prescience, espelho, saudade, ssff |
| 1,44 | 75 | + servo_hastighet, max_amplitud, flap_magnitude, wing_origin_offset[4] |
| 1,45 | 82 | + freq_channel, freq_min_hz, freq_max_hz, flight_mode, flutter_gain, flutter_hz, throttle_bypass |
| 1,46 | 87 | + profile_index, ferocity_downstroke, ferocity_upstroke, aeroelastic_glide, aeroelastic_flap |

### MSP_SERVO_CONFIGURATIONS (120 / 0x78)

Servokonfiguration med 4 ONDAS efterföljande byte: glide_deg + ONDAS v1 triplett.

## Bakåtkompatibilitet

Alla API-versioner är bakåtkompatibla. En 48-byte avsändare pratar med en 1,46 mottagare. — extra fält har som standard vettiga värden.

## Trådformat

Alla multi-byte-värden är little-endian. Signerade värden lagrade som `value + 128` på tråden. Osignerade förstärkningsvärden (0–100) är direkta. Arraylängder som föregås av u8 räknas.

---

*Se `docs/MSP_FIRMWARE_INTERFACE.md` i firmware-arkivet för den fullständiga specifikationen.*