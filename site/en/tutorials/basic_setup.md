# Basic Setup

> *Configure your ornithopter for first flight.*

## Pre-Flight Checklist

Before anything else:

- [ ] Flight controller flashed with OrniFlight
- [ ] Receiver bound to transmitter
- [ ] Servos connected to correct PWM outputs
- [ ] Battery connected (wings secured!)

## Receiver Setup

### CRSF (Recommended)

1. **Ports tab**: Set UART (e.g. UART1) to "Serial RX"
2. **Configuration tab**: Receiver Mode = "Serial-based receiver", Provider = "CRSF"
3. Power cycle, verify channel inputs move in Receiver tab

### SBUS / Other

Same process — select appropriate protocol in Configuration tab.

## Servo Mapping

In the **Servos tab**:

| Servo | Function | Default Rate |
|-------|----------|-------------|
| Servo 0 | Left Wing | 250 Hz |
| Servo 1 | Right Wing | 250 Hz |
| Servo 2 | Crest/Rudder | 50 Hz |

Adjust min/max/middle to match your servo's range. Test with "Override" to verify direction.

## Flight Mode Selection

In the **Modes tab**:

1. **ARM**: Assign to a switch (safety!)
2. **ORNITHOPTER INDEPENDENT** or **ORNITHOPTER GLIDE**: Choose your primary flight mode
3. **ORNITHOPTER PROFILE**: Optional — assign for in-flight profile switching

## ONDAS First Tuning

Go to **Advanced → ONDAS sub-tab**:

1. **Cadence Gain**: Start at 50 (mid). This is the most important parameter.
2. **Ferocity D Gain**: Start at 30. This is your primary stabilization.
3. **Ferocity P Gain**: Start at 20 for roll/pitch, 0 for yaw.
4. **Balance Gain**: 0 (centered).

Hook up a battery, **secure the ornithopter firmly**, and ARM. Observe servo movement — it should be smooth, sinusoidal flapping.

## First Flight

1. Start with a gentle toss into wind
2. Use GLIDE mode for natural soaring feel
3. Use INDEPENDENT mode when you want direct frequency control
4. Land, adjust ONDAS, repeat

---

*Next: [ONDAS Tuning Guide](ondas_tuning.html) →*
