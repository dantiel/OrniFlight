# Profils de vol

> *4 emplacements de réglage indépendants, commutables en vol.*

##Concept

OrniFlight stocke 4 structures `ornithopterProfile_t` complètes — contenant chacune les 19 ONDAS et les paramètres de dynamique des ailes. Un mode BOX (`BOXORNITHOPTERPROFILE`, permanentId 52) sélectionne le profil actif via un commutateur RC à 2 positions mappé sur 4 emplacements (0–3).

## Pourquoi les profils ?

Différents régimes de vol nécessitent des réglages différents :

| Profil | Cas d'utilisation | Cadence | Ferocity | Remarques |
|---------|----------|---------|----------|-------|
| 0 | **Croisière** | Milieu (50) | Faible (30) | Vol avant efficace |
| 1 | **Acrobatie** | Faible (20) | Élevé (80) | Autorité maximale |
| 2 | **Survol/Loiter** | Élevé (70) | Milieu (50) | Stabilité par rapport à la vitesse |
| 3 | **Glisser** | Milieu (50) | Faible (10) | Intervention minimale |

## Que contient un profil

Les 19 champs de `ornithopterProfile_t` :

- **Géométrie de glisse** : glide_angle
- **ONDAS v2 (10)** : cadence, ferocity_d/p/roll/yaw, équilibre, warp, warp_yaw, ancre, résonance
- **Phase 2 (4)** : prescience, espelho, saudade, ssff
- **Forme de vague (2)** : ferocity_downStroke, ferocity_upStroke
- **Aéroélastique (2)** : aeroelastic_glide_coefficient, aeroelastic_flap_coefficient

## Qu'est-ce qui est global (pas par profil)

- Canal de fréquence (un canal RC, fonctionne à la fois en INDEPENDENT et GLIDE)
- Angles de montage des servos
- Déphasages battants
- géométrie GralhaAzul (servo_speed, max_amplitude, flap_magnitude, wing_origin)

Ce sont des constantes physiques de la cellule —, elles ne changent pas avec le régime de vol.

## Changement de vol

1. Attribuez un interrupteur 2 ou 3 positions à un canal de réserve
2. Dans l'onglet Modes du configurateur, mappez cette plage à `ORNITHOPTER PROFILE`
3. Chaque position du commutateur sélectionne l'un des 4 emplacements
4. La liste déroulante du profil du configurateur modifie l'emplacement *actuellement sélectionné* via MSP

---

*Voir `src/main/flight/ornithopter_profile.h` pour la définition de la structure.*