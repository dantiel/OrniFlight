#MSPProtocollo

> *MultiWii Protocollo seriale — come il Configuratore comunica con OrniFlight.*

## Panoramica

OrniFlight estende Betaflight MSP con messaggi specifici degli ornitotteri. La specifica autorevole si trova nel repository del firmware su `src/main/msp/`.

**Versione corrente:** apiVersion 1.46 (OrniFlight v0.4.6)

## Messaggi chiave

### MSP_PID_ADVANCED (112/0x70)

Il messaggio principale di sintonizzazione ONDAS. Cresciuto da 48 byte (legacy) a 87 byte (1,46).

| API Versione | Taglia | Nuovi contenuti |
|-------------|------|-----|
| 1.33| 48| Legacy PID avanzato |
| 1.42| 59| + itermRelaxCutoff, 10 guadagni ONDAS v2 |
| 1.43| 71| + servo_mount_angle[4],phase_shift[4], prescience, espelho, saudade, ssff |
| 1.44| 75| + velocità_servo, ampiezza_max, magnitudine_flap, offset_origine_ala[4] |
| 1,45| 82| + freq_channel, freq_min_hz, freq_max_hz, flight_mode, flutter_gain, flutter_hz, Throttle_bypass |
| 1.46| 87| + profile_index, ferocia_downstroke, ferocia_upstroke, aeroelastic_glide, aeroelastic_flap |

### MSP_SERVO_CONFIGURATIONS (120/0x78)

Configurazione servo con 4 byte finali ONDAS: glide_deg + ONDAS v1 tripletta.

## Compatibilità con le versioni precedenti

Tutte le versioni API sono compatibili con le versioni precedenti. Un mittente da 48 byte comunica con un ricevitore da 1,46 — i campi aggiuntivi sono impostati su valori ragionevoli.

## Formato filo

Tutti i valori multibyte sono little-endian. Valori con segno memorizzati come `value + 128` sul cavo. I valori di guadagno senza segno (0–100) sono diretti. Lunghezze degli array precedute dal conteggio u8.

---

*Vedi `docs/MSP_FIRMWARE_INTERFACE.md` nel repository del firmware per le specifiche complete.*