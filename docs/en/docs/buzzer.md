# Buzzer

OrniFlight supports active buzzers for audible status indication and lost-model location.

## Functions

- **Arm/Disarm** — distinct tones
- **Low Battery** — repeating warning beeps
- **Failsafe** — SOS pattern
- **Lost Model** — continuous beeping via switch
- **GPS Fix** — confirmation tone on satellite lock
- **Calibration** — beep patterns during gyro/accel calibration
- **RX Signal Lost** — warning when receiver connection drops

## Hardware

- Connect a 5V active buzzer (NOT a passive piezo) to the **BUZZ-** and **BUZZ+** pads
- Buzzer is driven by a transistor on the FC — no external driver needed for standard buzzers

## CLI Settings

```
beeper -GYRO_CALIBRATED     # Disable gyro calibration beeps
beeper -RX_LOST             # Enable receiver lost warning
beeper -ON_USB              # Disable beeper when USB connected
```

## Ornithopter Safety

The beeper is especially useful for large ornithopters that may land in tall grass or foliage. Configure the BEEPER mode on a momentary switch for quick activation when needed.
