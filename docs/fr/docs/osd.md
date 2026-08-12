# Affichage à l'écran (OSD)

OrniFlight comprend un OSD (affichage à l'écran) intégré utilisant la puce MAX7456 ou AT7456E. Le OSD superpose les données de vol sur votre flux vidéo FPV.

## Éléments pris en charge

Configurez les éléments dans l'onglet **OSD** du configurateur OrniFlight. Faites glisser et déposez des éléments pour les positionner à l'écran.

### Données de vol

| Élément | Présentoirs |
|---------|----------|
| Tension de la batterie | Tension de la batterie principale (par exemple 14,8 V) |
| Tension moyenne des cellules | Tension par cellule (par exemple 3,7 V) |
| Tirage actuel | Ampères instantanés |
| mAh tiré | Capacité cumulée consommée |
| RSSI | Force du signal du récepteur |
| Mode vol | Mode actuel (INDEPENDENT, GLIDE, etc.) |
| Position du papillon | Pourcentage d'accélérateur actuel |
| Minuterie | Temps de vol / temps d'armement |
| Nom de l'artisanat | nom de l'artisanat OrniFlight |

### Spécifique aux ornithoptères

| Élément | Présentoirs |
|----------|----------|
| Fréquence de battement | Taux de course actuel de l'aile en Hz |
| Profil ONDAS | Numéro de profil de vol actif (1-3) |
| Phase Cadence | Décalage de phase de modulation de courant |
| Angle de servo | Position du servo d'aile |

## Gestion des polices

Le OSD utilise un système d'affichage basé sur des caractères. L'onglet **OSD** du configurateur OrniFlight comprend un **Gestionnaire de polices** pour télécharger des polices et des glyphes personnalisés.

## CLI Paramètres

```
set osd_units = METRIC
set osd_warn_bitmask = 270335  # Warning flag bitmask
set osd_tim1 = 2560            # Timer 1 source
set osd_tim2 = 2561            # Timer 2 source
```

## Matériel

Puce OSD actuellement prise en charge : **AT7456E** (trouvée sur les cartes OMNIBUSF4 et compatibles). MAX7456 est compatible et détecté automatiquement.