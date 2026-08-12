# LED Bande

OrniFlight prend en charge les bandes adressables WS2812/SK6812 LED pour l'indication d'état et le retour visuel.

##Configuration

Les bandes LED sont configurées dans l'onglet **LED Strip** du configurateur OrniFlight. Chaque position, couleur et fonction du LED peut être réglée individuellement.

## Fonctions

| Fonction | Effet visuel |
|--------------|--------------|
| Indicateur de batterie | Dégradé de couleur du vert → jaune → rouge |
| RSSI | Affichage de la force du signal |
| État des bras | Changement de couleur lors de l'activation/désactivation |
| Mode vol | Couleurs spécifiques au mode |
| Avertissement | Modèles de clignotement pour batterie faible, sécurité intégrée |
| Indicateur de battement | Impulsion à la fréquence de battement actuelle |
| Direction de poussée | Changement de couleur indiquant la sortie roulis/tangage/lacet |
| GPS | Verrouillage satellite et direction du domicile |

## Matériel

- LED WS2812 ou SK6812 RGB
- Connectez-vous au pad/pin **LED** de votre contrôleur de vol
- Alimentez les LED d'un BEC (ne pas alimenter à partir de 3,3 V —, utilisez 5 V)
- Pour les longues bandes (> 8 LED), connectez l'alimentation 5 V directement aux batteries, pas via FC

## Utilisation des ornithoptères

L'**indicateur de battement** est unique aux LED OrniFlight — qui pulsent en synchronisation avec la fréquence des coups d'aile, donnant une représentation visuelle du rythme de battement et aidant à régler les paramètres de cadence ONDAS.