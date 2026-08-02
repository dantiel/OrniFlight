# GPS

GPS enables position hold, return-to-home, and telemetry-based navigation for your ornithopter. GPS features in OrniFlight are functional but considered experimental — always fly within visual line of sight.

## Supported Protocols

- **UBLOX** (recommended) — UBlox binary protocol, efficient and reliable
- **NMEA** — Text-based standard protocol

## Hardware

- BN-880, BN-220, or similar UBlox M8N GPS+Compass modules
- Connect: TX/RX to a free UART, plus 5V/GND
- Mount GPS away from power wires and ESCs to minimize interference
- Compass/magnetometer must be away from magnetic sources (power wires, motors)

## Configuration

```
feature GPS
set gps_provider = UBLOX
set gps_sbas_mode = AUTO
set gps_auto_baud = ON
set gps_ublox_use_galileo = ON
```

1. Assign serial port to GPS in **Ports** tab (default 115200 baud for UBlox)
2. Enable GPS feature
3. Set provider
4. Save and reboot

## OSD Elements

GPS data displayed in OSD includes:
- Satellite count and fix type
- GPS coordinates (lat/lon)
- Ground speed
- Altitude (GPS)
- Distance from home
- Home direction arrow

## Ornithopter Considerations

- GPS antenna must have clear sky view — mounting location is critical with flapping wings
- Weight penalty is significant on small ornithopters
- GPS-assisted RTH (Return to Home) requires careful tuning of navigation PID values for flapping flight dynamics
