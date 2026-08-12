# Visualització en pantalla (OSD)

OrniFlight inclou un OSD (visualització en pantalla) integrat que utilitza el xip MAX7456 o AT7456E. El OSD superposa les dades de vol al vostre canal de vídeo FPV.

## Elements compatibles

Configureu els elements a la pestanya **OSD** de OrniFlight Configurator. Arrossegueu i deixeu anar elements per col·locar-los a la pantalla.

### Dades de vol

| Element | Displays |
|---------|----------|
| Tensió de la bateria | Tensió de la bateria principal (per exemple, 14,8 V) |
| Tensió mitjana de la cèl·lula | Tensió per cèl·lula (p. ex. 3,7 V) |
| Sorteig actual | Amperatge instantani |
| mAh dibuixat | Capacitat acumulada consumida |
| RSSI | Intensitat del senyal del receptor |
| Mode de vol | Mode actual (INDEPENDENT, GLIDE, etc.) |
| Posició de l'accelerador | Percentatge actual de l'accelerador |
| Temporitzador | Temps de vol / temps armat |
| Nom de l'artesania | OrniFlight nom de l'artesania |

### Específic d'ornitòpters

| Element | Displays |
|-----------|-----------|
| Freqüència de bateig | Velocitat de carrera actual de l'ala en Hz |
| Perfil de ONDAS | Número de perfil de vol actiu (1-3) |
| Cadence Fase | Desplaçament de fase de modulació actual |
| Angle servo | Posició del servo ala |

## Gestió de fonts

El OSD utilitza un sistema de visualització basat en caràcters. La pestanya **OSD** del configurador OrniFlight inclou un **Gestor de fonts** per penjar tipus de lletra i glifs personalitzats.

## CLI Configuració

```
set osd_units = METRIC
set osd_warn_bitmask = 270335  # Warning flag bitmask
set osd_tim1 = 2560            # Timer 1 source
set osd_tim2 = 2561            # Timer 2 source
```

## Maquinari

Xip OSD actualment compatible: **AT7456E** (es troba a OMNIBUSF4 i plaques compatibles). MAX7456 és compatible i es detecta automàticament.