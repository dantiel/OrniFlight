# Récepteur (RX)

OrniFlight prend en charge plusieurs protocoles de réception pour le contrôle radio de votre ornithoptère.

## Protocoles pris en charge

| Protocole | Tapez | Remarques |
|--------------|------|-------|
| **CRSF** (Feux croisés) | Série | Faible latence, télémétrie, recommandé |
| **SBUS** | Série | Inversé, nécessite un inverseur sur F4 |
| **IBUS** (FlySky) | Série | Non inversé, direct UART |
| **PPM** | Analogique monofilaire | 8 canaux, héritage, non recommandé |
| **SPEKTRUM** | Série | 1024/2048, liaison via CLI |
| **FPORT** | Série | FrSky, combine RX+Télémétrie |
| **GHST** (Fantôme) | Série | ImmersionRC, faible latence |

## Configuration série RX

1. Connectez le récepteur à une broche UART RX gratuite
2. Dans le configurateur → **Ports** : définissez le UART sur `Serial RX`
3. Dans le Configurateur → **Configuration** : sélectionnez le protocole
4. Pour SBUS sur F4 : activez `set sbus_inversion = ON`

## CLI Configuration rapide

```
feature RX_SERIAL
set serialrx_provider = CRSF
set serialrx_inverted = OFF
set serialrx_halfduplex = OFF
save
```

## Sécurité intégrée

Configurez la sécurité intégrée du récepteur afin que le récepteur n'émet **aucune impulsion** en cas de perte de signal. Le contrôleur de vol le détectera alors et activera sa propre procédure de sécurité. Voir [Failsafe](failsafe.html) pour la configuration au niveau FC.