# Getting Started

Welcome to OrniFlight! This guide walks you through the initial setup of your ornithopter flight controller.

## What You Need

- **OrniFlight Configurator** — download from [orniflight.org](https://orniflight.org)
- **USB cable** — to connect flight controller to computer
- **Ornithopter** with:
  - Supported flight controller (OMNIBUSF4, TINYFISH)
  - Servos for wing actuation
  - Receiver bound to your transmitter
  - Battery (2S–4S LiPo)

## Quick Start

### 1. Flash Firmware

1. Open **OrniFlight Configurator**
2. Go to **Firmware Flasher** tab
3. Select your board target (OMNIBUSF4 or TINYFISH)
4. Choose latest stable version
5. Click **Load Firmware** then **Flash Firmware**

### 2. Initial Configuration

After flashing, the Configurator will prompt you to apply custom defaults. **Always accept.**

### 3. Receiver Setup

1. Go to **Ports** tab → set the correct UART to `Serial RX`
2. Go to **Configuration** tab → select your receiver protocol (CRSF, SBUS, etc.)
3. Go to **Receiver** tab → verify stick movements match expected channels
4. Set channel endpoints: 1000–2000 with 1500 center

### 4. Servo Setup

1. Go to **Servos** tab
2. Verify servo mapping matches your ornithopter's wing configuration
3. Test servo direction — reverse if needed
4. Set center position (wings horizontal = 1500)

### 5. Modes Setup

1. Go to **Modes** tab
2. Assign ARM to an AUX switch
3. Assign flight modes (ANGLE / ACRO / HORIZON) as desired
4. Assign INDEPENDENT and GLIDE to spare switches
5. Configure BEEPER for lost-model locating

### 6. First Flight

1. **Remove propellers or disconnect wing linkage for bench testing**
2. Arm and verify servo movement direction
3. Check throttle response
4. For first actual flight: use ANGLE mode, low rates
5. Hover at eye level, trim as needed

## Next Steps

- [Basic Setup](basic_setup.html) — detailed configuration walkthrough
- [ONDAS Tuning](../../tutorials/ondas_tuning.html) — tune flapping dynamics
- [PID Tuning](../../tutorials/tuning.html) — adjust flight characteristics
