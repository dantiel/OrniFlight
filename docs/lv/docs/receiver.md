# Uztvērējs (RX)

OrniFlight atbalsta vairākus uztvērēja protokolus jūsu ornitoptera radio vadībai.

## Atbalstītie protokoli

| Protokols | Tips | Piezīmes |
|----------|------|-------|
| **CRSF** (Crossfire) | Sērijas | Zems latentums, telemetrija, ieteicams |
| **SBUS** | Sērijas | Apgriezts, nepieciešams invertors uz F4 |
| **IBUS** (FlySky) | Sērijas | Neapgriezts, tiešs UART |
| **PPM** | Viena vada analogs | 8ch, mantojums, nav ieteicams |
| **SPEKTRUM** | Sērijas | 1024/2048, saistīt, izmantojot CLI |
| **FPORT** | Sērijas | FrSky, apvieno RX+Telemetriju |
| **GHST** (Spoks) | Sērijas | ImmersionRC, zems latentums |

## Sērijas RX konfigurācija

1. Savienojiet uztvērēju ar brīvu UART RX tapu
2. Programmā Configurator → **Ports**: iestatiet UART uz `Serial RX`.
3. Programmā Configurator → **Configuration**: atlasiet protokolu
4. Zzz8zzz uz F4: iespējojiet `set sbus_inversion = ON`

## CLI Ātrā iestatīšana

```
feature RX_SERIAL
set serialrx_provider = CRSF
set serialrx_inverted = OFF
set serialrx_halfduplex = OFF
save
```

## Neatteicas

Konfigurējiet uztvērēju bezatteices, lai signāla zuduma gadījumā uztvērējs izvadītu **nav impulsu**. Pēc tam lidojuma kontrolieris to noteiks un aktivizēs savu bezatteices procedūru. Skatiet [Failsafe](failsafe.html) FC līmeņa konfigurāciju.