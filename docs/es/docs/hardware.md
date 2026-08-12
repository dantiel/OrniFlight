# Hardware soportado

OrniFlight se ejecuta en controladores de vuelo básicos STM32F3/F4/F7. La línea de base es **STM32F3** —. Cualquier objetivo F3 con pines de temporizador con capacidad servo volará.

## Controladores de vuelo

| tablero | MCU | IMU | Destello | Receptor | Estado |
|-------|-----|-----|-------|----------|--------|
| **TINYFISH** | STM32F303 | MPU6000 (SPI) | 256 KB | FrSky D8 (integrado) | ✅ Primaria |
| **OMNIBUSF4** | STM32F405 | MPU6000 (SPI) | 1 MB + 16 MB SPI | — | ✅ Compatible |

### TINYFISH — El objetivo OrniFlight más ligero

Diseñado por Fishpepper, TINYFISH es el controlador de vuelo de ornitóptero ideal: peso pluma, basado en F3 y que lleva un **receptor FrSky D8 integrado** a bordo. Sin RX externo, sin cableado adicional —, solo energía, servos y vuelo.

- **MCU**: STM32F303CCT6 @ 72MHz
- **Giroscopio**: MPU6000 (SPI, capacidad de 8 kHz)
- **Flash**: 256 KB en chip
- **RAM**: 40 KB
- **Receptor**: FrSky D8 integrado (SBUS enrutado internamente a UART2)
- **UART**: VCP + 2 UART de hardware (UART1 gratis para el complemento GPS/CRSF)
- **Entrada**: 2-4S LiPo (servopotencia directa)
- **Peso**: ~2,5 g

TINYFISH demuestra que el control de aleteo trascendente no necesita un F7. El STM32F303 ejecuta toda la tubería ONDAS — 10 canales de modulación, ala trapezoidal ODE, 4 perfiles de vuelo — dentro de 256 KB.

### OMNIBUSF4 — El caballo de batalla accesible

El clásico objetivo F4. Barato, ubicuo, con todas las funciones con OSD y amplio flash SPI para registro de Blackbox. La opción ideal para desarrollos y construcciones más grandes.

- **MCU**: STM32F405RGT6 @ 168MHz
- **Gyro**: MPU6000 (SPI, capacidad de 8 kHz)
- **Flash**: 1 MB en chip + 16 MB SPI (Caja negra)
- **RAM**: 192 KB
- **OSD**: AT7456E (compatible con MAX7456)
- **UART**: VCP + 5 UART de hardware
- **Barómetro**: BMP280 (algunas variantes)
- **Entrada**: 2-6S LiPo

---

## Anatomía del ornitóptero

### Servos de ala

Los controles OrniFlight se mueven a través de los servos PWM. Especificaciones clave:

| Parámetro | Rango típico |
|-----------|--------------|
| Ancho de pulso | 500–2500 µs |
| Centro | 1500 µs |
| Frecuencia | 50–330Hz |
| Ángulo de carrera | ±15–45° |

Para ornitópteros de alto rendimiento, se recomiendan servos digitales con velocidad de actualización de 330 Hz. Los servos analógicos funcionan a 50 Hz pero tienen menor precisión.

### Receptor

Se admite cualquier protocolo de receptor serie. CRSF (TBS Crossfire / ExpressLRS) se recomienda para:
- Baja latencia (crítica para el control del aleteo)
- Telemetría incorporada
- RSSI sobre protocolo (sin cableado adicional)

### Batería

- **2S (7.4V)**: Ornitópteros pequeños, servoalimentados directamente
- **3S (11.1V)**: Ornitópteros medianos, se requiere BEC para los servos
- **4S (14.8V)**: Ornitópteros grandes, se recomienda BEC externos

---

## Periféricos compatibles

| Periférico | Vía | Notas |
|-----------|-----|-------|
| GPS | UART | UBlox M8N o compatible |
| VTX | UART TX | Vagabundo, SmartAudio |
| Cámara | — | Cualquier cámara analógica FPV |
| Zumbador | almohadilla BUZZ | Zumbador activo de 5V |
| LED Tira | almohadilla LED | WS2812 / SK6812 |
| OpenLog | UART TX | Registro de caja negra |
| Bluetooth | UART | paso MSP para tuning móvil |

---

## Objetivos futuros

OrniFlight tiene como objetivo admitir objetivos STM32F4/F7 adicionales donde haya suficientes recursos UART y temporizador disponibles para el control del servo de aleteo. Se aceptan contribuciones.