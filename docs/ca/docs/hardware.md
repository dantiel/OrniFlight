# Maquinari compatible

OrniFlight funciona amb controladors de vol STM32F3/F4/F7. La línia de base és **STM32F3** — qualsevol objectiu F3 amb agulles de temporitzador amb servomotor volarà.

## Controladors de vol

| Junta | MCU | IMU | Flash | Receptor | Estat |
|-------|-----|-----|-------|----------|--------|
| **TINYFISH** | STM32F303 | MPU6000 (SPI) | 256 KB | FrSky D8 (integrat) | ✅ Primària |
| **OMNIBUSF4** | STM32F405 | MPU6000 (SPI) | 1 MB + 16 MB SPI | — | ✅ Admet |

### TINYFISH — L'objectiu OrniFlight més lleuger

Dissenyat per fishpepper, TINYFISH és el controlador de vol ornitòpter ideal: pes ploma, basat en F3 i que porta un **receptor FrSky D8 integrat** a bord. Sense RX extern, sense cablejat addicional — només potència, servos i volar.

- **MCU**: STM32F303CCT6 @ 72 MHz
- **Gyro**: MPU6000 (SPI, capaç de 8 kHz)
- **Flash**: 256 KB al xip
- **RAM**: 40 KB
- **Receptor**: FrSky D8 integrat (SBUS encaminat internament a UART2)
- **UART**: VCP + 2 UART de maquinari (UART1 gratuït per al complement GPS/CRSF)
- **Entrada**: 2-4S LiPo (potència servo directa)
- **Pes**: ~2,5 g

TINYFISH demostra que el control transcendent d'aleteig no necessita un F7. El STM32F303 executa la canalització completa ONDAS — 10 canals de modulació, ala trapezoïdal ODE, 4 perfils de vol — dins de 256 KB.

### OMNIBUSF4 — El cavall de batalla accessible

L'objectiu clàssic F4. Barat, omnipresent, amb totes les funcions amb OSD i un ampli flash SPI per al registre de Blackbox. El favorit per al desenvolupament i les construccions més grans.

- **MCU**: STM32F405RGT6 @ 168 MHz
- **Gyro**: MPU6000 (SPI, capacitat de 8 kHz)
- **Flash**: 1 MB al xip + 16 MB SPI (Blackbox)
- **RAM**: 192 KB
- **OSD**: AT7456E (compatible amb MAX7456)
- **UART**: VCP + 5 UART de maquinari
- **Baròmetre**: BMP280 (algunes variants)
- **Entrada**: 2-6S LiPo

---

## Anatomia de l'ornitòpter

### Servos d'ala

OrniFlight controla el moviment dels servos PWM. Especificacions clau:

| Paràmetre | Gamma típica |
|-----------|---------------|
| Amplada del pols | 500–2500 µs |
| Centre | 1500 µs |
| Freqüència | 50–330 Hz |
| Angle de traç | ±15–45° |

Per als ornitòpters d'alt rendiment, es recomanen servos digitals amb una velocitat d'actualització de 330 Hz. Els servos analògics funcionen a 50 Hz però tenen una precisió menor.

### Receptor

S'admet qualsevol protocol de receptor sèrie. Es recomana CRSF (TBS Crossfire / ExpressLRS) per a:
- Baixa latència (crític per al control de flapping)
- Telemetria integrada
- RSSI sobre protocol (sense cablejat addicional)

### Bateria

- **2S (7.4V)**: ornitòpters petits, servoalimentats directament
- **3S (11,1 V)**: ornitòpters mitjans, cal BEC per als servos
- **4S (14,8 V)**: ornitòpters grans, es recomana BEC extern

---

## Perifèrics compatibles

| Perifèric | Via | Notes |
|-----------|-----|-------|
| GPS | UART | UBlox M8N o compatible |
| VTX | UART TX | Vagabund, SmartAudio |
| Càmera | — | Qualsevol càmera analògica FPV |
| Zumbador | BUZZ coixinet | Zumbador actiu de 5V |
| LED Tira | LED coixinet | WS2812 / SK6812 |
| OpenLog | UART TX | Registre de Blackbox |
| Bluetooth | UART | Passthrough MSP per a la sintonització mòbil |

---

## Objectius futurs

OrniFlight té com a objectiu donar suport a objectius STM32F4/F7 addicionals on hi hagi suficients recursos UART i temporitzadors per al control del servo de flapping. Benvingudes aportacions.