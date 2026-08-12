# Summer

OrniFlight unterstützt aktive Summer zur akustischen Statusanzeige und zur Ortung verlorener Modelle.

## Funktionen

- **Aktivieren/Deaktivieren** — unterschiedliche Töne
- **Batterie schwach** — wiederholte Warntöne
- **Failsafe** — SOS Muster
- **Verlorenes Modell** — kontinuierlicher Piepton über den Schalter
- **GPS Fix** — Bestätigungston bei der Satellitensperre
- **Kalibrierung** — Signaltonmuster während der Kreisel-/Beschleunigungskalibrierung
- **RX Signal verloren** — Warnung, wenn die Empfängerverbindung unterbrochen wird

## Hardware

- Schließen Sie einen aktiven 5-V-Summer (KEIN passiver Piezo) an die Pads **BUZZ-** und **BUZZ+** an
- Der Summer wird von einem Transistor auf dem FC — angesteuert. Für Standard-Summer ist kein externer Treiber erforderlich

## CLI Einstellungen

```
beeper -GYRO_CALIBRATED     # Disable gyro calibration beeps
beeper -RX_LOST             # Enable receiver lost warning
beeper -ON_USB              # Disable beeper when USB connected
```

## Ornithopter-Sicherheit

Der Piepser ist besonders nützlich für große Ornithopter, die möglicherweise in hohem Gras oder Laub landen. Konfigurieren Sie den BEEPER-Modus über einen Taster, um ihn bei Bedarf schnell zu aktivieren.