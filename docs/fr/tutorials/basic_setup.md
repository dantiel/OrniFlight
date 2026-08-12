# Configuration de base

> *Configurez votre ornithoptère pour le premier vol.*

## Liste de contrôle avant le vol

Avant toute chose :

- [ ] Flight controller flashed with OrniFlight
- [ ] Récepteur lié à l'émetteur
-[ ] Servos connectés pour corriger les sorties PWM
- [ ] Batterie connectée (ailes sécurisées !)

## Configuration du récepteur

### CRSF (Recommandé)

1. **Onglet Ports** : définissez UART (par exemple UART1) sur « Série RX »
2. **Onglet Configuration** : Mode récepteur = "Récepteur série", Fournisseur = "CRSF"
3. Redémarrez et vérifiez que les entrées de canal se déplacent dans l'onglet Récepteur.

### SBUS / Autre

Même processus — sélectionnez le protocole approprié dans l'onglet Configuration.

## Cartographie des servos

Dans l'onglet **Servos** :

| Servomoteur | Fonction | Taux par défaut |
|-------|----------|-------------|
| Servo 0 | Aile gauche | 250 Hz |
| Servo 1 | Aile droite | 250 Hz |
| Servo 2 | Crête/Gouvernail | 50 Hz |

Ajustez min/max/milieu en fonction de la plage de votre servo. Testez avec "Override" pour vérifier la direction.

## Sélection du mode de vol

Dans l'**onglet Modes** :

1. **ARM** : Attribuer à un commutateur (sécurité !)
2. **ORNITHOPTER INDEPENDENT** ou **ORNITHOPTER GLIDE** : Choisissez votre mode de vol principal
3. **ORNITHOPTER PROFILE** : attribution facultative de — pour le changement de profil en vol

## ONDAS Premier réglage

Accédez au **sous-onglet Avancé → ONDAS** :

1. **Cadence Gain** : Commencez à 50 (moyen). C'est le paramètre le plus important.
2. **Ferocity D Gain** : Commencez à 30. Il s'agit de votre stabilisation principale.
3. **Ferocity P Gain** : Commencez à 20 pour le roulis/tangage, 0 pour le lacet.
4. **Balance Gain** : 0 (centré).

Branchez une batterie, **fixez fermement l'ornithoptère** et ARM. Observez le mouvement du servo —, il doit être un battement lisse et sinusoïdal.

## Premier vol

1. Start with a gentle toss into wind
2. Utilisez le mode GLIDE pour une sensation de vol naturelle
3. Utilisez le mode INDEPENDENT lorsque vous souhaitez un contrôle direct de la fréquence
4. Atterrissez, ajustez ONDAS, répétez

---

*Suivant : [Guide de réglage ONDAS](ondas_tuning.html) →*