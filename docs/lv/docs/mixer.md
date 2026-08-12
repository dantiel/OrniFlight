# Mikseris

Mikseris pārvērš lidojuma kontroliera izejas (slīpu, slīpumu, pagriezienu, droseļvārstu) jūsu ornitoptera servo signālos.

## Ornitoptera mikseris

OrniFlight paplašina Betaflight maisītāju sistēmu ar ornitopteram specifiskām konfigurācijām. Miksera rokturi:

- **Spārnu servoelementi**: pārveidojiet PID izvadi par spārna gājiena modulāciju
- **Astes servosistēmas** (pēc izvēles): kontrolējiet lifta/stūres virsmas

## Mikseru veidi

| Mikseris | Lietošanas gadījums |
|-------|-----------|
| **ORNITHOPTER** | Standarta divu spārnu ornitopteris ar 2 spārnu servo |
| **ORNITHOPTER_4S** | 4-servo ornitopteris (neatkarīga kreisā/labā spārna vadība) |
| **ORNITHOPTER_TAIL** | Divspārnu + astes lifts + stūre |

## Servo konfigurācija

Konfigurēts cilnē **Servos** vai caur CLI:

```
smix reverse 0 2 r       # Reverse servo 2
smix 0 0 0 100 0 0 100   # Servo 0: roll mixing
smix 1 1 1 100 0 0 100   # Servo 1: pitch mixing
```

## ONDAS Integrācija

Mikseris darbojas kopā ar ONDAS (Ornitoptera nelineārā dinamiskā aerodinamiskā sistēma):

- **Drosele** → iestata bāzes svārstību amplitūdu
- **ONDA Cadence** → maina modulācijas logu katrā gājienā
- **ONDA Ferocity** → maina gājiena viļņu formu (sinusoidāla ↔ trapecveida)
- **ONDA Balance** → kreisā/labā spārna simetrijas korekcija

Detalizētu ONDAS teoriju skatiet [ONDAS Wiki](../wiki/ondas.html).

## CLI iestatījumi

```
mixer = ORNITHOPTER
set servo_pwm_rate = 330     # Servo update frequency
set servo_center_pulse = 1500
set flap_spread = 20         # Wing angle amplitude in degrees
```