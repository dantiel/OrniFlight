# Grundeinrichtung

> *Konfigurieren Sie Ihren Ornithopter für den Erstflug.*

## Checkliste vor dem Flug

Vor allem:

- [ ] Flugcontroller blinkte mit OrniFlight
- [ ] Empfänger an Sender gebunden
- [ ] Servos an korrekte PWM-Ausgänge angeschlossen
- [ ] Batterie angeschlossen (Flügel gesichert!)

## Empfänger-Setup

### CRSF (empfohlen)

1. **Registerkarte „Ports“**: Setzen Sie UART (z. B. UART1) auf „Seriell RX“.
2. **Registerkarte „Konfiguration“**: Empfängermodus = „Serieller Empfänger“, Anbieter = „CRSF“
3. Schalten Sie das Gerät aus und wieder ein und überprüfen Sie, ob sich die Kanaleingänge auf der Registerkarte „Empfänger“ bewegen

### SBUS / Andere

Gleicher Vorgang — Wählen Sie auf der Registerkarte „Konfiguration“ das entsprechende Protokoll aus.

## Servozuordnung

Auf der **Registerkarte „Servos“**:

| Servo | Funktion | Standardtarif |
|-------|----------|-------------|
| Servo 0 | Linker Flügel | 250 Hz |
| Servo 1 | Rechter Flügel | 250 Hz |
| Servo 2 | Kamm/Ruder | 50 Hz |

Passen Sie Min/Max/Mittel an die Reichweite Ihres Servos an. Testen Sie mit „Override“, um die Richtung zu überprüfen.

## Auswahl des Flugmodus

Im **Register „Modi“**:

1. **ARM**: Einem Schalter zuweisen (Sicherheit!)
2. **ORNITHOPTER INDEPENDENT** oder **ORNITHOPTER GLIDE**: Wählen Sie Ihren primären Flugmodus
3. **ORNITHOPTER PROFILE**: Optionale —-Zuweisung für den Profilwechsel während des Flugs

## ONDAS Erstes Tuning

Gehen Sie zur Unterregisterkarte „Erweitert → ONDAS“**:

1. **Cadence Gain**: Beginnen Sie bei 50 (Mitte). Dies ist der wichtigste Parameter.
2. **Ferocity D Gain**: Beginnen Sie bei 30. Dies ist Ihre primäre Stabilisierung.
3. **Ferocity P Gain**: Beginnen Sie bei 20 für Roll/Nick, 0 für Gier.
4. **Balance Gain**: 0 (zentriert).

Schließen Sie eine Batterie an, **sichern Sie den Ornithopter fest** und ARM. Beobachten Sie die Servobewegung —, sie sollte gleichmäßig und sinusförmig schlagen.

## Erster Flug

1. Beginnen Sie mit einem sanften Wurf in den Wind
2. Verwenden Sie den GLIDE-Modus für ein natürliches Fluggefühl
3. Verwenden Sie den INDEPENDENT-Modus, wenn Sie eine direkte Frequenzsteuerung wünschen
4. Landen, ONDAS anpassen, wiederholen

---

*Weiter: [ONDAS Tuning Guide](ondas_tuning.html) →*