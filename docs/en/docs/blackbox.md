# Blackbox Logging

Blackbox records flight data for post-flight analysis, tuning, and debugging. OrniFlight supports logging to onboard flash chip or external OpenLog device.

## What Gets Logged

- **Gyro** — raw and filtered 3-axis angular velocity
- **Accelerometer** — 3-axis acceleration
- **PID Output** — P, I, D, F contributions per axis
- **ONDAS** — Cadence, Ferocity P/D, and other flapping-specific parameters
- **RC Commands** — stick positions after rates/expo
- **Servo Output** — final output to each servo channel
- **Battery** — voltage and current per iteration
- **GPS** — position, speed, altitude (when available)

## Setup

### Onboard Flash (OMNIBUSF4)

The OMNIBUSF4 includes 16MB onboard flash for Blackbox logging. Enable in Configurator:

1. **Blackbox** tab → Set `Blackbox logging device` to `Onboard flash`
2. Set logging rate (recommend: `1/N` with N=2-4 for F4 targets)
3. Assign a switch to start/stop logging

### External OpenLog

Connect OpenLog to a free UART TX pin:

1. **Ports** tab → Set the UART to `Blackbox logging` at 115200 baud
2. Connect OpenLog: FC TX → OpenLog RX, plus 5V/GND

## Analysis Tools

- [Blackbox Explorer](https://github.com/betaflight/blackbox-log-viewer) — web-based log viewer
- `blackbox_decode` — convert to CSV for custom analysis

## ONDAS-Specific

Blackbox is essential for tuning ONDAS parameters. Logged ONDAS data includes:
- `ondas_cadence_phase` — modulation window timing
- `ondas_ferocity_p` / `ondas_ferocity_d` — asymmetric thrust components
- `ondas_balance` — left/right wing balance
- Per-servo output at each iteration

This allows precise analysis of flapping mechanics and wing asymmetry corrections.