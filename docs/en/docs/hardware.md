# Supported Hardware

## Flight Controllers

| Board | MCU | IMU | Flash | OSD | Status |
|-------|-----|-----|-------|-----|--------|
| **OMNIBUSF4** | STM32F405 | MPU6000 (SPI) | 16MB | AT7456E | ✅ Primary |
| **TINYFISH** | STM32F411 | MPU6000 (SPI) | 256KB | — | ✅ Supported |

### OMNIBUSF4

The primary development target. Full-featured F4 flight controller with OSD, ample flash for Blackbox logging, and sufficient UARTs for all peripherals.

- **MCU**: STM32F405RGT6 @ 168 MHz
- **Gyro**: MPU6000 (SPI, 8 kHz capable)
- **Flash**: 16MB for Blackbox
- **OSD**: AT7456E (compatible with MAX7456)
- **UARTs**: VCP + 5 hardware UARTs
- **Barometer**: BMP280 (some variants)
- **Input**: 2-6S LiPo

### TINYFISH

Compact F4 target for small ornithopters and micro flappers.

- **MCU**: STM32F411CEU6 @ 100 MHz
- **Gyro**: MPU6000 (SPI)
- **Flash**: 256KB onboard
- **UARTs**: VCP + 2 hardware UARTs
- **Input**: 2-4S LiPo

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
