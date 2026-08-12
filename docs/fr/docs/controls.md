# Contrôles

OrniFlight utilise le mappage de bâtons RC standard avec des extensions spécifiques aux ornithoptères.

## Cartographie des bâtons

| Bâton | Axe | Effet primaire |
|-------|------|--------------------|
| Accélérateur (gauche, vertical) | Accélérateur | Amplitude / poussée de battement |
| Lacet (gauche, horizontal) | Lacet | Poussée différentielle des ailes pour tourner |
| Pas (droite, vertical) | Emplacement | Inclinaison avant/arrière |
| Rouleau (droite, horizontal) | Rouleau | Banque gauche/droite |

## Modes de vol

| Mode | Comportement du bâton |
|------|--------------------|
| **ACRO** | Les bâtons contrôlent la vitesse angulaire — pas de niveau automatique |
| **ANGLE** | Colle l'angle de contrôle — automatiquement au niveau lorsqu'il est relâché |
| **HORIZON** | ANGLE près du centre, ACRO en pleine déviation |

ACRO est recommandé aux pilotes expérimentés. ANGLE est bon pour les premiers vols et le vol thermique.

## Contrôles spécifiques aux ornithoptères

### Mode INDEPENDENT

Lorsque le mode INDEPENDENT est actif, chaque servo d'aile répond indépendamment :
- **stick gauche** servos d'aile gauche →
- **stick droit** servos de l'aile droite →
- Permet un battement asymétrique pour des manœuvres agressives

### Mode GLIDE

Le mode GLIDE verrouille les deux ailes en position horizontale. L'ornithoptère devient un planeur :
- **La manette des gaz** n'a aucun effet sur la position de l'aile
- **Pitch/Roll/Yaw** influence toujours les gouvernes de queue (si équipé)

### Changement de profil

La commutation de profil en vol via le canal AUX permet de modifier les paramètres PID/ONDAS en cours de vol :
- **Profil 1** : Paramètres de croisière standard
- **Profil 2** : paramètres de haute agilité
- **Profil 3** : Paramètres efficacité/glisse

## Tarifs

Configurez les tarifs dans l'onglet **PID Tuning**. Pour les ornithoptères, commencez par des taux conservateurs. La dynamique de battement — amplifie les entrées de contrôle :
- Tarif RC : 0,80–1,00
- Super tarif : 0,60–0,70
- Expo : 0,20–0,40