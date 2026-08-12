#RSSI

RSSI (indicador de força del senyal rebut) mostra la qualitat del vostre enllaç de ràdio. OrniFlight pot obtenir RSSI des de l'entrada analògica, les dades del receptor en sèrie o el protocol RSSI.

## RSSI Fonts

| Font | Connexió | Configuració |
|--------|-----------|----------------|
| **Protocol sèrie** | Cap (a través del cable de sèrie RX) | CRSF, GHST — automàtic |
| **Canal AUX** | Cap (TX envia RSSI com a canal) | `set rssi_channel = 8` |
| **Zzz25zzz analògic** | RSSI coixinet activat FC → Receptor RSSI fora | `set rssi_adc_channel = 1` |

## Configuració

### Sèrie RSSI (CRSF/GHST/SBUS)

```
set rssi_src_frame_errors = OFF
set rssi_scale = 100
set rssi_offset = 0
```

RSSI es transmet automàticament mitjançant protocols sèrie —, no cal cablejat addicional.

### Zzz32zzz analògic

Connecteu el receptor RSSI sortida → RSSI coixinet al controlador de vol:

```
set rssi_adc_channel = 1      # Use ADC channel 1
set rssi_scale = 100          # Scale to 0-100%
set rssi_offset = 0
```

### AUX Canal RSSI

Configureu el vostre transmissor per enviar RSSI a un canal específic i, a continuació:

```
set rssi_channel = 12         # Aux channel number
set rssi_scale = 100
set rssi_offset = 0
```

## Mostra

RSSI es mostra a OSD i es pot transmetre mitjançant telemetria a la vostra ràdio. Configura els llindars d'avís:

```
set osd_rssi_alarm = 20        # Warning at 20% RSSI
```

## Gamma d'ornitòpters

Per als ornitòpters, RSSI és crític. Les ales — que aletegen creen patrons d'interferència RF dinàmics. Superviseu RSSI durant els vols de prova inicials per verificar el rendiment de l'enllaç fiable a totes les posicions de les ales.