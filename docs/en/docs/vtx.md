# Video Transmitter (VTX)

OrniFlight supports VTX control for FPV ornithopters. VTX modules can be configured via the OrniFlight Configurator, MSP, or CLI — setting band, channel, power level, and pit mode.

## Supported Protocols

1. **IRC Tramp** — Common on small VTX modules, ideal for lightweight FPV ornithopters
2. **TBS SmartAudio** — Digital protocol with pit mode support
3. **RTC6705** — Direct SPI control on boards with integrated VTX (e.g. SPRACINGF3NEO)

## Configuration

VTX settings are managed through the **VTX** tab in OrniFlight Configurator, or via CLI:

```
set vtx_band = 5           # Raceband
set vtx_channel = 1        # 5658 MHz
set vtx_power = 2          # 200mW
set vtx_low_power_disarm = ON  # Lower power when disarmed
set vtx_pit_mode_freq = 0  # Pit mode frequency (0 = disabled)
```

## Serial Port

VTX control requires a dedicated UART TX pin. Configure the port in **Ports** tab with `IRC Tramp` or `TBS SmartAudio` peripheral.

## FPV Ornithopter Considerations

- Weight is critical — choose lightweight VTX modules (Tramp Nano, Eachine Nano)
- Antenna mounting: ensure clearance from flapping wings
- Power filtering: connect VTX power after LC filter to avoid motor noise in video
- Pit mode is recommended for bench testing to avoid overheating small VTX modules
