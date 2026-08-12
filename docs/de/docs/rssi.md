# RSSI

RSSI (Received Signal Strength Indicator) zeigt die Qualität Ihrer Funkverbindung an. OrniFlight kann RSSI vom analogen Eingang, seriellen Empfängerdaten oder dem Protokoll RSSI beziehen.

## RSSI Quellen

| Quelle | Verbindung | Konfiguration |
|--------|-----------|---------------|
| **Serielles Protokoll** | Keine (über serielles RX-Kabel) | CRSF, GHST — automatisch |
| **AUX Kanal** | Keine (TX sendet RSSI als Kanal) | `set rssi_channel = 8` |
| **Analog ADC** | RSSI Pad ein FC → Empfänger RSSI Ausgang | `set rssi_adc_channel = 1` |

## Konfiguration

### Seriennummer RSSI (CRSF/GHST/SBUS)

```
set rssi_src_frame_errors = OFF
set rssi_scale = 100
set rssi_offset = 0
```

RSSI wird automatisch über serielle Protokolle — übertragen, keine zusätzliche Verkabelung erforderlich.

### Analog RSSI

Verbinden Sie den Empfänger RSSI Ausgang → RSSI Pad am Flugcontroller:

```
set rssi_adc_channel = 1      # Use ADC channel 1
set rssi_scale = 100          # Scale to 0-100%
set rssi_offset = 0
```

### AUX Kanal RSSI

Konfigurieren Sie Ihren Sender so, dass er RSSI auf einem bestimmten Kanal sendet, und gehen Sie dann wie folgt vor:

```
set rssi_channel = 12         # Aux channel number
set rssi_scale = 100
set rssi_offset = 0
```

## Anzeige

RSSI wird im OSD angezeigt und kann per Telemetrie an Ihr Funkgerät übertragen werden. Warnschwellenwerte konfigurieren:

```
set osd_rssi_alarm = 20        # Warning at 20% RSSI
```

## Ornithopter Range

Für Ornithopter ist RSSI von entscheidender Bedeutung. — Flügelschlag erzeugt dynamische RF Interferenzmuster. Überwachen Sie RSSI während der ersten Testflüge, um die zuverlässige Verbindungsleistung in allen Flügelpositionen zu überprüfen.