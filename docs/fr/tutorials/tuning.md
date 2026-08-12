# PID Réglage

OrniFlight utilise un contrôleur PID (Proportionnel-Intégral-Dérivé) adapté au vol à ailes battantes. Le réglage diffère considérablement de celui des avions conventionnels en raison de la nature périodique de la poussée battante.

## Ornithoptère PID Bases

Contrairement aux avions conventionnels où la poussée est presque continue, la poussée des ornithoptères oscille à chaque coup d'aile. Cela crée :

- **Ondulation de poussée** à la fréquence de battement (généralement 5–15 Hz)
- **Autorité de contrôle dépendante de la phase** — la même sortie PID a un effet différent selon l'endroit où elle est appliquée dans le cycle de course.
- **Dynamique roulis-lacet couplée** La poussée asymétrique de l'aile — affecte les deux axes simultanément

## PID Conditions

| Terme | Effet | Note sur les ornithoptères |
|------|--------|-----------------|
| **P** | Correction immédiate proportionnelle — | Utilisez des valeurs conservatrices ; l'oscillation est synchrone au battement |
| **Je** | Correction d'erreur persistante intégrale — | Indispensable pour maintenir l'attitude lors des glissades |
| **D** | La dérivée — amortit les oscillations | Adapté à la cadence de l'aile et non aux oscillations du cadre |
| **F** | Feed-forward — collage direct sur la sortie | Utile pour une réponse nette sur l'axe de roulis |

## Valeurs de départ

Pour un ornithoptère de taille moyenne (1–1,5m d'envergure) :

| Axe | P | Je | D | F |
|------|---|---|---|---|
| Rouleau | 25 | 30 | 15 | 30 |
| Emplacement | 30 | 35 | 20 | 35 |
| Lacet | 40 | 35 | 10 | 20 |

## Procédure de réglage

### 1. Le réglage du taux en premier

Avant le réglage PID, définissez des taux qui vous conviennent :
- Commencez avec RC Taux 0,90, Super Taux 0,65, Expo 0,30
- Ajustez-le en fonction de votre style de vol et de la taille de votre ornithoptère

### 2. Gain P

Augmentez P jusqu'à ce que vous voyiez une oscillation à la fréquence de battement, puis réduisez de 20 % :
- Oscillation en roulis : oscillation de l'aile à la cadence
- Oscillation de tangage : oscillation d'avant en arrière
- Oscillation de lacet : remuement de la queue synchronisé avec les coups

### 3. Gain D

Augmentez D pour amortir le rebond après des entrées brusques avec le stick :
- Trop : jitter des servos, surchauffe
- Trop peu : sonnerie après l'arrêt du roulis/tangage

### 4. Je gagne

Je gagne des compteurs dérive persistante :
- Augmenter jusqu'à éliminer la dérive
- Trop : oscillation lente à 1–2 Hz (en dessous du taux de battement)

## ONDAS Intégration

ONDAS (Ornithopter Nonlinear Dynamic Aerodynamic System) module la sortie PID dans chaque coup d'aile. Après le réglage de base de PID :

1. Réglez **Cadence Gain** — déplace la fenêtre de modulation sur une phase aérodynamiquement optimale
2. Réglez **Ferocity P** — sur-boost asymétrique immédiat
3. Définir **Ferocity D** — exploitation anticipée du glisser
4. Affinez la symétrie de l'aile gauche/droite **Balance** —

Voir le [Guide de réglage ONDAS](ondas_tuning.html) pour la procédure détaillée.

## Analyse de la boîte noire

Activez la journalisation Blackbox pour visualiser les performances de PID. Recherchez :
- **Oscillation du terme P** à la fréquence de battement → réduit P
- **Remontage du terme I** pendant les virages soutenus → réduire le terme I ou augmenter la relaxation du terme I
- **Bruit de terme D** provenant des vibrations →, vérifiez d'abord l'équilibre mécanique, puis réduisez D

## Profils de vol

OrniFlight prend en charge 3 profils de vol commutables en cours de vol :

| Profil | Cas d'utilisation |
|---------|----------|
| 1 | Croisière standard |
| 2 | Haute agilité / agressif |
| 3 | Efficacité / envolée thermique |