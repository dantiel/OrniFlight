# Télémétrie

La télémétrie envoie les données de vol de OrniFlight à votre émetteur radio —, tension de la batterie, courant, RSSI, coordonnées GPS, altitude, etc.

## Protocoles pris en charge

| Protocole | Système radio | Nombre de fils |
|--------------|-------------|------------|
| **CRSF** | Feux croisés / Traceur / ELRS | Intégré avec RX (bidirectionnel) |
| **SmartPort** | FrSky | 1 fil (broche TX) |
| **HoTT** | Graupner | 1 fil (TX+TZ) |
| **IBUS** | FlySky | 1 fil (capteur TX) |
| **LTM** | Télémétrie lumineuse (MWP) | 1 fil (TX) |

##Configuration

1. Dans le configurateur → **Ports** : définissez la broche UART TX sur le protocole de télémétrie approprié.
2. Activer la fonction de télémétrie : `feature TELEMETRY`
3. Configurez l'inversion de télémétrie si nécessaire

Pour **CRSF**, la télémétrie est gérée automatiquement —, aucun port séparé n'est nécessaire.

## SmartPort (FrSky)

SmartPort nécessite une inversion de signal sur les processeurs F4. Soit :
- Utiliser un contrôleur de vol avec inverseur intégré
- Utilisez SoftSerial avec `set tlm_inversion = ON`

```
feature TELEMETRY
set tlm_inverted = ON
set tlm_halfduplex = ON
```

## Données de télémétrie

OrniFlight transmet :
- tension VBAT (batterie principale)
- Consommation de courant / mAh consommé
- RSSI (force du signal)
- Mode vol/état du bras
- coordonnées GPS (si équipé)
- Altitude / vario (si baromètre)
- Profil de vol ONDAS actif