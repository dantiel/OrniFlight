# Telemetrie

Telemetrie sendet Flugdaten von OrniFlight an Ihren Funksender —, Batteriespannung, Strom, RSSI, GPS Koordinaten, Höhe und mehr.

## Unterstützte Protokolle

| Protokoll | Funksystem | Anzahl der Drähte |
|----------|-------------|------------|
| **CRSF** | Crossfire / Tracer / ELRS | Integriert mit RX (bidirektional) |
| **SmartPort** | FrSky | 1 Draht (TX Pin) |
| **HoTT** | Graupner | 1 Draht (TX+TZ) |
| **IBUS** | FlySky | 1 Draht (Sensor TX) |
| **LTM** | Lichttelemetrie (MWP) | 1 Draht (TX) |

## Konfiguration

1. Im Konfigurator → **Ports**: Stellen Sie den Pin UART TX auf das entsprechende Telemetrieprotokoll ein
2. Telemetriefunktion aktivieren: `feature TELEMETRY`
3. Konfigurieren Sie bei Bedarf die Telemetrieinversion

Für **CRSF** wird die Telemetrie automatisch verarbeitet, — kein separater Port erforderlich.

## SmartPort (FrSky)

SmartPort erfordert eine Signalinvertierung auf F4-Prozessoren. Entweder:
- Verwenden Sie einen Flugcontroller mit eingebautem Wechselrichter
- Verwenden Sie SoftSerial mit `set tlm_inversion = ON`

```
feature TELEMETRY
set tlm_inverted = ON
set tlm_halfduplex = ON
```

## Telemetriedaten

OrniFlight überträgt:
- VBAT Spannung (Hauptbatterie)
- Stromverbrauch / verbrauchte mAh
- RSSI (Signalstärke)
- Flugmodus/Armstatus
- GPS-Koordinaten (falls vorhanden)
- Höhe / Vario (falls Barometer)
- ONDAS Flugprofil aktiv