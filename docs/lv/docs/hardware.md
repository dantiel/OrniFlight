# Atbalstītā aparatūra

OrniFlight darbojas ar preču STM32F3/F4/F7 lidojumu kontrolieriem. Bāzes līnija ir **STM32F3** —. Jebkurš F3 mērķis ar taimera tapām ar servospējām lidos.

## Lidojuma kontrolieri

| Valde | MCU | IMU | Zibspuldze | Uztvērējs | Statuss |
|-------|-----|-----|-------|----------|--------|
| **TINYFISH** | STM32F303 | MPU6000 (SPI) | 256 KB | FrSky D8 (integrēts) | ✅ Primārais |
| **OMNIBUSF4** | STM32F405 | MPU6000 (SPI) | 1 MB + 16 MB SPI | — | ✅ Atbalstīts |

### TINYFISH — Vieglākais OrniFlight mērķis

Fishpepper izstrādātais TINYFISH ir ideāls ornitoptera lidojuma kontrolieris: spalvu svars, uz F3 balstīts un ar **integrētu FrSky D8 uztvērēju**. Nav ārēju RX, bez papildu vadu —, tikai jauda, ​​servo un lidojums.

- **MCU**: STM32F303CCT6 @ 72 MHz
- **Gyro**: MPU6000 (SPI, var 8 kHz)
- **Flash**: 256 KB mikroshēmā
- **RAM**: 40 KB
- **Uztvērējs**: integrēts FrSky D8 (SBUS iekšēji maršrutēts uz UART2)
- **UART**: VCP + 2 aparatūras UART (UART1 bez maksas GPS/CRSF papildinājumam)
- **Ieeja**: 2-4S LiPo (tiešā servo jauda)
- **Svars**: ~2,5 g

TINYFISH pierāda, ka pārpasaulīgai plivināšanas kontrolei nav nepieciešama F7. Zzz73zzz vada pilnu ONDAS cauruļvadu — 10 modulācijas kanālus, trapecveida spārnu ODE, 4 lidojuma profilus — 256 KB robežās.

### OMNIBUSF4 — Pieejamais darba zirgs

Klasiskais F4 mērķis. Lēti, visuresoši, pilnvērtīgi ar OSD un plašu SPI zibspuldzi Blackbox reģistrēšanai. Izstrādes un lielākām būvēm paredzētais risinājums.

- **MCU**: STM32F405RGT6 @ 168 MHz
- **Gyro**: MPU6000 (SPI, var 8 kHz)
- **Flash**: 1 MB mikroshēma + 16 MB SPI (Blackbox)
- **RAM**: 192 KB
- **OSD**: AT7456E (saderīgs ar MAX7456)
- **UART**: VCP + 5 aparatūras UART
- **Barometrs**: BMP280 (daži varianti)
- **Ievade**: 2-6S LiPo

---

## Ornitoptera anatomija

### Spārnu servo

OrniFlight kontrolē PWM servo. Galvenās specifikācijas:

| Parametrs | Tipisks diapazons |
|-----------|--------------|
| Impulsa platums | 500–2500 µ |
| Centrs | 1500 µs |
| Biežums | 50–330 Hz |
| Gājiena leņķis | ±15–45° |

Augstas veiktspējas ornitopteriem ir ieteicami digitālie servo ar 330 Hz atjaunināšanas ātrumu. Analogie servo darbojas ar 50 Hz, bet tiem ir zemāka precizitāte.

### Uztvērējs

Tiek atbalstīts jebkurš seriālā uztvērēja protokols. CRSF (TBS Crossfire / ExpressLRS) ir ieteicams:
- Zems latentums (būtisks, lai kontrolētu viļņus)
- Iebūvēta telemetrija
- RSSI, izmantojot protokolu (bez papildu vadu)

### Akumulators

- **2S (7,4 V)**: mazi ornitopteri ar tiešu servo barošanu
- **3S (11,1 V)**: vidēji ornitopteri, BEC nepieciešami servo
- **4S (14,8 V)**: lieli ornitopteri, ieteicami ārējie BEC

---

## Atbalstītās perifērijas ierīces

| Perifērijas | Izmantojot | Piezīmes |
|-----------|-----|-------|
| GPS | UART | UBlox M8N vai saderīgs |
| VTX | UART TX | Tramps, SmartAudio |
| Kamera | — | Jebkura analogā FPV kamera |
| Zummers | BUZZ pad | Aktīvs 5V zummers |
| LED Strip | LED pad | WS2812 / SK6812 |
| OpenLog | UART TX | Blackbox mežizstrāde |
| Bluetooth | UART | MSP caurlaide mobilajai skaņošanai |

---

## Nākotnes mērķi

OrniFlight mērķis ir atbalstīt papildu STM32F4/F7 mērķus, kur ir pieejami pietiekami UART un taimera resursi, lai veiktu servo vadību. Apsveicam ar ieguldījumiem.