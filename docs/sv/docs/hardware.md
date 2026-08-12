# Hårdvara som stöds

OrniFlight körs på commodity STM32F3/F4/F7 flygkontroller. Baslinjen är **STM32F3** — alla F3-mål med servo-kapabla timerstift kommer att flyga.

## Flygkontroller

| Styrelse | MCU | IMU | Flash | Mottagare | Status |
|-------|-----|-----|-------|----------|--------|
| **TINYFISH** | STM32F303 | MPU6000 (SPI) | 256 KB | FrSky D8 (integrerad) | ✅ Primär |
| **OMNIBUSF4** | STM32F405 | MPU6000 (SPI) | 1 MB + 16 MB SPI | — | ✅ stöds |

### TINYFISH — Det lättaste målet för OrniFlight

Designad av fishpepper är TINYFISH den idealiska ornithopterflygkontrollen: fjäderlätt, F3-baserad och bär en **integrerad FrSky D8-mottagare** ombord. Inga externa RX, inga extra kablar — bara ström, servon och flyg.

- **MCU**: STM32F303CCT6 @ 72 MHz
- **Gyro**: MPU6000 (SPI, 8 kHz-kompatibel)
- **Flash**: 256 KB på chipet
- **RAM**: 40 KB
- **Mottagare**: Integrerad FrSky D8 (SBUS internt dirigerad till UART2)
- **UARTs**: VCP + 2 hårdvaru-UARTs (UART1 gratis för GPS/CRSF-tillägg)
- **Ingång**: 2-4S LiPo (direkt servokraft)
- **Vikt**: ~2,5 g

TINYFISH bevisar att transcendent flaxande kontroll inte behöver en F7. Zzz73zzz kör hela ONDAS pipeline — 10 moduleringskanaler, trapetsformade vingar ODE, 4 flygprofiler — inom 256 KB.

### OMNIBUSF4 — Den lättillgängliga arbetshästen

Det klassiska målet F4. Billigt, allmänt förekommande, fullfjädrat med OSD och gott om SPI-blixt för Blackbox-loggning. Go-to för utveckling och större byggen.

- **MCU**: STM32F405RGT6 @ 168 MHz
- **Gyro**: MPU6000 (SPI, 8 kHz-kompatibel)
- **Flash**: 1 MB on-chip + 16 MB SPI (Blackbox)
- **RAM**: 192 KB
- **OSD**: AT7456E (kompatibel med MAX7456)
- **UARTs**: VCP + 5 hårdvaru-UARTs
- **Barometer**: BMP280 (vissa varianter)
- **Ingång**: 2-6S LiPo

---

## Ornithopter Anatomy

### Wing Servos

OrniFlight kontroller flaxande genom PWM servon. Viktiga specifikationer:

| Parameter | Typiskt intervall |
|--------|-------------|
| Pulsbredd | 500–2500 µs |
| Center | 1500 µs |
| Frekvens | 50–330 Hz |
| Slagvinkel | ±15–45° |

För högpresterande ornithoptrar rekommenderas digitala servon med 330 Hz uppdateringshastighet. Analoga servon arbetar vid 50 Hz men har lägre precision.

### Mottagare

Alla seriella mottagarprotokoll stöds. CRSF (TBS Crossfire / ExpressLRS) rekommenderas för:
- Låg latens (kritiskt för flaxande kontroll)
- Inbyggd telemetri
- RSSI överprotokoll (inga extra kablar)

### Batteri

- **2S (7,4V)**: Små ornithoptrar, servodrivna direkt
- **3S (11,1V)**: Medium ornithoptrar, BEC krävs för servon
- **4S (14,8V)**: Stora ornithoptrar, externa BEC rekommenderas

---

## Kringutrustning som stöds

| Perifer | Via | Anteckningar |
|-----------|-----|-------|
| GPS | UART | UBlox M8N eller kompatibel |
| VTX | UART TX | Luffare, SmartAudio |
| Kamera | — | Vilken analog FPV kamera som helst |
| Summer | BUZZ pad | Aktiv 5V summer |
| LED Strip | LED pad | WS2812 / SK6812 |
| OpenLog | UART TX | Blackbox-loggning |
| Bluetooth | UART | MSP passthrough för mobil tuning |

---

## Framtida mål

OrniFlight syftar till att stödja ytterligare STM32F4/F7-mål där tillräckligt med UART och timerresurser finns tillgängliga för flaxande servokontroll. Bidrag välkomna.