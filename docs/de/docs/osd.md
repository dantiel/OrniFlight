# Bildschirmanzeige (OSD)

OrniFlight verfügt über ein integriertes OSD (On-Screen-Display) mit dem MAX7456- oder AT7456E-Chip. Der OSD überlagert Flugdaten mit Ihrem FPV-Video-Feed.

## Unterstützte Elemente

Konfigurieren Sie Elemente auf der Registerkarte **OSD** des OrniFlight-Konfigurators. Ziehen Sie Elemente per Drag-and-Drop, um sie auf dem Bildschirm zu positionieren.

### Flugdaten

| Element | Zeigt |
|---------|----------|
| Batteriespannung | Hauptbatteriespannung (z. B. 14,8 V) |
| Durchschnittliche Zellspannung | Spannung pro Zelle (z. B. 3,7 V) |
| Aktuelle Auslosung | Momentanverstärker |
| mAh gezogen | Kumulierte verbrauchte Kapazität |
| RSSI | Signalstärke vom Empfänger |
| Flugmodus | Aktueller Modus (INDEPENDENT, GLIDE usw.) |
| Drosselklappenposition | Aktueller Drosselungsprozentsatz |
| Timer | Flugzeit / bewaffnete Zeit |
| Handwerksname | OrniFlight Handwerksname |

### Ornithopter-spezifisch

| Element | Zeigt |
|----------|----------|
| Schlagfrequenz | Aktuelle Flügelschlagfrequenz in Hz |
| ONDAS Profil | Aktive Flugprofilnummer (1-3) |
| Cadence Phase | Aktueller Modulationsphasenversatz |
| Servowinkel | Flügelservoposition |

## Schriftartenverwaltung

Der OSD verwendet ein zeichenbasiertes Anzeigesystem. Die Registerkarte **OSD** des OrniFlight-Konfigurators enthält einen **Font-Manager** zum Hochladen benutzerdefinierter Schriftarten und Glyphen.

## CLI Einstellungen

```
set osd_units = METRIC
set osd_warn_bitmask = 270335  # Warning flag bitmask
set osd_tim1 = 2560            # Timer 1 source
set osd_tim2 = 2561            # Timer 2 source
```

## Hardware

Derzeit unterstützter OSD-Chip: **AT7456E** (auf OMNIBUSF4 und kompatiblen Boards zu finden). MAX7456 ist kompatibel und wird automatisch erkannt.