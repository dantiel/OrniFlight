# Mixer

Mixern översätter flygkontrollerns utsignaler (rullning, pitch, gir, gas) till servosignaler för din ornithopter.

## Ornithopter Mixer

OrniFlight utökar Betaflights mixersystem med ornithopter-specifika konfigurationer. Mixern hanterar:

- **Vingservon**: Konvertera PID-utgång till vingslagsmodulering
- **Svansservon** (tillval): Styr hiss-/roderytor

## Blandartyper

| Mixer | Användningsfall |
|-------|--------|
| **ORNITHOPTER** | Standard dubbelvingad ornithopter med 2 vingar servon |
| **ORNITHOPTER_4S** | 4-servo ornithopter (oberoende vänster/höger vingkontroll) |
| **ORNITHOPTER_TAIL** | Dubbelvinge + baklyft + roder |

## Servokonfiguration

Konfigurerad på fliken **Servos** eller via CLI:

```
smix reverse 0 2 r       # Reverse servo 2
smix 0 0 0 100 0 0 100   # Servo 0: roll mixing
smix 1 1 1 100 0 0 100   # Servo 1: pitch mixing
```

## ONDAS Integration

Mixern fungerar tillsammans med ONDAS (Ornithopter Nonlinear Dynamic Aerodynamic System):

- **Throttle** → ställer in basflapping-amplituden
- **ONDA Cadence** → skiftar moduleringsfönstret inom varje slag
- **ONDA Ferocity** → modifierar slagvågformen (sinusformad ↔ trapetsformad)
- **ONDA Balance** → vänster/höger vingsymmetrikorrigering

För detaljerad ONDAS-teori, se [ONDAS Wiki](../wiki/ondas.html).

## CLI Inställningar

```
mixer = ORNITHOPTER
set servo_pwm_rate = 330     # Servo update frequency
set servo_center_pulse = 1500
set flap_spread = 20         # Wing angle amplitude in degrees
```