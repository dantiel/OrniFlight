# Mixer

Der Mixer wandelt die Ausgänge der Flugsteuerung (Rollen, Nicken, Gieren, Gas) in Servosignale für Ihren Ornithopter um.

## Ornithopter-Mischer

OrniFlight erweitert das Mixersystem von Betaflight um Ornithopter-spezifische Konfigurationen. Der Mixer verarbeitet:

- **Flügelservos**: Wandeln Sie den PID-Ausgang in Flügelhubmodulation um
- **Heckservos** (optional): Steuern Höhenruder/Ruderoberflächen

## Mixertypen

| Mixer | Anwendungsfall |
|-------|----------|
| **ORNITHOPTER** | Standard-Doppelflügel-Ornithopter mit 2 Flügelservos |
| **ORNITHOPTER_4S** | 4-Servo-Ornithopter (unabhängige linke/rechte Flügelsteuerung) |
| **ORNITHOPTER_TAIL** | Doppelflügel + Heckhöhenruder + Seitenruder |

## Servokonfiguration

Konfiguriert im Reiter **Servos** oder über CLI:

```
smix reverse 0 2 r       # Reverse servo 2
smix 0 0 0 100 0 0 100   # Servo 0: roll mixing
smix 1 1 1 100 0 0 100   # Servo 1: pitch mixing
```

## ONDAS Integration

Der Mischer arbeitet mit ONDAS (Ornithopter Nonlinear Dynamic Aerodynamic System) zusammen:

- **Gas** → legt die Grundschlagamplitude fest
- **ONDA Cadence** → verschiebt das Modulationsfenster innerhalb jedes Strichs
- **ONDA Ferocity** → ändert die Form der Schlagwellenform (sinusförmig, ↔ trapezförmig)
- **ONDA Balance** → Korrektur der linken/rechten Flügelsymmetrie

Eine detaillierte ONDAS-Theorie finden Sie im [ONDAS Wiki](../wiki/ondas.html).

## CLI Einstellungen

```
mixer = ORNITHOPTER
set servo_pwm_rate = 330     # Servo update frequency
set servo_center_pulse = 1500
set flap_spread = 20         # Wing angle amplitude in degrees
```