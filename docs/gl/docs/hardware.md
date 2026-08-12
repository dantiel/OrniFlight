# Hardware compatible

OrniFlight funciona con controladores de voo STM32F3/F4/F7. A liña de base é **STM32F3** — calquera obxectivo F3 con pinos de temporizador con capacidade de servo voará.

## Controladores de voo

| Xunta | MCU | IMU | Flash | Receptor | Estado |
|-------|-----|-----|-------|--------------------|
| **TINYFISH** | STM32F303 | MPU6000 (SPI) | 256 KB | FrSky D8 (integrado) | ✅ Primaria |
| **OMNIBUSF4** | STM32F405 | MPU6000 (SPI) | 1 MB + 16 MB SPI | — | ✅ Compatible |

### TINYFISH — O obxectivo OrniFlight máis lixeiro

Deseñado por fishpepper, TINYFISH é o controlador de voo ornitóptero ideal: peso pluma, baseado en F3 e que leva un **receptor FrSky D8 integrado** a bordo. Sen RX externo, sen cableado adicional — só alimentación, servos e voar.

- **MCU**: STM32F303CCT6 @ 72 MHz
- **Gyro**: MPU6000 (SPI, capaz de 8 kHz)
- **Flash**: 256 KB no chip
- **RAM**: 40 KB
- **Receptor**: FrSky D8 integrado (SBUS enrutado internamente a UART2)
- **UART**: VCP + 2 UART de hardware (UART1 gratuíto para o complemento GPS/CRSF)
- **Entrada**: 2-4S LiPo (potencia servo directo)
- **Peso**: ~2,5 g

TINYFISH demostra que o control de aleteo trascendente non precisa un F7. O STM32F303 executa a canalización completa ONDAS — 10 canles de modulación, ala trapezoidal ODE, 4 perfís de voo — dentro de 256 KB.

### OMNIBUSF4 — O cabalo de batalla accesible

O branco clásico F4. Barato, omnipresente, con todas as funcións con OSD e un amplo flash SPI para o rexistro de Blackbox. O ideal para o desenvolvemento e as construcións máis grandes.

- **MCU**: STM32F405RGT6 @ 168 MHz
- **Gyro**: MPU6000 (SPI, capaz de 8 kHz)
- **Flash**: 1 MB no chip + 16 MB SPI (Blackbox)
- **RAM**: 192 KB
- **OSD**: AT7456E (compatible con MAX7456)
- **UART**: VCP + 5 UART de hardware
- **Barómetro**: BMP280 (algunhas variantes)
- **Entrada**: 2-6S LiPo

---

## Anatomía de ornitópteros

### Servos de Á

Os controis OrniFlight pasan a través dos servos PWM. Especificacións clave:

| Parámetro | Rango típico |
|-----------|--------------|
| Ancho de pulso | 500–2500 µs |
| Centro | 1500 µs |
| Frecuencia | 50–330 Hz |
| Ángulo de trazo | ±15–45° |

Para ornitópteros de alto rendemento, recoméndanse servos dixitais cunha taxa de actualización de 330 Hz. Os servos analóxicos funcionan a 50 Hz pero teñen menor precisión.

### Receptor

Admite calquera protocolo de receptor en serie. CRSF (TBS Crossfire / ExpressLRS) recoméndase para:
- Baixa latencia (crítico para o control do aleteo)
- Telemetría incorporada
- RSSI sobre protocolo (sen cableado adicional)

### Batería

- **2S (7,4V)**: ornitópteros pequenos, servoalimentados directamente
- **3S (11,1 V)**: ornitópteros medianos, BEC necesario para servos
- **4S (14,8 V)**: ornitópteros grandes, recomendado BEC externo

---

## Periféricos compatibles

| Periférico | Vía | Notas |
|-----------|-----|-------|
| GPS | UART | UBlox M8N ou compatible |
| VTX | UART TX | Vagabundo, SmartAudio |
| Cámara | — | Calquera cámara analóxica FPV |
| Zumbador | BUZZ pad | Zumbador activo de 5 V |
| LED Tira | LED pad | WS2812 / SK6812 |
| OpenLog | UART TX | rexistro de caixa negra |
| Bluetooth | UART | MSP paso para a sintonización móbil |

---

## Obxectivos futuros

OrniFlight ten como obxectivo admitir obxectivos STM32F4/F7 adicionais nos que hai suficientes recursos UART e temporizadores dispoñibles para o control do servo de aleteo. Benvidas achegas.