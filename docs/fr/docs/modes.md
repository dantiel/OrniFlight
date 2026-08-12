# Modes de vol

Les modes sont commutés via les commutateurs AUX de votre émetteur. Chaque mode peut être attribué à une plage de canaux AUX spécifique dans l'onglet **Modes** du configurateur OrniFlight.

## Modes standards

| Mode | Fonction |
|------|----------|
| **ARM** | Activer le contrôle de vol (moteurs/servos actifs) |
| **ANGLE** | L'engin — à niveau automatique revient au niveau lorsque les bâtons sont centrés |
| **HORIZON** | Mode angle hybride — près du centre, acro au stick complet |
| **ACRO** | Zzz2zzz par défaut pas de niveau automatique, contrôle pur du taux |
| **AIRMODE** | Maintient la boucle PID active à zéro gaz pour une autorité totale |

## Modes spécifiques à OrniFlight

| ID | Mode | Fonction |
|----|------|----------|
| 50 | **INDEPENDENT** | Contrôle indépendant des ailes — chaque aile répond à son propre canal servo |
| 51 | **GLIDE** | Mode plané Ailes — verrouillées en position horizontale pour le vol à voile |
| 52 | **PROFILE** | Sélection du profil de vol — basculer entre 3 profils PID/ONDAS |

## Modes utilitaires

| Mode | Fonction |
|------|----------|
| **BEEPER** | Activer le buzzer pour localiser les avions perdus |
| **BLACKBOX** | Démarrer/arrêter la journalisation Blackbox |
| **FAILSAFE** | Déclencher manuellement le niveau de sécurité 2 (interrupteur anti-panique) |
| **OSD** | Basculer l'affichage de OSD |
| **TELEMETRY** | Activer/désactiver la sortie de télémétrie |

## Notes sur les ornithoptères

- Le mode **INDEPENDENT** est unique au OrniFlight —, il permet le mappage des servos par aile pour la poussée asymétrique et le contrôle différentiel des ailes.
- Le mode **GLIDE** maintient les ailes en position neutre, utile pour le vol thermique et la descente économe en énergie
- La commutation **PROFILE** permet de modifier les paramètres ONDAS en vol pour différentes conditions de vol (par exemple, croisière ou manœuvres agressives)