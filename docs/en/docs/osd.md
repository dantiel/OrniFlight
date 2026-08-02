# On-Screen Display (OSD)

OrniFlight includes a built-in OSD (On-Screen Display) using the MAX7456 or AT7456E chip. The OSD overlays flight data onto your FPV video feed.

## Supported Elements

Configure elements in the **OSD** tab of OrniFlight Configurator. Drag and drop elements to position them on screen.

### Flight Data

| Element | Displays |
|---------|----------|
| Battery Voltage | Main battery voltage (e.g. 14.8V) |
| Average Cell Voltage | Per-cell voltage (e.g. 3.7V) |
| Current Draw | Instantaneous amps |
| mAh Drawn | Cumulative capacity consumed |
| RSSI | Signal strength from receiver |
| Flight Mode | Current mode (INDEPENDENT, GLIDE, etc.) |
| Throttle Position | Current throttle percentage |
| Timer | Flight time / armed time |
| Craft Name | OrniFlight craft name |

### Ornithopter-Specific

| Element | Displays |
|----------|----------|
| Flapping Frequency | Current wing stroke rate in Hz |
| ONDAS Profile | Active flight profile number (1-3) |
| Cadence Phase | Current modulation phase offset |
| Servo Angle | Wing servo position |

## Font Management

The OSD uses a character-based display system. The OrniFlight Configurator's **OSD** tab includes a **Font Manager** for uploading custom fonts and glyphs.

## CLI Settings

```
set osd_units = METRIC
set osd_warn_bitmask = 270335  # Warning flag bitmask
set osd_tim1 = 2560            # Timer 1 source
set osd_tim2 = 2561            # Timer 2 source
```

## Hardware

Currently supported OSD chip: **AT7456E** (found on OMNIBUSF4 and compatible boards). MAX7456 is compatible and auto-detected.