# Batterieüberwachung

OrniFlight überwacht die Hauptbatteriespannung über den ADC (Analog-zu-Digital-Wandler). Dies ermöglicht Warnungen bei niedrigem Batteriestand durch Summer, Statusstreifenmuster LED und LED.

## Funktionen

- Automatische Erkennung der Zellenzahl beim Verbinden (basierend auf den minimalen/maximalen Zellenspannungen)
- Warnung bei niedrigem Batteriestand mit konfigurierbaren Schwellenwerten
- Strommessung für mAh-Verbrauch (sofern von FC unterstützt)
- Spannung wird in OSD angezeigt und per Telemetrie übertragen

## Unterstützte Ziele

Alle unterstützten Flugregler (OMNIBUSF4, TINYFISH) verfügen über eine VBAT-Überwachung per Spannungsteiler.

## Verbindungen

**PRÜFEN SIE IMMER DIE POLARITÄT.** Messen Sie die erwarteten Spannungen vor dem Anschließen. Falsche Spannung oder umgekehrte Polarität zerstören Ihren Flugregler.

### OMNIBUSF4

Schließen Sie den Hauptakku an das VBAT-Pad an. Der integrierte Spannungsteiler verarbeitet bis zu 6S direkt.

### TINYFISH

VBAT wird über den Stromeingang des Boards geleitet. — ist kein separater Anschluss erforderlich.

## CLI Einstellungen

```
set vbat_min_cell_voltage = 330       # Minimum per-cell voltage (3.3V)
set vbat_max_cell_voltage = 430       # Maximum per-cell voltage (4.3V)
set vbat_warning_cell_voltage = 350   # Warning threshold (3.5V)
set battery_meter_type = ADC
set current_meter_type = ADC          # If current sensor available
```

## Sicherheit

LiPo-Batterien sollten unter Last niemals unter 3,5 V pro Zelle entladen werden. Die konfigurierbaren Schwellenwerte von OrniFlight tragen dazu bei, einen sicheren Betrieb und eine lange Batterielebensdauer zu gewährleisten.