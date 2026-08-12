# Unterstützte Hardware

OrniFlight läuft auf den Standard-Flugsteuerungen STM32F3/F4/F7. Die Grundlinie ist **STM32F3** —, jedes F3-Ziel mit servofähigen Timer-Pins wird fliegen.

## Fluglotsen

| Vorstand | MCU | IMU | Blitz | Empfänger | Status |
|-------|-----|-----|-------|----------|--------|
| **TINYFISH** | STM32F303 | MPU6000 (SPI) | 256 KB | FrSky D8 (integriert) | ✅ Primär |
| **OMNIBUSF4** | STM32F405 | MPU6000 (SPI) | 1 MB + 16 MB SPI | — | ✅ Unterstützt |

### TINYFISH — Das leichteste OrniFlight Ziel

Der von Fishpepper entworfene TINYFISH ist der ideale Ornithopter-Flugcontroller: federleicht, F3-basiert und mit einem **integrierten FrSky D8-Empfänger** an Bord. Keine externe RX, keine zusätzliche Verkabelung —, nur Strom, Servos und Flug.

- **MCU**: STM32F303CCT6 bei 72 MHz
- **Gyro**: MPU6000 (SPI, 8 kHz fähig)
- **Flash**: 256 KB auf dem Chip
- **RAM**: 40 KB
- **Empfänger**: Integrierter FrSky D8 (SBUS intern an UART2 geroutet)
- **UARTs**: VCP + 2 Hardware-UARTs (UART1 kostenlos für das Add-on GPS/CRSF)
- **Eingang**: 2-4S LiPo (direkte Servoleistung)
- **Gewicht**: ~2,5 g

TINYFISH beweist, dass transzendente Schlagsteuerung keinen F7 benötigt. Der STM32F303 betreibt die gesamte ONDAS-Pipeline, — 10 Modulationskanäle, Trapezflügel ODE, 4 Flugprofile — innerhalb von 256 KB.

### OMNIBUSF4 — Das zugängliche Arbeitstier

Das klassische F4-Ziel. Günstig, allgegenwärtig, voll ausgestattet mit OSD und reichlich SPI Flash für Blackbox-Protokollierung. Die Anlaufstelle für Entwicklung und größere Builds.

- **MCU**: STM32F405RGT6 bei 168 MHz
- **Gyro**: MPU6000 (SPI, 8 kHz fähig)
- **Flash**: 1 MB On-Chip + 16 MB SPI (Blackbox)
- **RAM**: 192 KB
- **OSD**: AT7456E (kompatibel mit MAX7456)
- **UARTs**: VCP + 5 Hardware-UARTs
- **Barometer**: BMP280 (einige Varianten)
- **Eingang**: 2-6S LiPo

---

## Ornithopter-Anatomie

### Flügelservos

OrniFlight steuert das Flattern durch PWM-Servos. Wichtige Spezifikationen:

| Parameter | Typischer Bereich |
|-----------|--------------|
| Impulsbreite | 500–2500 µs |
| Zentrum | 1500 µs |
| Häufigkeit | 50–330 Hz |
| Hubwinkel | ±15–45° |

Für Hochleistungsornithopter werden Digitalservos mit 330 Hz Aktualisierungsrate empfohlen. Analoge Servos arbeiten mit 50 Hz, haben aber eine geringere Präzision.

### Empfänger

Jedes serielle Empfängerprotokoll wird unterstützt. CRSF (TBS Crossfire / ExpressLRS) wird empfohlen für:
- Geringe Latenz (kritisch für die Schlagkontrolle)
- Integrierte Telemetrie
- RSSI über Protokoll (keine zusätzliche Verkabelung)

### Batterie

- **2S (7,4V)**: Kleine Ornithopter, direkt servoangetrieben
- **3S (11,1V)**: Mittlere Ornithopter, BEC für Servos erforderlich
- **4S (14,8V)**: Große Ornithopter, externe BEC empfohlen

---

## Unterstützte Peripheriegeräte

| Peripherie | Über | Notizen |
|-----------|-----|-------|
| GPS | UART | UBlox M8N oder kompatibel |
| VTX | UART TX | Tramp, SmartAudio |
| Kamera | — | Jede analoge FPV-Kamera |
| Summer | BUZZ Pad | Aktiver 5V-Summer |
| LED Streifen | LED Pad | WS2812 / SK6812 |
| OpenLog | UART TX | Blackbox-Protokollierung |
| Bluetooth | UART | MSP Passthrough für mobiles Tuning |

---

## Zukünftige Ziele

OrniFlight zielt darauf ab, zusätzliche STM32F4/F7-Ziele zu unterstützen, bei denen ausreichend UART- und Timer-Ressourcen für die Schlagservosteuerung verfügbar sind. Beiträge willkommen.