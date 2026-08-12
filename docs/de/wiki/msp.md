# MSP Protokoll

> *MultiWii Serielles Protokoll — wie der Konfigurator mit OrniFlight kommuniziert.*

## Übersicht

OrniFlight erweitert den Betaflight MSP um Ornithopter-spezifische Nachrichten. Die maßgebliche Spezifikation befindet sich im Firmware-Repository unter `src/main/msp/`.

**Aktuelle Version:** apiVersion 1.46 (OrniFlight v0.4.6)

## Kernbotschaften

### MSP_PID_ADVANCED (112 / 0x70)

Die Haupt-Tuning-Nachricht von ONDAS. Von 48 Byte (Legacy) auf 87 Byte (1,46) gewachsen.

| API-Version | Größe | Neue Inhalte |
|-------------|------|-------------|
| 1,33 | 48 | Legacy PID erweitert |
| 1,42 | 59 | + itermRelaxCutoff, 10 ONDAS v2 Gewinne |
| 1,43 | 71 | + servo_mount_angle[4], phase_shift[4], prescience, espelho, saudade, ssff |
| 1,44 | 75 | + servo_speed, max_amplitude, Flap_magnitude, Wing_origin_offset[4] |
| 1,45 | 82 | + freq_channel, freq_min_hz, freq_max_hz, Flight_mode, flutter_gain, flutter_hz, Throttle_bypass |
| 1,46 | 87 | + Profile_index, Ferocity_DownStroke, Ferocity_UpStroke, aeroelastic_glide, aeroelastic_flap |

### MSP_SERVO_CONFIGURATIONS (120 / 0x78)

Servokonfiguration mit 4 ONDAS-Trailing-Bytes: glide_deg + ONDAS v1-Triplett.

## Abwärtskompatibilität

Alle API-Versionen sind abwärtskompatibel. Ein 48-Byte-Sender kommuniziert mit einem 1,46-Byte-Empfänger. Die zusätzlichen —-Felder werden standardmäßig auf sinnvolle Werte gesetzt.

## Drahtformat

Alle Multibyte-Werte sind Little-Endian. Vorzeichenbehaftete Werte werden als `value + 128` auf der Leitung gespeichert. Vorzeichenlose Verstärkungswerte (0–100) sind direkt. Array-Längen, denen u8 vorangestellt ist, zählen.

---

*Die vollständige Spezifikation finden Sie unter `docs/MSP_FIRMWARE_INTERFACE.md` im Firmware-Repository.*