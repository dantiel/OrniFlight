#Installation

Comment installer le firmware OrniFlight sur votre contrôleur de vol.

## Prérequis

- **Configurateur OrniFlight** (dernière version)
- Câble de données USB (non destiné uniquement à la charge)
- Supported flight controller board

## Cartes prises en charge

| Conseil | Cible | Flash | Remarques |
|-------|--------|-------|-------|
| OMNIBUSF4 | `OMNIBUSF4` | 16 Mo | STM32F405, MPU6000, OSD |
| TINYFISH | `TINYFISH` | 256 Ko | STM32F411, MPU6000 |

## Étapes clignotantes

### 1. Entrez en mode DFU/Bootloader

**OMNIBUSF4** : maintenez le bouton BOOT enfoncé tout en connectant USB. Le rouge LED reste solide —, vous êtes en mode DFU.

**TINYFISH** : maintenez le bouton BOOT enfoncé tout en connectant USB.

### 2. Flash via le configurateur

1. Ouvrez le configurateur OrniFlight
2. Accédez à l'onglet **Firmware Flasher**
3. Sélectionnez votre cible dans la liste déroulante
4. Choisissez la version du firmware (dernière version stable recommandée)
5. Cliquez sur **Charger le micrologiciel (en ligne)** ou sélectionnez un fichier hexadécimal local.
6. Cliquez sur **Flash Firmware**
7. Attendez "Programmation : RÉUSSIE"

### 3. Première connexion

Après avoir flashé :
1. Déconnectez et reconnectez le USB (sans le bouton BOOT)
2. Le configurateur doit se connecter automatiquement
3. Acceptez l'invite « Appliquer les paramètres par défaut personnalisés »
4. Vérifiez les informations de la carte dans l'onglet Configuration

## Dépannage

### Pas de port DFU

**macOS/Linux** : DFU devrait apparaître automatiquement. Sinon :
```bash
# Check for DFU device
system_profiler SPUSBDataType | grep -A 10 STM
```

**Windows** : installez [Zadig](https://zadig.akeo.ie/) pour remplacer le pilote STM32 DFU :
1. Exécutez Zadig
2. Options → Liste tous les appareils
3. Sélectionnez "STM32 BOOTLOADER"
4. Remplacez le pilote par "WinUSB"

### Échec du flash

- Essayez un autre câble USB (capable de données, pas de charge uniquement)
- Essayez un autre port USB (direct, pas hub)
- Maintenez le bouton BOOT tout au long du processus de flash
- **OMNIBUSF4** : Un effacement complet de la puce peut être nécessaire. — cochez l'option "Full Chip Erase"

### Le configurateur ne se connecte pas

- Vérifiez que le câble USB est compatible avec les données
- Vérifiez que la carte n'est pas en mode DFU (LED clignote = mode normal)
- Redémarrer le configurateur
- Essayez un autre port USB

## CLI Flash (avancé)

Pour les utilisateurs avancés, flashez via STM32CubeProgrammer ou st-flash :

```bash
st-flash write orniflight_0.4.6_OMNIBUSF4.hex 0x08000000
```

Après avoir flashé, vérifiez avec :

```bash
st-flash verify orniflight_0.4.6_OMNIBUSF4.hex 0x08000000
```