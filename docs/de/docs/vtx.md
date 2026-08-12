# Videosender (VTX)

OrniFlight unterstützt die VTX-Steuerung für FPV-Ornithopter. VTX-Module können über den OrniFlight-Konfigurator, MSP oder CLI — konfiguriert werden, indem Band, Kanal, Leistungspegel und Pit-Modus eingestellt werden.

## Unterstützte Protokolle

1. **IRC Tramp** — Häufig bei kleinen VTX-Modulen, ideal für leichte FPV-Ornithopter
2. **TBS SmartAudio** — Digitales Protokoll mit Pit-Modus-Unterstützung
3. **RTC6705** — Direkte SPI-Steuerung auf Platinen mit integriertem VTX (z. B. SPRACINGF3NEO)

## Konfiguration

Die Einstellungen von VTX werden über die Registerkarte **VTX** im OrniFlight-Konfigurator oder über CLI verwaltet:

```
set vtx_band = 5           # Raceband
set vtx_channel = 1        # 5658 MHz
set vtx_power = 2          # 200mW
set vtx_low_power_disarm = ON  # Lower power when disarmed
set vtx_pit_mode_freq = 0  # Pit mode frequency (0 = disabled)
```

## Serieller Port

Für die VTX-Steuerung ist ein dedizierter UART TX-Pin erforderlich. Konfigurieren Sie den Port auf der Registerkarte **Ports** mit dem Peripheriegerät `IRC Tramp` oder `TBS SmartAudio`.

## FPV Überlegungen zum Ornithopter

- Gewicht ist entscheidend — wählen Sie leichte VTX-Module (Tramp Nano, Eachine Nano)
- Antennenmontage: Auf Abstand zu den Flügelschlägen achten
- Leistungsfilterung: Schließen Sie die VTX-Stromversorgung nach dem LC-Filter an, um Servogeräusche im Video zu vermeiden
- Für Prüfstandstests wird der Pit-Modus empfohlen, um eine Überhitzung kleiner VTX-Module zu vermeiden