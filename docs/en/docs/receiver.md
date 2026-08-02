# Receiver (RX)

OrniFlight supports multiple receiver protocols for radio control of your ornithopter.

## Supported Protocols

| Protocol | Type | Notes |
|----------|------|-------|
| **CRSF** (Crossfire) | Serial | Low latency, telemetry, recommended |
| **SBUS** | Serial | Inverted, needs inverter on F4 |
| **IBUS** (FlySky) | Serial | Non-inverted, direct UART |
| **PPM** | Single-wire analog | 8ch, legacy, not recommended |
| **SPEKTRUM** | Serial | 1024/2048, bind via CLI |
| **FPORT** | Serial | FrSky, combines RX+Telemetry |
| **GHST** (Ghost) | Serial | ImmersionRC, low latency |

## Serial RX Configuration

1. Connect receiver to a free UART RX pin
2. In Configurator → **Ports**: set the UART to `Serial RX`
3. In Configurator → **Configuration**: select protocol
4. For SBUS on F4: enable `set sbus_inversion = ON`

## CLI Quick Setup

```
feature RX_SERIAL
set serialrx_provider = CRSF
set serialrx_inverted = OFF
set serialrx_halfduplex = OFF
save
```

## Failsafe

Configure receiver failsafe so that the receiver outputs **no pulses** on signal loss. The flight controller will then detect this and activate its own failsafe procedure. See [Failsafe](failsafe.html) for FC-level configuration.
