#RSSI

RSSI (indicateur de force du signal reçu) indique la qualité de votre liaison radio. OrniFlight peut obtenir RSSI à partir d'une entrée analogique, de données de récepteur série ou du protocole RSSI.

## RSSI Sources

| Source | Connexion | Configuration |
|--------|-----------|---------------|
| **Protocole série** | Aucun (sur le fil série RX) | CRSF, GHST — automatique |
| **Chaîne AUX** | Aucun (TX envoie RSSI comme canal) | `set rssi_channel = 8` |
| **Analogique ADC** | Pad RSSI activé FC → Récepteur RSSI sorti | `set rssi_adc_channel = 1` |

##Configuration

### Série RSSI (CRSF/GHST/SBUS)

```
set rssi_src_frame_errors = OFF
set rssi_scale = 100
set rssi_offset = 0
```

RSSI est transmis automatiquement par les protocoles série —, aucun câblage supplémentaire n'est nécessaire.

### Analogique RSSI

Connectez le récepteur RSSI sortie → RSSI pad sur le contrôleur de vol :

```
set rssi_adc_channel = 1      # Use ADC channel 1
set rssi_scale = 100          # Scale to 0-100%
set rssi_offset = 0
```

### AUX Chaîne RSSI

Configurez votre émetteur pour envoyer RSSI sur un canal spécifique, puis :

```
set rssi_channel = 12         # Aux channel number
set rssi_scale = 100
set rssi_offset = 0
```

## Affichage

RSSI est affiché dans le OSD et peut être transmis par télémétrie à votre radio. Configurez les seuils d'avertissement :

```
set osd_rssi_alarm = 20        # Warning at 20% RSSI
```

## Portée des ornithoptères

Pour les ornithoptères, RSSI est essentiel. Les ailes battantes de — créent des modèles d'interférence dynamiques de RF. Surveillez RSSI pendant les vols d'essai initiaux pour vérifier les performances fiables de la liaison à toutes les positions de l'aile.