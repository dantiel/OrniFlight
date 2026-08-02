# LED Strip

OrniFlight supports addressable WS2812/SK6812 LED strips for status indication and visual feedback.

## Configuration

LED strips are configured in the **LED Strip** tab of OrniFlight Configurator. Each LED position, color, and function can be set individually.

## Functions

| Function | Visual Effect |
|----------|--------------|
| Battery Indicator | Color gradient from green → yellow → red |
| RSSI | Signal strength display |
| Arm State | Color change on arm/disarm |
| Flight Mode | Mode-specific colors |
| Warning | Blink patterns for low battery, failsafe |
| Flapping Indicator | Pulse at current flapping frequency |
| Thrust Direction | Color shift indicating roll/pitch/yaw output |
| GPS | Satellite lock and home direction |

## Hardware

- WS2812 or SK6812 RGB LEDs
- Connect to the **LED** pad/pin on your flight controller
- Power LEDs from a BEC (do NOT power from 3.3V — use 5V)
- For long strips (>8 LEDs), connect 5V power directly to battery pads, not through FC

## Ornithopter Use

The **Flapping Indicator** is unique to OrniFlight — LEDs pulse in sync with wing stroke frequency, giving a visual representation of flapping rhythm and helping tune ONDAS cadence parameters.
