# Premier éclair

> *Installer OrniFlight sur votre contrôleur de vol — étape par étape.*

## Ce dont vous avez besoin

- Contrôleur de vol basé sur STM32F4 (OMNIBUSF4, TINYFISH, MATEKF405, etc.)
- câble USB
- [dfu-util](http://dfu-util.sourceforge.net/) ou STM32CubeProgrammer
- Fichier OrniFlight `.hex` de la [page des versions](https://github.com/dantiel/OrniFlight/releases)

## Étape 1 : Entrez dans le mode DFU

1. **Maintenez enfoncé le bouton BOOT** de votre contrôleur de vol
2. **Branchez USB** tout en maintenant le bouton enfoncé
3. **Relâchez** après 2 secondes

Vérifiez sur macOS/Linux :

```
dfu-util -l
```

Devrait afficher `Found DFU: [0483:df11]`

## Étape 2 : Flash

```
dfu-util -a 0 -D obj/orniflight_0.4.6_OMNIBUSF4.hex
```

## Étape 3 : Premier démarrage

1. Débranchez USB
2. Rebranchez USB (ne tenez pas BOOT)
3. Connectez-vous via le configurateur OrniFlight

## Étape 4 : Configuration de base

Dans le Configurateur :

1. **Onglet Ports** : configurez UART pour votre récepteur (série RX)
2. **Onglet Configuration** : Sélectionnez le protocole du récepteur (CRSF recommandé)
3. **Onglet Modes** : configurez les commutateurs ARM, GLIDE/INDEPENDENT et PROFILE
4. **Onglet → ONDAS avancé** : vérifiez les paramètres par défaut, réglez d'abord Cadence

## Dépannage

| Problème | Corriger |
|---------|-----|
| Appareil DFU introuvable | Essayez un autre câble USB, vérifiez le bouton BOOT |
| Flash échoue | Vérifiez l'installation de dfu-util, les autorisations USB |
| Pas de démarrage après flash | Re-flashez, vérifiez que l'hexagone correspond à votre cible |
| Le configurateur ne se connecte pas | Vérifiez le port COM et le débit en bauds |

---

*Suivant : [Configuration de base](basic_setup.html) →*