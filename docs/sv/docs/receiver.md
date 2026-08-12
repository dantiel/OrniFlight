# Mottagare (RX)

OrniFlight stöder flera mottagarprotokoll för radiostyrning av din ornithopter.

## Protokoll som stöds

| Protokoll | Skriv | Anteckningar |
|--------|------|-------|
| **CRSF** (Crossfire) | Seriell | Låg latens, telemetri, rekommenderas |
| **SBUS** | Seriell | Inverterad, behöver växelriktare på F4 |
| **IBUS** (FlySky) | Seriell | Icke-inverterad, direkt UART |
| **PPM** | Enkeltråds analog | 8ch, legacy, rekommenderas inte |
| **SPEKTRUM** | Seriell | 1024/2048, bind via CLI |
| **FPORT** | Seriell | FrSky, kombinerar RX+telemetri |
| **GHST** (Spöke) | Seriell | ImmersionRC, låg latens |

## Seriell RX Konfiguration

1. Anslut mottagaren till ett ledigt UART RX-stift
2. I Configurator → **Portar**: ställ in UART på `Serial RX`
3. I Configurator → **Configuration**: välj protokoll
4. För SBUS på F4: aktivera `set sbus_inversion = ON`

## CLI Snabbinställning

```
feature RX_SERIAL
set serialrx_provider = CRSF
set serialrx_inverted = OFF
set serialrx_halfduplex = OFF
save
```

## Felsäker

Konfigurera mottagarens felsäker så att mottagaren avger **inga pulser** vid signalförlust. Flygledaren kommer då att upptäcka detta och aktivera sin egen felsäkra procedur. Se [Failsafe](failsafe.html) för FC-nivåkonfiguration.