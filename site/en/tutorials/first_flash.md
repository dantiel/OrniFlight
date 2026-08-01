# First Flash

> *Getting OrniFlight onto your flight controller — step by step.*

## What You Need

- STM32F4-based flight controller (OMNIBUSF4, TINYFISH, MATEKF405, etc.)
- USB cable
- [dfu-util](http://dfu-util.sourceforge.net/) or STM32CubeProgrammer
- OrniFlight `.hex` file from the [releases page](https://github.com/dantiel/OrniFlight/releases)

## Step 1: Enter DFU Mode

1. **Hold the BOOT button** on your flight controller
2. **Plug in USB** while holding the button
3. **Release** after 2 seconds

Verify on macOS/Linux:

```
dfu-util -l
```

Should show `Found DFU: [0483:df11]`

## Step 2: Flash

```
dfu-util -a 0 -D obj/orniflight_0.4.6_OMNIBUSF4.hex
```

## Step 3: First Boot

1. Unplug USB
2. Plug USB back in (don't hold BOOT)
3. Connect via OrniFlight Configurator

## Step 4: Basic Configuration

In the Configurator:

1. **Ports tab**: Configure UART for your receiver (Serial RX)
2. **Configuration tab**: Select receiver protocol (CRSF recommended)
3. **Modes tab**: Set up ARM, GLIDE/INDEPENDENT, and PROFILE switches
4. **Advanced → ONDAS tab**: Review defaults, tune Cadence first

## Troubleshooting

| Problem | Fix |
|---------|-----|
| DFU device not found | Try different USB cable, check BOOT button |
| Flash fails | Check dfu-util installation, USB permissions |
| No boot after flash | Re-flash, verify hex matches your target |
| Configurator won't connect | Check COM port and baud rate |

---

*Next: [Basic Setup](basic_setup.html) →*
