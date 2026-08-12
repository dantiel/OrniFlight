# Ports série

OrniFlight utilise des ports série pour la communication avec les périphériques : récepteurs, GPS, télémétrie, contrôle VTX, journalisation Blackbox et MSP (connexion du configurateur).

## Types de ports série

| Tapez | Descriptif | Idéal pour |
|------|------------|--------------|
| **VCP** | USB Port COM virtuel — Connexion directe USB au processeur | Configurateur (MSP) |
| **UART** | Broches matérielles TX/RX avec détection de signal matériel | RX, GPS, Télémétrie, VTX, Blackbox |
| **SoftSerial** | Série pilotée par logiciel sur n'importe quelle paire de broches | Faible bande passante : télémétrie uniquement |

VCP ne consomme pas de UART — physique, il est toujours disponible pour le Configurateur.

## Attribution des ports

Dans le configurateur OrniFlight, accédez à l'onglet **Ports** pour attribuer des fonctions :

| Fonction | Typique UART | Remarques |
|--------------|-------------|-------|
| Série RX | UART1 ou UART3 | SBUS, CRSF, IBUS, etc.
| GPS | UART3 ou UART6 | 57 600 ou 115 200 bauds |
| Télémétrie | N’importe quelle broche TX | SmartPort, HoTT, IBUS |
| VTX (Tramp/SmartAudio) | N’importe quelle broche TX | Monofilaire |
| Boîte noire | N’importe quelle broche TX | OpenLog ou flash intégré |
| MSP | VCP (USB) | Connexion du configurateur |

## OMNIBUSF4 Mappage des ports

| UART | Épingles | Utilisation typique |
|------|------|------------|
| VCP | USB | MSP (Configurateur) |
| UART1 | TX1/RX1 | Série RX |
| UART3 | TX3/RX3 | GPS ou Télémétrie |
| UART6 | TX6/RX6 | Gratuit / Boîte noire / VTX |

## SoftSerial

SoftSerial est disponible mais sa bande passante est limitée. Convient uniquement pour la télémétrie à faible débit (par exemple 9 600 bauds SmartPort). Non recommandé pour les séries RX ou GPS.