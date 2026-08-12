# Surveillance de la batterie

OrniFlight surveille la tension de la batterie principale via le ADC (convertisseur analogique-numérique). Cela permet des avertissements de batterie faible via le buzzer, les modèles de bande d'état LED et LED.

## Fonctionnalités

- Détection automatique du nombre de cellules lors de la connexion (basée sur les tensions min/max des cellules)
- Avertissement de batterie faible avec seuils configurables
- Détection de courant pour la consommation mAh (si pris en charge par FC)
- Tension affichée en OSD et transmise par télémétrie

## Cibles prises en charge

Tous les contrôleurs de vol pris en charge (OMNIBUSF4, TINYFISH) incluent la surveillance VBAT via un diviseur de tension.

## Connexions

**TOUJOURS VÉRIFIER LA POLARITÉ.** Mesurez les tensions attendues avant de connecter. Une tension incorrecte ou une polarité inversée détruira votre contrôleur de vol.

### OMNIBUSF4

Connectez la batterie principale au pad VBAT. Le diviseur de tension intégré gère directement jusqu'à 6S.

### TINYFISH

VBAT est acheminé via l'entrée d'alimentation de la carte —, aucune connexion séparée n'est nécessaire.

## CLI Paramètres

```
set vbat_min_cell_voltage = 330       # Minimum per-cell voltage (3.3V)
set vbat_max_cell_voltage = 430       # Maximum per-cell voltage (4.3V)
set vbat_warning_cell_voltage = 350   # Warning threshold (3.5V)
set battery_meter_type = ADC
set current_meter_type = ADC          # If current sensor available
```

## Sécurité

Les batteries LiPo ne doivent jamais être déchargées en dessous de 3,5 V par cellule sous charge. Les seuils configurables du OrniFlight contribuent à garantir un fonctionnement sûr et la longévité de la batterie.