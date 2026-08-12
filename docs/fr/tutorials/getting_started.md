# Mise en route

Bienvenue sur OrniFlight ! Ce guide vous guide à travers la configuration initiale de votre contrôleur de vol ornithoptère.

## Ce dont vous avez besoin

- **Configurateur OrniFlight** Téléchargement — depuis [orniflight.org](https://orniflight.org)
- **câble USB** — pour connecter le contrôleur de vol à l'ordinateur
- **Ornithoptère** avec :
  - Contrôleur de vol pris en charge (OMNIBUSF4, TINYFISH)
  - Servos pour l'actionnement des ailes
  - Récepteur lié à votre émetteur
  - Battery (2S–4S LiPo)

## Démarrage rapide

### 1. Micrologiciel Flash

1. Ouvrez le **configurateur OrniFlight**.
2. Accédez à l'onglet **Firmware Flasher**
3. Sélectionnez votre cible de tableau (OMNIBUSF4 ou TINYFISH)
4. Choisissez la dernière version stable
5. Cliquez sur **Charger le micrologiciel**, puis sur **Flash Firmware**.

### 2. Configuration initiale

Après le clignotement, le configurateur vous demandera d'appliquer les paramètres par défaut personnalisés. **Toujours accepter.**

### 3. Configuration du récepteur

1. Allez dans l'onglet **Ports** → et définissez le bon UART sur `Serial RX`.
2. Allez dans l'onglet **Configuration** → sélectionnez votre protocole de récepteur (CRSF, SBUS, etc.)
3. Accédez à l'onglet **Récepteur** → et vérifiez que les mouvements du stick correspondent aux canaux attendus.
4. Définissez les points de terminaison du canal : 1000–2000 avec un centre de 1 500.

### 4. Configuration des servos

1. Accédez à l'onglet **Servos**
2. Vérifiez que le mappage des servos correspond à la configuration des ailes de votre ornithoptère.
3. Testez la direction du servo — en marche arrière si nécessaire
4. Réglez la position centrale (ailes horizontales = 1500)

### 5. Configuration des modes

1. Accédez à l'onglet **Modes**
2. Attribuez ARM à un commutateur AUX
3. Attribuez les modes de vol (ANGLE / ACRO / HORIZON) comme vous le souhaitez
4. Attribuez INDEPENDENT et GLIDE aux commutateurs de rechange
5. Configurez BEEPER pour la localisation des modèles perdus

### 6. Premier vol

1. **Déconnectez la tringlerie de l'aile pour les tests au banc**
2. Armez et vérifiez la direction du mouvement du servo.
3. Vérifiez la réponse de l'accélérateur
4. Pour le premier vol réel : utilisez le mode ANGLE, tarifs bas
5. Survolez au niveau des yeux, coupez si nécessaire

## Prochaines étapes

- [Configuration de base](basic_setup.html) Procédure pas à pas de configuration détaillée de —
- [ONDAS Tuning](../../tutorials/ondas_tuning.html) — tune dynamique de battement
- [PID Tuning](../../tutorials/tuning.html) — ajuste les caractéristiques de vol