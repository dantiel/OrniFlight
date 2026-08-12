# MSP protokol

> *MultiWii serijski protokol — kako konfigurator razgovara sa OrniFlight.*

## Pregled

OrniFlight proširuje Betaflight MSP porukama specifičnim za ornitoptere. Mjerodavna specifikacija nalazi se u repozitoriju firmvera na adresi `src/main/msp/`.

**Trenutna verzija:** apiVerzija 1.46 (OrniFlight v0.4.6)

## Ključne poruke

### MSP_PID_ADVANCED (112 / 0x70)

Glavna poruka o ugađanju ONDAS. Povećano s 48 bajtova (naslijeđeno) na 87 bajtova (1,46).

| API verzija | Veličina | Novi sadržaji |
|-------------|------|-------------|
| 1.33 | 48 | Naslijeđe PID napredno |
| 1.42 | 59 | + itermRelaxCutoff, 10 ONDAS v2 dobitaka |
| 1.43 | 71 | + servo_mount_angle[4], phase_shift[4], predviđanje, espelho, saudade, ssff |
| 1,44 | 75 | + servo_brzina, maksimalna_amplituda, veličina_zakrilca, pomak_početka_krila[4] |
| 1,45 | 82 | + freq_channel, freq_min_hz, freq_max_hz, flight_mode, flutter_gain, flutter_hz, throttle_bypass |
| 1,46 | 87 | + profile_index, ferocity_downstroke, ferocity_upstroke, aeroelastic_glide, aeroelastic_flap |

### MSP_SERVO_CONFIGURATIONS (120 / 0x78)

Servo konfiguracija s 4 ONDAS zadnja bajta: glide_deg + ONDAS v1 triplet.

## Kompatibilnost sa prethodnim verzijama

Sve verzije API kompatibilne su s prethodnim verzijama. 48-bajtni pošiljatelj razgovara s 1.46 primateljem — dodatna polja su zadana na razumne vrijednosti.

## Format žice

Sve višebajtne vrijednosti su little-endian. Vrijednosti s predznakom pohranjene kao `value + 128` na žici. Nepredznačene vrijednosti pojačanja (0–100) su izravne. Broj duljina nizova ispred kojih stoji u8.

---

*Pogledajte `docs/MSP_FIRMWARE_INTERFACE.md` u repozitoriju firmvera za potpunu specifikaciju.*