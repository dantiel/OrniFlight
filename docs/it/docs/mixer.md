# Miscelatore

Il mixer traduce le uscite del controller di volo (rollio, beccheggio, imbardata, acceleratore) in segnali servo per il tuo ornitottero.

## Miscelatore di ornitotteri

OrniFlight estende il sistema mixer di Betaflight con configurazioni specifiche per gli ornitotteri. Il mixer gestisce:

- **Servi ala**: converte l'uscita PID in modulazione della corsa dell'ala
- **Servi di coda** (opzionale): controlla le superfici dell'elevatore/timone

## Tipi di mixer

| Miscelatore | Caso d'uso |
|-------|----------|
| **ORNITHOPTER** | Ornitottero standard a doppia ala con 2 servi alari |
| **ORNITHOPTER_4S** | Ornitottero a 4 servi (comando indipendente dell'ala sinistra/destra) |
| **ORNITHOPTER_TAIL** | Doppia ala + elevatore di coda + timone |

## Configurazione del servo

Configurato nella scheda **Servi** o tramite CLI:

```
smix reverse 0 2 r       # Reverse servo 2
smix 0 0 0 100 0 0 100   # Servo 0: roll mixing
smix 1 1 1 100 0 0 100   # Servo 1: pitch mixing
```

## ONDAS Integrazione

Il mixer funziona di concerto con ONDAS (Ornithopter Nonlinear Dynamic Aerodynamic System):

- **Throttle** → imposta l'ampiezza del battito di base
- **ONDA Cadence** → sposta la finestra di modulazione all'interno di ogni colpo
- **ONDA Ferocity** → modifica la forma della forma d'onda del tratto (sinusoidale ↔ trapezoidale)
- **ONDA Balance** → correzione simmetria ala sinistra/destra

Per la teoria dettagliata di ONDAS, vedere il [ONDAS Wiki](../wiki/ondas.html).

## CLI Impostazioni

```
mixer = ORNITHOPTER
set servo_pwm_rate = 330     # Servo update frequency
set servo_center_pulse = 1500
set flap_spread = 20         # Wing angle amplitude in degrees
```