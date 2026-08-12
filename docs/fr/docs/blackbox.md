# Journalisation de la boîte noire

Blackbox enregistre les données de vol pour l'analyse, le réglage et le débogage après le vol. OrniFlight prend en charge la connexion à la puce flash intégrée ou au périphérique OpenLog externe.

## Ce qui est enregistré

- **Gyro** — vitesse angulaire brute et filtrée sur 3 axes
- **Accéléromètre** — accélération sur 3 axes
- **PID Sortie** — Contributions P, I, D, F par axe
- **ONDAS** — Cadence, Ferocity P/D et autres paramètres spécifiques au battement
- **Commandes RC** Positions des sticks — après les tarifs/expo
- **Sortie servo** Sortie finale — vers chaque canal de servo
- **Batterie** tension et courant — par itération
- **GPS** — position, vitesse, altitude (si disponible)

## Configuration

### Flash intégré (OMNIBUSF4)

Le OMNIBUSF4 comprend 16 Mo de mémoire flash intégrée pour la journalisation Blackbox. Activer dans le configurateur :

1. Onglet **Blackbox** → Définissez `Blackbox logging device` sur `Onboard flash`
2. Définissez le taux de journalisation (recommandé : `1/N` avec N=2-4 pour les cibles F4)
3. Attribuez un commutateur pour démarrer/arrêter la journalisation

### OpenLog externe

Connectez OpenLog à une broche UART TX gratuite :

1. Onglet **Ports** → Réglez le UART sur `Blackbox logging` à 115 200 bauds
2. Connectez OpenLog : FC TX → OpenLog RX, plus 5 V/GND

## Outils d'analyse

- [Blackbox Explorer](https://github.com/betaflight/blackbox-log-viewer) visionneuse de journaux basée sur le Web —
- `blackbox_decode` — converti en CSV pour une analyse personnalisée

## ONDAS-Spécifique

Blackbox est essentiel pour régler les paramètres de ONDAS. Les données ONDAS enregistrées incluent :
- synchronisation de la fenêtre de modulation `ondas_cadence_phase` —
- composants de poussée asymétriques `ondas_ferocity_p` / `ondas_ferocity_d` —
- `ondas_balance` — équilibre aile gauche/droite
- Sortie par servo à chaque itération

Cela permet une analyse précise de la mécanique des battements et des corrections d’asymétrie des ailes.