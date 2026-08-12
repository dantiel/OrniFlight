# Émetteur vidéo (VTX)

OrniFlight prend en charge le contrôle VTX pour les ornithoptères FPV. Les modules VTX peuvent être configurés via le configurateur OrniFlight, MSP ou CLI — en réglant la bande, le canal, le niveau de puissance et le mode fosse.

## Protocoles pris en charge

1. **IRC Tramp** — Commun sur les petits modules VTX, idéal pour les ornithoptères légers FPV
2. **TBS SmartAudio** — Protocole numérique avec prise en charge du mode fosse
3. **RTC6705** — Contrôle direct du SPI sur les cartes avec VTX intégré (par exemple SPRACINGF3NEO)

##Configuration

Les paramètres de VTX sont gérés via l'onglet **VTX** du configurateur OrniFlight, ou via CLI :

```
set vtx_band = 5           # Raceband
set vtx_channel = 1        # 5658 MHz
set vtx_power = 2          # 200mW
set vtx_low_power_disarm = ON  # Lower power when disarmed
set vtx_pit_mode_freq = 0  # Pit mode frequency (0 = disabled)
```

##Port série

Le contrôle VTX nécessite une broche UART TX dédiée. Configurez le port dans l'onglet **Ports** avec le périphérique `IRC Tramp` ou `TBS SmartAudio`.

## FPV Considérations sur les ornithoptères

- Le poids est critique — choisissez des modules VTX légers (Tramp Nano, Eachine Nano)
- Montage de l'antenne : assurer un dégagement par rapport aux ailes battantes
- Filtrage de puissance : connectez l'alimentation VTX après le filtre LC pour éviter le bruit des servos en vidéo
- Le mode Pit est recommandé pour les tests sur banc afin d'éviter la surchauffe des petits modules VTX