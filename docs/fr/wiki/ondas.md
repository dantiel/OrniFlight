# ONDAS — Stabilisation adaptative dynamique normalisée oscillante

## Le principe fondamental

Un avion à voilure fixe ou conventionnel génère des forces de contrôle **en continu** — une déviation de la gouverne ou un changement de RPM produit un moment stable. Ce n’est pas le cas d’un ornithoptère. Chaque gramme de poussée, chaque Newton de couple est **lié à une phase** dans le cycle de battement d'aile. La même impulsion de force appliquée à différents points du coup produit des résultats fondamentalement différents.

ONDAS reconnaît cette réalité et module l'effort de stabilisation de manière synchrone avec le cycle de battement.

---

## Cadence — Le cerveau du timing

Cadence est le filtre ONDAS le plus critique car il détermine **quand** la correction se produit dans chaque battement d'aile.

| Phase d'AVC | Effet de l'application de la force |
|---|---|
| Centre de course descendante | Levage maximum, autorité de roulis |
| Fin de course descendante (freinage) | Traînée induite → moment de lacet |
| Centre de montée | Poussée vers l'arrière, cabrage |
| Fin de course | Inversion des ailes, effet minimal |

**Cadence décale la fenêtre de modulation** pour l'aligner sur la phase où le bras de levier aérodynamique est le plus long. Mauvaise cadence = physique des ailes de combat. Cadence correcte = chaque milliwatt devient autorité de contrôle.

### Paramètres

| Paramètre | Valeur | Fonction |
|---------------|-------|--------------|
| `ONDAS_K0` | 1.0 | Décalage de phase de base |
| `ONDAS_K2` | 10,0 | Étalement de phase / netteté |
| `ONDAS_PHASE_SCALE` | 0,00005 | Petit facteur, grand effet de levier |

---

## Ferocity P — Poussée asymétrique immédiate

Ferocity P augmente la **carrérité de la forme d'onde** (forme trapézoïdale : maintien à ±1, rampe cosinusoïdale entre) proportionnellement à l'erreur PID actuelle.

- Plus de poussée d'un côté → instant immédiat
- L'aile freinée en fin de course subit une **traînée induite** — c'est le contre-moment
- Effet : direct, proportionnel, immédiat

---

## Ferocity D — Exploitation anticipée du drag

Ferocity D complète le tableau. Là où P fournit une asymétrie de poussée, D exploite la **traînée de l'aile controlatérale** comme frein.

- Lit le taux d'erreur de changement et **anticipe**
- Peut délibérément exploiter la traînée d'une aile ralentie pour les moments de lacet/tangage
- P+D créent ensemble une **paire de moments différentiels** — poussée sur le côté A, traînée sur le côté B — plus efficace que la poussée seule

---

## Trois façons Cadence/Ferocity D augmente Ferocity

### 1. Direct — D augmente P lors d'un changement d'erreur rapide

Dans les rafales ou les manœuvres agressives, `error_rate` est grand. D multiplie cela et ajoute à la férocité de base. L'aile devient *plus nette* (plus trapézoïdale) car P+D ensemble exigent plus de squareness que P seul. Résultat : une autorité maximale précisément lorsque cela est critique.

### 2. Indirect — Cadence déplace le point de levier

Cadence module *quand* dans le cycle la férocité agit. Déplacer la fenêtre dans une phase plus sensible sur le plan aérodynamique (par exemple, centre de course descendante par rapport à fin de course ascendante) signifie que la **même valeur de férocité** produit plus d'effet —, une amplification efficace sans changement numérique.

### 3. Combinatoire — D × Cadence pendant la sortie de décrochage

Dans un décrochage : taux de chute élevé → D détecte le taux → augmente la férocité. Simultanément, la cadence déplace la modulation vers la phase descendante où l'aile a un mordant maximum. L'interaction : D fournit la force, la cadence le bon moment. Sans cadence, la force D arrive à la mauvaise phase et se dissipe inutilement.

---

## Paramètres ONDAS supplémentaires

| Paramètre | Fonction |
|-----------|----------|
| **Balance** | Symétrie de poussée haut/bas — Biais en terme I entre la course ascendante et la course descendante. Compense l'asymétrie des ailes, les tolérances de fabrication et l'usure |
| **Warp** | Roll/Yaw P → Différentiel de férocité L/R — les ailes droite et gauche battent indépendamment sur l'axe de roulis pour les manœuvres d'inclinaison et de virage |
| **Anchor** | L'ancrage de phase — verrouille la modulation sur une référence de phase spécifique, résistant à la dérive |
| **Resonance** | La compensation de résonance de la cellule — évite les modes structurels passionnants de la cellule |

---

## Analogie

**Cadence est le chef d'orchestre. Ferocity P et D sont les instruments.**

Sans chef d'orchestre, ils jouent — mais pas ensemble. Avec un seul, le bruit devient musique.

---

## Voir aussi

- [Guide de réglage ONDAS](../../tutorials/ondas_tuning.html) Procédure de réglage pratique —
- [Protocole MSP](msp.html) Format de fil — pour les paramètres ONDAS
- [Profils de vol](profiles.html) configuration — prenant en compte le profil ONDAS