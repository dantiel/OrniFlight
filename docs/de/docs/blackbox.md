# Blackbox-Protokollierung

Blackbox zeichnet Flugdaten für die Analyse, Optimierung und Fehlerbehebung nach dem Flug auf. OrniFlight unterstützt die Protokollierung auf dem integrierten Flash-Chip oder einem externen OpenLog-Gerät.

## Was protokolliert wird

- **Gyro** — rohe und gefilterte 3-Achsen-Winkelgeschwindigkeit
- **Beschleunigungsmesser** — 3-Achsen-Beschleunigung
- **PID Ausgabe** — P-, I-, D-, F-Beiträge pro Achse
- **ONDAS** — Cadence, Ferocity P/D und andere flatternspezifische Parameter
- **RC Befehle** — Stickpositionen nach Kursen/Expo
- **Servoausgang** — endgültiger Ausgang an jeden Servokanal
- **Batterie** — Spannung und Strom pro Iteration
- **GPS** — Position, Geschwindigkeit, Höhe (sofern verfügbar)

## Einrichtung

### Onboard-Flash (OMNIBUSF4)

Der OMNIBUSF4 verfügt über 16 MB Onboard-Flash für die Blackbox-Protokollierung. Im Konfigurator aktivieren:

1. **Blackbox**-Registerkarte → Setzen Sie `Blackbox logging device` auf `Onboard flash`
2. Protokollierungsrate festlegen (empfohlen: `1/N` mit N=2-4 für F4-Ziele)
3. Weisen Sie einen Schalter zum Starten/Stoppen der Protokollierung zu

### Extern OpenLog

Verbinden Sie OpenLog mit einem kostenlosen UART TX-Pin:

1. Registerkarte **Ports** → Stellen Sie UART auf `Blackbox logging` bei 115200 Baud ein
2. Verbinden Sie OpenLog: FC TX → OpenLog RX, plus 5V/GND

## Analysetools

- [Blackbox Explorer](https://github.com/betaflight/blackbox-log-viewer) — webbasierter Protokoll-Viewer
- `blackbox_decode` — zur benutzerdefinierten Analyse in CSV konvertieren

## ONDAS-spezifisch

Blackbox ist für die Optimierung der ONDAS-Parameter unerlässlich. Zu den protokollierten ONDAS-Daten gehören:
- `ondas_cadence_phase` — Modulationsfenster-Timing
- `ondas_ferocity_p` / `ondas_ferocity_d` — asymmetrische Schubkomponenten
- `ondas_balance` — linker/rechter Flügelausgleich
- Pro-Servo-Ausgabe bei jeder Iteration

Dies ermöglicht eine präzise Analyse der Schlagmechanik und Flügelasymmetriekorrekturen.