# Empfänger (RX)

OrniFlight unterstützt mehrere Empfängerprotokolle zur Funksteuerung Ihres Ornithopters.

## Unterstützte Protokolle

| Protokoll | Geben Sie | ein Notizen |
|----------|------|-------|
| **CRSF** (Kreuzfeuer) | Seriell | Geringe Latenz, Telemetrie, empfohlen |
| **SBUS** | Seriell | Invertiert, benötigt Wechselrichter an F4 |
| **IBUS** (FlySky) | Seriell | Nicht invertiert, direkt UART |
| **PPM** | Single-Wire-Analog | 8ch, Legacy, nicht empfohlen |
| **SPEKTRUM** | Seriell | 1024/2048, binden über CLI |
| **FPORT** | Seriell | FrSky, kombiniert RX+Telemetrie |
| **GHST** (Geist) | Seriell | ImmersionRC, niedrige Latenz |

## Serielle RX-Konfiguration

1. Empfänger an einen freien UART RX Pin anschließen
2. Im Konfigurator → **Ports**: Setzen Sie UART auf `Serial RX`
3. Im Konfigurator → **Konfiguration**: Protokoll auswählen
4. Für SBUS auf F4: `set sbus_inversion = ON` aktivieren

## CLI Schnelleinrichtung

```
feature RX_SERIAL
set serialrx_provider = CRSF
set serialrx_inverted = OFF
set serialrx_halfduplex = OFF
save
```

## Ausfallsicher

Konfigurieren Sie die Ausfallsicherheit des Empfängers so, dass der Empfänger bei Signalverlust **keine Impulse** ausgibt. Der Fluglotse erkennt dies dann und aktiviert sein eigenes Failsafe-Verfahren. Siehe [Failsafe](failsafe.html) für die Konfiguration auf FC-Ebene.