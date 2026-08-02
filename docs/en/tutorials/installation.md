# Installation

How to install OrniFlight firmware on your flight controller.

## Prerequisites

- **OrniFlight Configurator** (latest version)
- USB data cable (not charge-only)
- Supported flight controller board

## Supported Boards

| Board | Target | Flash | Notes |
|-------|--------|-------|-------|
| OMNIBUSF4 | `OMNIBUSF4` | 16MB | STM32F405, MPU6000, OSD |
| TINYFISH | `TINYFISH` | 256KB | STM32F411, MPU6000 |

## Flashing Steps

### 1. Enter DFU/Bootloader Mode

**OMNIBUSF4**: Hold BOOT button while connecting USB. Red LED stays solid — you're in DFU mode.

**TINYFISH**: Hold BOOT button while connecting USB.

### 2. Flash via Configurator

1. Open OrniFlight Configurator
2. Go to **Firmware Flasher** tab
3. Select your target from the dropdown
4. Choose firmware version (latest stable recommended)
5. Click **Load Firmware (Online)** or select a local hex file
6. Click **Flash Firmware**
7. Wait for "Programming: SUCCESSFUL"

### 3. First Connection

After flashing:
1. Disconnect and reconnect USB (without BOOT button)
2. Configurator should auto-connect
3. Accept "Apply Custom Defaults" prompt
4. Verify board info on Setup tab

## Troubleshooting

### No DFU Port

**macOS/Linux**: DFU should appear automatically. If not:
```bash
# Check for DFU device
system_profiler SPUSBDataType | grep -A 10 STM
```

**Windows**: Install [Zadig](https://zadig.akeo.ie/) to replace the STM32 DFU driver:
1. Run Zadig
2. Options → List All Devices
3. Select "STM32 BOOTLOADER"
4. Replace driver with "WinUSB"

### Flash Fails

- Try a different USB cable (data-capable, not charge-only)
- Try a different USB port (direct, not hub)
- Hold BOOT button throughout the flash process
- **OMNIBUSF4**: Full chip erase may be needed — check "Full Chip Erase" option

### Configurator Won't Connect

- Verify USB cable is data-capable
- Check board is not in DFU mode (LED flashing = normal mode)
- Restart Configurator
- Try different USB port

## CLI Flash (Advanced)

For advanced users, flash via STM32CubeProgrammer or st-flash:

```bash
st-flash write orniflight_0.4.6_OMNIBUSF4.hex 0x08000000
```

After flashing, verify with:

```bash
st-flash verify orniflight_0.4.6_OMNIBUSF4.hex 0x08000000
```
