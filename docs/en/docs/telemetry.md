# Telemetry

Telemetry sends flight data from OrniFlight to your radio transmitter — battery voltage, current, RSSI, GPS coordinates, altitude, and more.

## Supported Protocols

| Protocol | Radio System | Wire Count |
|----------|-------------|------------|
| **CRSF** | Crossfire / Tracer / ELRS | Integrated with RX (bidirectional) |
| **SmartPort** | FrSky | 1 wire (TX pin) |
| **HoTT** | Graupner | 1 wire (TX+TZ) |
| **IBUS** | FlySky | 1 wire (sensor TX) |
| **LTM** | Light Telemetry (MWP) | 1 wire (TX) |

## Configuration

1. In Configurator → **Ports**: set the UART TX pin to the appropriate telemetry protocol
2. Enable telemetry feature: `feature TELEMETRY`
3. Configure telemetry inversion if needed

For **CRSF**, telemetry is handled automatically — no separate port needed.

## SmartPort (FrSky)

SmartPort requires signal inversion on F4 processors. Either:
- Use a flight controller with built-in inverter
- Use SoftSerial with `set tlm_inversion = ON`

```
feature TELEMETRY
set tlm_inverted = ON
set tlm_halfduplex = ON
```

## Telemetry Data

OrniFlight transmits:
- VBAT voltage (main battery)
- Current draw / mAh consumed
- RSSI (signal strength)
- Flight mode / arm status
- GPS coordinates (if equipped)
- Altitude / vario (if barometer)
- ONDAS flight profile active
