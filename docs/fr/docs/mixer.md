# Mélangeur

Le mélangeur traduit les sorties du contrôleur de vol (roulis, tangage, lacet, accélérateur) en signaux d'asservissement pour votre ornithoptère.

## Mélangeur d'ornithoptères

OrniFlight étend le système de mixage de Betaflight avec des configurations spécifiques aux ornithoptères. Le mixeur gère :

- **Servos d'aile** : Convertissez la sortie PID en modulation de course d'aile
- **Servos de queue** (en option) : Contrôlez les surfaces de profondeur/gouvernail de direction

## Types de mélangeurs

| Mélangeur | Cas d'utilisation |
|-------|--------------|
| **ORNITHOPTER** | Ornithoptère standard à double aile avec 2 servos d'aile |
| **ORNITHOPTER_4S** | Ornithoptère à 4 servos (commande indépendante des ailes gauche/droite) |
| **ORNITHOPTER_TAIL** | Double aile + élévateur de queue + gouvernail |

## Configuration des servos

Configuré dans l'onglet **Servos** ou via CLI :

```
smix reverse 0 2 r       # Reverse servo 2
smix 0 0 0 100 0 0 100   # Servo 0: roll mixing
smix 1 1 1 100 0 0 100   # Servo 1: pitch mixing
```

## ONDAS Intégration

Le mélangeur fonctionne de concert avec ONDAS (Ornithopter Nonlinear Dynamic Aerodynamic System) :

- **Throttle** → définit l'amplitude du battement de base
- **ONDA Cadence** → décale la fenêtre de modulation à chaque coup
- **ONDA Ferocity** → modifie la forme de la forme d'onde de course (sinusoïdale ↔ trapézoïdale)
- **ONDA Balance** → correction de symétrie des ailes gauche/droite

Pour une théorie détaillée de ONDAS, consultez le [ONDAS Wiki](../wiki/ondas.html).

## Paramètres CLI

```
mixer = ORNITHOPTER
set servo_pwm_rate = 330     # Servo update frequency
set servo_center_pulse = 1500
set flap_spread = 20         # Wing angle amplitude in degrees
```