# Supported Hardware

> *Flight controllers tested with OrniFlight.*

## Primary Targets

| Target | MCU | Flash | Servo Pins | Status |
|--------|-----|-------|-----------|--------|
| **OMNIBUSF4** | STM32F405 | 1MB | Motors 1-4, LED strip | Primary |
| **TINYFISH** | STM32F411 | 512KB | Motors 1-4, LED strip | Limited flash |

## Servo Output Pins

OrniFlight repurposes motor output pins for servo PWM:

| Logical Servo | F4 Timer Pin | Common Use |
|---------------|-------------|------------|
| Servo 0 | Motor 1 (PA3) | Left wing |
| Servo 1 | Motor 2 (PA2) | Right wing |
| Servo 2 | Motor 3 (PB0) | Crest rudder |
| Servo 3 | Motor 4 (PB1) | Aux / spare |

## Receiver Compatibility

| Protocol | Status | Notes |
|----------|--------|-------|
| **CRSF** (ELRS/Crossfire) | Primary | Telemetry, binding phrase |
| **SBUS** | Working | Standard FrSky/Futaba |
| **Spektrum 1024/2048** | Working | Bind via CLI |
| **SUMD** | Working | Graupner HoTT |
| **IBUS** | Working | FlySky |

## Wiring

```
FC                          Receiver (CRSF)
——                          ————————————————
UART1 TX  ──────────────→  RX
UART1 RX  ──────────────→  TX
GND       ──────────────→  GND
5V        ──────────────→  VCC

FC                          Servos
——                          ——————
Motor 1 (PA3)  ──────────→  Left Wing (signal)
Motor 2 (PA2)  ──────────→  Right Wing (signal)
Motor 3 (PB0)  ──────────→  Rudder (signal)
GND            ──────────→  Servo GND
5V (BEC)       ──────────→  Servo VCC
```

---

*See `docs/Boards.md` in the firmware repository for board-specific details.*
