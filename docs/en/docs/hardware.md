# Supported Hardware

OrniFlight runs on commodity STM32F3/F4/F7 flight controllers. The baseline is **STM32F3** — any F3 target with servo-capable timer pins will fly.

## Flight Controllers

| Board | MCU | IMU | Flash | Receiver | Status |
|-------|-----|-----|-------|----------|--------|
| **TINYFISH** | STM32F303 | MPU6000 (SPI) | 256 KB | FrSky D8 (integrated) | ✅ Primary |
| **OMNIBUSF4** | STM32F405 | MPU6000 (SPI) | 1 MB + 16 MB SPI | — | ✅ Supported |

### TINYFISH — The Lightest OrniFlight Target

Designed by fishpepper, TINYFISH is the ideal ornithopter flight controller: featherweight, F3-based, and carrying an **integrated FrSky D8 receiver** on-board. No external RX, no extra wiring — just power, servos, and fly.

- **MCU**: STM32F303CCT6 @ 72 MHz
- **Gyro**: MPU6000 (SPI, 8 kHz capable)
- **Flash**: 256 KB on-chip
- **RAM**: 40 KB
- **Receiver**: Integrated FrSky D8 (SBUS internally routed to UART2)
- **UARTs**: VCP + 2 hardware UARTs (UART1 free for GPS/CRSF add-on)
- **Input**: 2-4S LiPo (direct servo power)
- **Weight**: ~2.5 g

TINYFISH proves that transcendent flapping control doesn't need an F7. The STM32F303 runs the full ONDAS pipeline — 10 modulation channels, trapezoidal wing ODE, 4 flight profiles — within 256 KB.

### OMNIBUSF4 — The Accessible Workhorse

The classic F4 target. Cheap, ubiquitous, full-featured with OSD and ample SPI flash for Blackbox logging. The go-to for development and larger builds.

- **MCU**: STM32F405RGT6 @ 168 MHz
- **Gyro**: MPU6000 (SPI, 8 kHz capable)
- **Flash**: 1 MB on-chip + 16 MB SPI (Blackbox)
- **RAM**: 192 KB
- **OSD**: AT7456E (compatible with MAX7456)
- **UARTs**: VCP + 5 hardware UARTs
- **Barometer**: BMP280 (some variants)
- **Input**: 2-6S LiPo

---

## Ornithopter Anatomy

### Wing Servos

OrniFlight controls flapping through PWM servos. Key specifications:

| Parameter | Typical Range |
|-----------|--------------|
| Pulse Width | 500–2500 µs |
| Center | 1500 µs |
| Frequency | 50–330 Hz |
| Stroke Angle | ±15–45° |

For high-performance ornithopters, digital servos with 330 Hz update rate are recommended. Analog servos work at 50 Hz but have lower precision.

### Receiver

Any serial receiver protocol is supported. CRSF (TBS Crossfire / ExpressLRS) is recommended for:
- Low latency (critical for flapping control)
- Built-in telemetry
- RSSI over protocol (no extra wiring)

### Battery

- **2S (7.4V)**: Small ornithopters, servo-powered directly
- **3S (11.1V)**: Medium ornithopters, BEC required for servos
- **4S (14.8V)**: Large ornithopters, external BEC recommended

---

## Supported Peripherals

| Peripheral | Via | Notes |
|-----------|-----|-------|
| GPS | UART | UBlox M8N or compatible |
| VTX | UART TX | Tramp, SmartAudio |
| Camera | — | Any analog FPV camera |
| Buzzer | BUZZ pad | Active 5V buzzer |
| LED Strip | LED pad | WS2812 / SK6812 |
| OpenLog | UART TX | Blackbox logging |
| Bluetooth | UART | MSP passthrough for mobile tuning |

---

## Future Targets

OrniFlight aims to support additional STM32F4/F7 targets where sufficient UART and timer resources are available for flapping servo control. Contributions welcome.