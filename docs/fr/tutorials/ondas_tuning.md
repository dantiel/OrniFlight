# ONDAS Guide de réglage

> *Le compagnon pratique de la théorie ONDAS —, comment régler chaque paramètre au toucher.*

## Ordre de réglage

Les paramètres ONDAS sont interdépendants. Accordez-les dans cet ordre :

```
1. Cadence    →  timing
2. Ferocity D →  primary stabilization
3. Ferocity P →  response crispness
4. Balance    →  upstroke/downstroke bias
5. Warp       →  modulation width
6. Anchor     →  dry/wet mix
7. Resonance  →  cycle-to-cycle memory
8. Phase 2    →  advanced (prescience, espelho, saudade, SSFF)
```

## Étape par étape

### 1. Cadence — Trouvez votre fenêtre de phase

**Objectif** : Placez la modulation là où votre aile a le plus de mordant.

**Méthode** : 
- Commencer à 50 ans
- Augmenter à 70 —, la réponse au roulis s'affaiblit-elle ?
- Diminuer à 30 —, la réponse au roulis devient-elle plus forte ?
- Le point "le plus fort" est l'endroit où la course de puissance de votre aile culmine

**Signes de trop haut** : réponse molle, l'engin semble "retardé"
**Signes de niveau trop bas** : réponse saccadée, dépassement au roulis

### 2. Ferocity D — Stabilisez l'engin

**Objectif** : Stabilisation primaire sans oscillation.

**Méthode** :
- Commencer à 20
- Vol stationnaire ou vers l'avant régulier
- Augmentez jusqu'à sentir l'engin "se raidir"
- Reculez de 5 points à partir de l'endroit où vous remarquez pour la première fois une oscillation

**Signes de niveau trop élevé** : vibrations fines, bourdonnement semblable à celui d'un moteur dans les servos
**Signes de niveau trop bas** : l'artisanat dérive, semble lâche

### 3. Ferocity P — Croustillance

**Objectif** : Réactif mais pas nerveux.

**Méthode** :
- Commencer à 15 heures
- Frappez le bâton de rouleau —, l'engin mord-il immédiatement ?
- Augmentez jusqu'à ce que la réponse du bâton soit nette
- Reculez si vous voyez un dépassement

**Signes de niveau trop élevé** : Sonnerie après l'entrée du stick, rebond
**Signes de niveau trop bas** : réponse pâteuse et retardée

### 4. Balance — Réglage de l'asymétrie

**Objectif** : autorité égale dans les deux sens.

**Méthode** :
- Voler droit et à niveau
- Roulez à gauche, notez la vitesse de réponse
- Roulez à droite, notez la vitesse de réponse
- Ajuster la balance pour les égaliser

### 5–7. Warp, Anchor, Resonance

Paramètres de réglage fin. Ajustez seulement après que 1 à 4 soient solides.

| Paramètres | Démarrer | Ajuster quand |
|-------|-------|-------------|
| Warp | 50 | La modulation semble trop étalée ou trop pointue |
| Anchor | 70 | Vous voulez plus/moins de PID brut mélangé |
| Resonance | 30 | Le vol stationnaire est instable ou le vol vers l'avant semble ringard |

### 8. Phase 2 — Avancé

| Paramètres | Effet |
|-------|--------|
| Prescience | Avance de synchronisation — plus élevée = la modulation mène la phase plus |
| Espelho | Couplage différentiel — rouleau plus serré, peut réduire l'efficacité |
| Saudade | Mémoire de course — plus fluide mais moins réactive |
| SSFF | Injection directe gyro→wave — commence à 10 |

---

*Le but est un engin qui vole comme s'il voulait être dans les airs. Si vous vous battez, reculez et réaccordez à partir de Cadence.*