Protocolo #MSP

> *MultiWii Protocolo de serie — como fala o configurador con OrniFlight.*

## Visión xeral

OrniFlight amplía o Betaflight MSP con mensaxes específicas de ornitópteros. A especificación autorizada reside no repositorio de firmware en `src/main/msp/`.

**Versión actual:** apiVersion 1.46 (OrniFlight v0.4.6)

## Mensaxes clave

### MSP_PID_ADVANCED (112/0x70)

A mensaxe principal de sintonía ONDAS. Pasou de 48 bytes (herdado) a 87 bytes (1,46).

| API Versión | Tamaño | Novos Contidos |
|--------------|------|--------------|
| 1,33 | 48 | Legado PID avanzado |
| 1,42 | 59 | + itermRelaxCutoff, 10 ganancias ONDAS v2 |
| 1,43 | 71 | + servo_mount_angle[4], phase_shift[4], prescience, espelho, saudade, ssff |
| 1,44 | 75 | + servo_speed, max_amplitude, flap_magnitude, wing_origin_offset[4] |
| 1,45 | 82 | + freq_channel, freq_min_hz, freq_max_hz, flight_mode, flutter_gain, flutter_hz, throttle_bypass |
| 1,46 | 87 | + índice_perfil, trazo_abaixo_feroz, trazo_ascendente_feroz, deslizamento_aeroelástico, solapa_aeroelástica |

### MSP_SERVO_CONFIGURATIONS (120/0x78)

Configuración do servo con 4 bytes de final ONDAS: glide_deg + triplete ONDAS v1.

## Compatibilidade con versións anteriores

Todas as versións de API son compatibles con versións anteriores. Un remitente de 48 bytes fala cun receptor de 1,46 — campos adicionais por defecto a valores sensatos.

## Formato de cable

Todos os valores de varios bytes son little-endian. Valores asinados almacenados como `value + 128` no cable. Os valores de ganancia sen asinar (0–100) son directos. Lonxitudes de matriz precedidas de conta u8.

---

*Consulte `docs/MSP_FIRMWARE_INTERFACE.md` no repositorio de firmware para ver a especificación completa.*