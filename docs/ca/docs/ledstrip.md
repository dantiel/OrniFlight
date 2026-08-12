# LED Strip

OrniFlight admet tires WS2812/SK6812 LED adreçables per a la indicació d'estat i comentaris visuals.

## Configuració

Les tires LED es configuren a la pestanya **LED Strip** del Configurador OrniFlight. Cada posició, color i funció LED es poden configurar individualment.

## Funcions

| Funció | Efecte visual |
|----------|--------------|
| Indicador de bateria | Gradient de color del verd → groc → vermell |
| RSSI | Visualització de la força del senyal |
| Estat del braç | Canvi de color en armar/desarmar |
| Mode de vol | Colors específics del mode |
| Avís | Patrons de parpelleig per a bateria baixa, seguretat |
| Indicador de bateig | Pols a la freqüència de flapping actual |
| Direcció d'empenta | Canvi de color que indica la sortida de gir/encaix/guiada |
| GPS | Bloqueig de satèl·lit i direcció a casa |

## Maquinari

- LEDs WS2812 o SK6812 RGB
- Connecteu-vos al coixinet/pin **LED** del vostre controlador de vol
- LED d'alimentació des d'un BEC (NO s'alimenta des de 3,3 V — utilitza 5 V)
- Per a tires llargues (> 8 LED), connecteu l'alimentació de 5 V directament als coixinets de la bateria, no a través de FC

## Ús d'ornitòpters

L'**Indicador de bateig** és exclusiu per als LED OrniFlight — pols sincronitzat amb la freqüència de batuda de l'ala, donant una representació visual del ritme de bateig i ajudant a ajustar els paràmetres de cadència ONDAS.