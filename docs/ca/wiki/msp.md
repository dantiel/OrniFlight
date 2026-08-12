# MSP Protocol

> *MultiWii Protocol de sèrie — com el configurador parla amb OrniFlight.*

## Visió general

OrniFlight amplia el Betaflight MSP amb missatges específics d'ornitòpters. L'especificació autoritzada viu al dipòsit de microprogramari a `src/main/msp/`.

**Versió actual:** apiVersion 1.46 (OrniFlight v0.4.6)

## Missatges clau

### MSP_PID_ADVANCED (112/0x70)

El missatge principal de sintonització de ONDAS. Ha crescut de 48 bytes (legat) a 87 bytes (1,46).

| API Versió | Mida | Nous continguts |
|--------------|------|--------------|
| 1,33 | 48 | Llegat PID avançat |
| 1,42 | 59 | + itermRelaxCutoff, 10 guanys ONDAS v2 |
| 1,43 | 71 | + servo_mount_angle[4], phase_shift[4], prescience, espelho, saudade, ssff |
| 1,44 | 75 | + servo_speed, max_amplitude, flap_magnitude, wing_origin_offset[4] |
| 1,45 | 82 | + freq_channel, freq_min_hz, freq_max_hz, flight_mode, flutter_gain, flutter_hz, throttle_bypass |
| 1,46 | 87 | + profile_index, ferocity_downstroke, ferocity_downstroke, aeroelastic_glide, aeroelastic_flap |

### MSP_SERVO_CONFIGURATIONS (120/0x78)

Configuració del servo amb 4 bytes al final ONDAS: glide_deg + triplet ONDAS v1.

## Compatibilitat enrere

Totes les versions de API són compatibles amb versions anteriors. Un remitent de 48 bytes parla amb un receptor d'1,46 — camps addicionals per defecte a valors sensatis.

## Format de cable

Tots els valors de diversos bytes són little-endians. Valors signats emmagatzemats com a `value + 128` al cable. Els valors de guany sense signe (0–100) són directes. Les longituds de matriu precedides per u8 compten.

---

*Vegeu `docs/MSP_FIRMWARE_INTERFACE.md` al repositori de microprogramari per obtenir l'especificació completa.*