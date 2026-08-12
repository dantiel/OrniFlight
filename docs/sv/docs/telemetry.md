# Telemetri

Telemetri skickar flygdata från OrniFlight till din radiosändare — batterispänning, ström, RSSI, GPS koordinater, höjd och mer.

## Protokoll som stöds

| Protokoll | Radiosystem | Trådräkning |
|--------|-------------|--------|
| **CRSF** | Crossfire / Tracer / ELRS | Integrerad med RX (dubbelriktad) |
| **SmartPort** | FrSky | 1 tråd (TX stift) |
| **HoTT** | Graupner | 1 tråd (TX+TZ) |
| **IBUS** | FlySky | 1 tråd (sensor TX) |
| **LTM** | Ljus telemetri (MWP) | 1 tråd (TX) |

## Konfiguration

1. I Configurator → **Portar**: ställ in UART TX pin till lämpligt telemetriprotokoll
2. Aktivera telemetrifunktion: `feature TELEMETRY`
3. Konfigurera telemetriinversion om det behövs

För **CRSF** hanteras telemetri automatiskt — ingen separat port behövs.

## SmartPort (FrSky)

SmartPort kräver signalinversion på F4-processorer. Antingen:
- Använd en flygkontroll med inbyggd växelriktare
- Använd SoftSerial med `set tlm_inversion = ON`

```
feature TELEMETRY
set tlm_inverted = ON
set tlm_halfduplex = ON
```

## Telemetridata

OrniFlight sänder:
- VBAT spänning (huvudbatteri)
- Strömdragning / mAh förbrukad
- RSSI (signalstyrka)
- Flygläge / armstatus
- GPS-koordinater (om utrustad)
- Höjd/vario (om barometer)
- ONDAS flygprofil aktiv