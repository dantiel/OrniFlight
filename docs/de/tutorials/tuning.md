# PID Tuning

OrniFlight verwendet einen PID-Controller (Proportional-Integral-Derivative), der für den Schlagflügelflug geeignet ist. Aufgrund der periodischen Natur des Schlagschubs unterscheidet sich die Abstimmung erheblich von herkömmlichen Flugzeugen.

## Ornithopter PID Grundlagen

Im Gegensatz zu herkömmlichen Flugzeugen, bei denen der Schub nahezu kontinuierlich ist, schwankt der Schub beim Ornithopter mit jedem Flügelschlag. Dadurch entsteht:

- **Schubwelligkeit** bei Schlagfrequenz (typischerweise 5–15 Hz)
- **Phasenabhängige Steuerautorität** — Derselbe PID-Ausgang hat unterschiedliche Auswirkungen, je nachdem, an welcher Stelle im Hubzyklus er angewendet wird
- **Gekoppelte Roll-Gier-Dynamik** — asymmetrischer Flügelschub wirkt sich auf beide Achsen gleichzeitig aus

## PID Bedingungen

| Begriff | Wirkung | Ornithopter-Hinweis |
|------|--------|-----------------|
| **P** | Proportionale — sofortige Korrektur | Verwenden Sie konservative Werte; Schwingung ist flattersynchron |
| **Ich** | Integrale — dauerhafte Fehlerkorrektur | Unverzichtbar für die Aufrechterhaltung der Fluglage beim Gleiten |
| **D** | Ableitung — dämpft Schwingungen | Auf Flügelschlagfrequenz abgestimmt, nicht auf Rahmenschwingungen |
| **F** | Feed-Forward — direkter Stick-to-Ausgang | Nützlich für eine klare Reaktion auf der Rollachse |

## Startwerte

Für einen mittelgroßen Ornithopter (1–1,5 m Flügelspannweite):

| Achse | P | Ich | D | F |
|------|---|---|---|---|
| Rolle | 25 | 30 | 15 | 30 |
| Tonhöhe | 30 | 35 | 20 | 35 |
| Gieren | 40 | 35 | 10 | 20 |

## Tuning-Verfahren

### 1. Rate-Tuning zuerst

Stellen Sie vor der Abstimmung von PID die Raten ein, die sich angenehm anfühlen:
- Beginnen Sie mit RC Rate 0,90, Super Rate 0,65, Expo 0,30
- Passen Sie es an Ihren Flugstil und die Größe Ihres Ornithopters an

### 2. P-Verstärkung

Erhöhen Sie P, bis Sie eine Schwingung mit Schlagfrequenz sehen, und reduzieren Sie sie dann um 20 %:
- Rolloszillation: Flügelwackeln bei Schlagfrequenz
- Pitch-Oszillation: Vorwärts- und Rückwärtswippen
- Gieroszillation: Schwanzwedeln synchronisiert mit den Bewegungen

### 3. D-Verstärkung

Erhöhen Sie D, um den Rückprall nach scharfen Steuerknüppeleingaben zu dämpfen:
- Zu viel: Servo-Jitter, Überhitzung
- Zu wenig: Klingeln nach Roll-/Nickstopps

### 4. Ich gewinne

Ich erhalte Zähler für anhaltende Drift:
- Erhöhen, bis die Drift beseitigt ist
- Zu viel: langsame Oszillation mit 1–2 Hz (unterhalb der Schlagfrequenz)

## ONDAS Integration

ONDAS (Ornithopter Nonlinear Dynamic Aerodynamic System) moduliert die PID-Ausgabe innerhalb jedes Flügelschlags. Nach der grundlegenden PID-Abstimmung:

1. Stellen Sie **Cadence Gain** — ein, um das Modulationsfenster auf die aerodynamisch optimale Phase zu verschieben
2. Stellen Sie **Ferocity P** — sofortigen asymmetrischen Schubschub ein
3. Legen Sie **Ferocity D** — vorausschauende Widerstandsausnutzung fest
4. Passen Sie **Balance** — linke/rechte Flügelsymmetrie an

Ausführliche Informationen zum Verfahren finden Sie im [ONDAS Tuning Guide](ondas_tuning.html).

## Blackbox-Analyse

Aktivieren Sie die Blackbox-Protokollierung, um die Leistung von PID zu visualisieren. Suchen Sie nach:
- **P-Term-Oszillation** bei Schlagfrequenz → P reduzieren
- **I-Term-Windup** bei anhaltenden Drehungen → Reduzieren Sie I oder erhöhen Sie I-Term-Relax
- **D-Term-Geräusch** durch Vibration → Überprüfen Sie zuerst das mechanische Gleichgewicht und reduzieren Sie dann D

## Flugprofile

OrniFlight unterstützt 3 Flugprofile, die während des Fluges umschaltbar sind:

| Profil | Anwendungsfall |
|---------|----------|
| 1 | Standardkreuzfahrt |
| 2 | Hohe Agilität / Aggressivität |
| 3 | Effizienz / Thermiksegelflug |