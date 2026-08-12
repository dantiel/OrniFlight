# Mikser

Mikser prevodi izlaze kontrolera leta (okretanje, nagib, skretanje, gas) u servo signale za vaš ornitopter.

## Mješalica za ornitopter

OrniFlight proširuje Betaflightov sustav miksera konfiguracijama specifičnim za ornitopter. Ručke miješalice:

- **Servo krila**: Pretvorite izlaz PID u modulaciju zamaha krila
- **Repni servos** (opcionalno): Upravljajte površinama visine/kormila

## Vrste miksera

| Mikser | Slučaj upotrebe |
|-------|----------|
| **ORNITHOPTER** | Standardni dvokrilni ornitopter s 2 servo krila |
| **ORNITHOPTER_4S** | 4-servo ornitopter (neovisna kontrola lijevog/desnog krila) |
| **ORNITHOPTER_TAIL** | Duplo krilo + repno podizanje + kormilo |

## Servo konfiguracija

Konfigurirano u kartici **Servos** ili putem CLI:

```
smix reverse 0 2 r       # Reverse servo 2
smix 0 0 0 100 0 0 100   # Servo 0: roll mixing
smix 1 1 1 100 0 0 100   # Servo 1: pitch mixing
```

## ONDAS Integracija

Mikser radi zajedno sa ONDAS (Ornithopter nelinearni dinamički aerodinamički sustav):

- **Throttle** → postavlja osnovnu amplitudu mahanja
- **ONDA Cadence** → pomiče prozor modulacije unutar svakog poteza
- **ONDA Ferocity** → modificira valni oblik hoda (sinusoidni ↔ trapezoidni)
- **ONDA Balance** → korekcija simetrije lijevog/desnog krila

Za detaljnu ONDAS teoriju pogledajte [ONDAS Wiki](../wiki/ondas.html).

## CLI Postavke

```
mixer = ORNITHOPTER
set servo_pwm_rate = 330     # Servo update frequency
set servo_center_pulse = 1500
set flap_spread = 20         # Wing angle amplitude in degrees
```