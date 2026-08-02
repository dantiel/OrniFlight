# Battery Monitoring

OrniFlight monitors main battery voltage via the ADC (Analog-to-Digital Converter). This enables low-battery warnings through buzzer, status LED, and LED strip patterns.

## Features

- Auto-detection of cell count on connect (based on min/max cell voltages)
- Low battery warning with configurable thresholds
- Current sensing for mAh consumption (if supported by FC)
- Voltage displayed in OSD and transmitted via telemetry

## Supported Targets

All supported flight controllers (OMNIBUSF4, TINYFISH) include VBAT monitoring via voltage divider.

## Connections

**ALWAYS CHECK POLARITY.** Measure expected voltages before connecting. Incorrect voltage or reversed polarity will destroy your flight controller.

### OMNIBUSF4

Connect main battery to VBAT pad. The onboard voltage divider handles up to 6S directly.

### TINYFISH

VBAT is routed through the board's power input — no separate connection needed.

## CLI Settings

```
set vbat_min_cell_voltage = 330       # Minimum per-cell voltage (3.3V)
set vbat_max_cell_voltage = 430       # Maximum per-cell voltage (4.3V)
set vbat_warning_cell_voltage = 350   # Warning threshold (3.5V)
set battery_meter_type = ADC
set current_meter_type = ADC          # If current sensor available
```

## Safety

LiPo batteries should never be discharged below 3.5V per cell under load. OrniFlight's configurable thresholds help ensure safe operation and battery longevity.
