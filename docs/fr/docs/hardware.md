# Matériel pris en charge

OrniFlight fonctionne sur les contrôleurs de vol STM32F3/F4/F7. La ligne de base est **STM32F3** —, toute cible F3 dotée de broches de minuterie compatibles avec les servos volera.

## Contrôleurs de vol

| Conseil | MCU | IMU | Flash | Récepteur | Statut |
|-------|-----|-----|-------|--------------|--------|
| **TINYFISH** | STM32F303 | MPU6000 (SPI) | 256 KB | FrSky D8 (intégré) | ✅ Primaire |
| **OMNIBUSF4** | STM32F405 | MPU6000 (SPI) | 1 MB + 16 MB SPI | — | ✅ Pris en charge |

### TINYFISH — La cible OrniFlight la plus légère

Conçu par fishpepper, le TINYFISH est le contrôleur de vol idéal pour un ornithoptère : poids plume, basé sur le F3 et transportant un **récepteur FrSky D8** intégré à bord. Pas de RX externe, pas de câblage supplémentaire —, juste de l'alimentation, des servos et du vol.

- **MCU** : STM32F303CCT6 à 72 MHz
- **Gyro** : MPU6000 (SPI, compatible 8 kHz)
- **Flash** : 256 KB sur la puce
- **RAM** : 40 KB
- **Récepteur** : FrSky D8 intégré (SBUS acheminé en interne vers UART2)
- **UART** : VCP + 2 UART matériels (UART1 gratuit pour le module complémentaire GPS/CRSF)
- **Entrée** : 2-4S LiPo (alimentation servo directe)
- **Poids** : ~2,5 g

TINYFISH prouve que le contrôle transcendant des battements n'a pas besoin d'un F7. Le STM32F303 exécute le pipeline ONDAS complet — 10 canaux de modulation, aile trapézoïdale ODE, 4 profils de vol — dans 256 KB.

### OMNIBUSF4 — Le bourreau de travail accessible

La cible F4 classique. Bon marché, omniprésent, complet avec OSD et un grand flash SPI pour la journalisation Blackbox. La référence pour le développement et les constructions plus importantes.

- **MCU** : STM32F405RGT6 à 168 MHz
- **Gyro** : MPU6000 (SPI, compatible 8 kHz)
- **Flash** : 1 MB sur puce + 16 MB SPI (Blackbox)
- **RAM** : 192 KB
- **OSD** : AT7456E (compatible avec MAX7456)
- **UART** : VCP + 5 UART matériels
- **Baromètre** : BMP280 (certaines variantes)
- **Entrée** : 2-6S LiPo

---

## Anatomie des ornithoptères

### Servomoteurs d'aile

Les commandes OrniFlight battent via les servos PWM. Spécifications clés :

| Paramètre | Gamme typique |
|-----------|--------------|
| Largeur d'impulsion | 500–2500 µs |
| Centre | 1500 µ |
| Fréquence | 50–330 Hz |
| Angle de course | ±15–45° |

Pour les ornithoptères hautes performances, des servos numériques avec un taux de mise à jour de 330 Hz sont recommandés. Les servos analogiques fonctionnent à 50 Hz mais ont une précision moindre.

### Récepteur

Tout protocole de récepteur série est pris en charge. CRSF (TBS Crossfire / ExpressLRS) est recommandé pour :
- Faible latence (critique pour le contrôle du battement)
- Télémétrie intégrée
- RSSI sur protocole (pas de câblage supplémentaire)

### Batterie

- **2S (7,4 V)** : Petits ornithoptères, directement servo-alimentés
- **3S (11,1 V)** : Ornithoptères moyens, BEC requis pour les servos
- **4S (14,8 V)** : Grands ornithoptères, BEC externe recommandé

---

## Périphériques pris en charge

| Périphérique | Par | Remarques |
|-----------|-----|-------|
| GPS | UART | UBlox M8N ou compatible |
| VTX | UART TX | Clochard, SmartAudio |
| Appareil photo | — | Toute caméra analogique FPV |
| Buzzer | tampon BUZZ | Buzzer actif 5V |
| LED Bande | bloc LED | WS2812 / SK6812 |
| OpenLog | UART TX | Journalisation de la boîte noire |
| Bluetooth | UART | Passthrough MSP pour le réglage mobile |

---

## Cibles futures

OrniFlight vise à prendre en charge des cibles STM32F4/F7 supplémentaires où suffisamment de ressources UART et de minuterie sont disponibles pour le contrôle d'asservissement du battement. Les contributions sont les bienvenues.