# protocolo MSP

> *MultiWii Protocolo serie — cómo el Configurador habla con OrniFlight.*

## Descripción general

OrniFlight amplía Betaflight MSP con mensajes específicos de ornitópteros. La especificación autorizada se encuentra en el repositorio de firmware en `src/main/msp/`.

**Versión actual:** apiVersion 1.46 (OrniFlight v0.4.6)

## Mensajes clave

### MSP_PID_ADVANCED (112/0x70)

El mensaje principal de sintonización de ONDAS. Aumentó de 48 bytes (heredado) a 87 bytes (1.46).

| Versión API | Tamaño | Nuevos contenidos |
|-------------|------|-------------|
| 1,33 | 48 | Legado PID avanzado |
| 1,42 | 59 | + itermRelaxCutoff, 10 ganancias ONDAS v2 |
| 1,43 | 71 | + servo_mount_angle[4], Phase_shift[4], presciencia, espelho, saudade, ssff |
| 1,44 | 75 | + servo_speed, max_amplitude, flap_magnitude, wing_origin_offset[4] |
| 1,45 | 82 | + freq_channel, freq_min_hz, freq_max_hz, modo de vuelo, flutter_gain, flutter_hz, throttle_bypass |
| 1,46 | 87 | + perfil_index, ferocity_downstroke, ferocity_upstroke, aeroelastic_glide, aeroelastic_flap |

### MSP_SERVO_CONFIGURATIONS (120/0x78)

Configuración de servo con 4 bytes finales ONDAS: glide_deg + triplete ONDAS v1.

## Compatibilidad con versiones anteriores

Todas las versiones de API son compatibles con versiones anteriores. Un remitente de 48 bytes habla con un receptor de 1,46 —. Los campos adicionales tienen valores razonables por defecto.

## Formato de cable

Todos los valores de varios bytes son little-endian. Valores con signo almacenados como `value + 128` en el cable. Los valores de ganancia sin signo (0–100) son directos. Longitudes de matriz precedidas por el recuento u8.

---

*Consulte `docs/MSP_FIRMWARE_INTERFACE.md` en el repositorio de firmware para conocer las especificaciones completas.*