# MSP protokols

> *MultiWii seriālais protokols — kā konfigurators runā ar OrniFlight.*

## Pārskats

OrniFlight paplašina Betaflight MSP ar ornitopteram raksturīgiem ziņojumiem. Autoritatīvā specifikācija atrodas programmaparatūras repozitorijā `src/main/msp/`.

**Pašreizējā versija:** apiVersion 1.46 (OrniFlight v0.4.6)

## Galvenie ziņojumi

### MSP_PID_ADVANCED (112/0x70)

Galvenais ONDAS skaņošanas ziņojums. Pieaudzis no 48 baitiem (mantots) līdz 87 baitiem (1,46).

| API Versija | Izmērs | Jauns saturs |
|-------------|------|--------------|
| 1,33 | 48 | Mantojums PID uzlabots |
| 1,42 | 59 | + itermRelaxCutoff, 10 ONDAS v2 ieguvumi |
| 1,43 | 71 | + servo_mount_angle[4], phase_shift[4], prescience, espelho, saudade, ssff |
| 1,44 | 75 | + servo_ātrums, maksimālā_amplitūda, flap_magnitude, wing_origin_offset[4] |
| 1,45 | 82 | + Freq_channel, Freq_min_hz, Freq_max_hz, flight_mode, flutter_gain, flutter_hz, throttle_bypass |
| 1,46 | 87 | + profila_indekss, ferocity_downstroke, ferocity_upstroke, aeroelastic_glide, aeroeastic_flap |

### MSP_SERVO_CONFIGURATIONS (120/0x78)

Servo konfigurācija ar 4 ONDAS beigu baitiem: glide_deg + ONDAS v1 triplets.

## Atgriezeniskā saderība

Visas API versijas ir saderīgas ar atpakaļejošu datumu. 48 baitu sūtītājs runā ar 1,46 uztvērēju. — papildu lauki pēc noklusējuma ir saprātīgi.

## Vadu formāts

Visas vairāku baitu vērtības ir mazas. Parakstītās vērtības, kas tiek saglabātas kā `value + 128` uz vada. Neparakstītas pastiprinājuma vērtības (0–100) ir tiešas. Masīvu garumi, pirms kuriem ir u8, tiek skaitīti.

---

* Pilnu specifikāciju skatiet programmaparatūras repozitorijā `docs/MSP_FIRMWARE_INTERFACE.md`.*