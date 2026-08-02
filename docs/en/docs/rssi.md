# RSSI

RSSI (Received Signal Strength Indicator) shows the quality of your radio link. OrniFlight can source RSSI from analog input, serial receiver data, or protocol RSSI.

## RSSI Sources

| Source | Connection | Configuration |
|--------|-----------|---------------|
| **Serial Protocol** | None (over serial RX wire) | CRSF, GHST — automatic |
| **AUX Channel** | None (TX sends RSSI as channel) | `set rssi_channel = 8` |
| **Analog ADC** | RSSI pad on FC → Receiver RSSI out | `set rssi_adc_channel = 1` |

## Configuration

### Serial RSSI (CRSF/GHST/SBUS)

```
set rssi_src_frame_errors = OFF
set rssi_scale = 100
set rssi_offset = 0
```

RSSI is transmitted automatically by serial protocols — no extra wiring needed.

### Analog RSSI

Connect receiver RSSI output → RSSI pad on flight controller:

```
set rssi_adc_channel = 1      # Use ADC channel 1
set rssi_scale = 100          # Scale to 0-100%
set rssi_offset = 0
```

### AUX Channel RSSI

Configure your transmitter to send RSSI on a specific channel, then:

```
set rssi_channel = 12         # Aux channel number
set rssi_scale = 100
set rssi_offset = 0
```

## Display

RSSI is shown in the OSD and can be transmitted via telemetry to your radio. Configure warning thresholds:

```
set osd_rssi_alarm = 20        # Warning at 20% RSSI
```

## Ornithopter Range

For ornithopters, RSSI is critical — flapping wings create dynamic RF interference patterns. Monitor RSSI during initial test flights to verify reliable link performance at all wing positions.
