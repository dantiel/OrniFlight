# GPS

GPS ermöglicht Positionshalten, Rückkehr zur Heimat und telemetriebasierte Navigation für Ihren Ornithopter. GPS-Funktionen in OrniFlight sind funktionsfähig, gelten aber als experimentell. — fliegt immer in Sichtlinie.

## Unterstützte Protokolle

- **UBLOX** (empfohlen) — UBlox-Binärprotokoll, effizient und zuverlässig
- **NMEA** — Textbasiertes Standardprotokoll

## Hardware

- BN-880, BN-220 oder ähnliche UBlox M8N GPS+Compass-Module
- Anschluss: TX/RX an einen freien UART, plus 5V/GND
- Montieren Sie GPS entfernt von Stromkabeln und Servokabeln, um Störungen zu minimieren
- Kompass/Magnetometer müssen von magnetischen Quellen (Stromkabel, Servos) entfernt sein.

## Konfiguration

```
feature GPS
set gps_provider = UBLOX
set gps_sbas_mode = AUTO
set gps_auto_baud = ON
set gps_ublox_use_galileo = ON
```

1. Weisen Sie den seriellen Port GPS auf der Registerkarte **Ports** zu (Standard 115200 Baud für UBlox).
2. Aktivieren Sie die GPS-Funktion
3. Anbieter einstellen
4. Speichern und neu starten

## OSD Elemente

Zu den in OSD angezeigten Daten von GPS gehören:
- Satellitenanzahl und Fixtyp
- GPS-Koordinaten (Breitengrad/Längengrad)
- Geschwindigkeit über Grund
- Höhe (GPS)
- Entfernung von zu Hause
- Home-Richtungspfeil

## Überlegungen zum Ornithopter

- Die GPS-Antenne muss freie Sicht zum Himmel haben. Der —-Montageort ist bei Flügelschlägen von entscheidender Bedeutung
- Bei kleinen Ornithoptern ist der Gewichtsnachteil erheblich
- GPS-unterstütztes RTH (Return to Home) erfordert eine sorgfältige Abstimmung der Navigationswerte PID für die Schlagflugdynamik