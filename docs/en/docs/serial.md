# Serial Ports

OrniFlight uses serial ports for communication with peripherals: receivers, GPS, telemetry, VTX control, Blackbox logging, and MSP (Configurator connection).

## Serial Port Types

| Type | Description | Best For |
|------|------------|----------|
| **VCP** | USB Virtual COM Port — direct USB connection to processor | Configurator (MSP) |
| **UART** | Hardware TX/RX pins with hardware signal detection | RX, GPS, Telemetry, VTX, Blackbox |
| **SoftSerial** | Software-driven serial on any pin pair | Low-bandwidth: telemetry only |

VCP does not consume a physical UART — it's always available for the Configurator.

## Port Assignment

In OrniFlight Configurator, go to the **Ports** tab to assign functions:

| Function | Typical UART | Notes |
|----------|-------------|-------|
| Serial RX | UART1 or UART3 | SBUS, CRSF, IBUS, etc. |
| GPS | UART3 or UART6 | 57600 or 115200 baud |
| Telemetry | Any TX pin | SmartPort, HoTT, IBUS |
| VTX (Tramp/SmartAudio) | Any TX pin | Single-wire |
| Blackbox | Any TX pin | OpenLog or onboard flash |
| MSP | VCP (USB) | Configurator connection |

## OMNIBUSF4 Port Mapping

| UART | Pins | Typical Use |
|------|------|------------|
| VCP | USB | MSP (Configurator) |
| UART1 | TX1/RX1 | Serial RX |
| UART3 | TX3/RX3 | GPS or Telemetry |
| UART6 | TX6/RX6 | Free / Blackbox / VTX |

## SoftSerial

SoftSerial is available but has limited bandwidth. Suitable only for low-rate telemetry (e.g. 9600 baud SmartPort). Not recommended for Serial RX or GPS.
