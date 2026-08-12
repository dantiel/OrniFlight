# Buzzer

OrniFlight prend en charge les buzzers actifs pour l'indication sonore de l'état et la localisation du modèle perdu.

## Fonctions

- **Armer/Désarmer** — tonalités distinctes
- **Batterie faible** — répétant des bips d'avertissement
- Modèle **Failsafe** — SOS
- **Modèle perdu** — bip continu via le commutateur
- **GPS Fix** tonalité de confirmation — sur le verrouillage satellite
- **Calibration** Modèles de bips — pendant l'étalonnage du gyroscope/accélération
- **RX Signal perdu** avertissement — lorsque la connexion du récepteur est interrompue

## Matériel

- Connectez un buzzer actif 5 V (PAS un piézo passif) aux pads **BUZZ-** et **BUZZ+**
- Le buzzer est piloté par un transistor sur le FC — aucun pilote externe n'est nécessaire pour les buzzers standards

## CLI Paramètres

```
beeper -GYRO_CALIBRATED     # Disable gyro calibration beeps
beeper -RX_LOST             # Enable receiver lost warning
beeper -ON_USB              # Disable beeper when USB connected
```

## Sécurité des ornithoptères

Le bip est particulièrement utile pour les gros ornithoptères qui peuvent atterrir dans les herbes hautes ou le feuillage. Configurez le mode BEEPER sur un interrupteur momentané pour une activation rapide en cas de besoin.