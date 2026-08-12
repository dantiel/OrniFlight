# Mesclador

El mesclador tradueix les sortides del controlador de vol (roll, to, guiñada, acceleració) en senyals servo per al vostre ornitòpter.

## Mesclador d'ornitòpters

OrniFlight amplia el sistema de mescla de Betaflight amb configuracions específiques d'ornitòpters. El mesclador s'encarrega de:

- **Servos d'ala**: Converteix la sortida PID a la modulació de la carrera de l'ala
- **Servos de cua** (opcional): Control de superfícies d'elevador/timó

## Tipus de mescladors

| Mesclador | Cas d'ús |
|-------|----------|
| **ORNITHOPTER** | Ornitòpter estàndard de doble ala amb servos de 2 ales |
| **ORNITHOPTER_4S** | Ornitòpter de 4 servos (control independent de l'ala esquerra/dreta) |
| **ORNITHOPTER_TAIL** | Ala doble + elevador de cua + timó |

## Configuració del servo

Configurat a la pestanya **Servos** o mitjançant CLI:

```
smix reverse 0 2 r       # Reverse servo 2
smix 0 0 0 100 0 0 100   # Servo 0: roll mixing
smix 1 1 1 100 0 0 100   # Servo 1: pitch mixing
```

## ONDAS Integració

El mesclador funciona conjuntament amb ONDAS (Ornithopter Nonlinear Dynamic Aerodynamic System):

- **Acelerador** → estableix l'amplitud de bateig de la base
- **ONDA Cadence** → desplaça la finestra de modulació dins de cada traç
- **ONDA Ferocity** → modifica la forma d'ona del traç (sinusoïdal ↔ trapezoïdal)
- **ONDA Balance** → correcció de la simetria de l'ala esquerra/dreta

Per obtenir una teoria detallada de ONDAS, consulteu la [ONDAS Wiki](../wiki/ondas.html).

## CLI Configuració

```
mixer = ORNITHOPTER
set servo_pwm_rate = 330     # Servo update frequency
set servo_center_pulse = 1500
set flap_spread = 20         # Wing angle amplitude in degrees
```