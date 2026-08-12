# Transmissor de vídeo (VTX)

OrniFlight admet el control VTX per als ornitòpters FPV. Els mòduls VTX es poden configurar mitjançant el configurador OrniFlight, MSP o CLI —, la banda de configuració, el canal, el nivell de potència i el mode de fossa.

## Protocols compatibles

1. **IRC Tramp** — Comú en mòduls VTX petits, ideal per a ornitòpters FPV lleugers
2. **TBS SmartAudio** — Protocol digital amb compatibilitat amb el mode pit
3. **RTC6705** — Control directe SPI a les plaques amb VTX integrat (p. ex., SPRACINGF3NEO)

## Configuració

La configuració de VTX es gestiona mitjançant la pestanya **VTX** a OrniFlight Configurator o mitjançant CLI:

```
set vtx_band = 5           # Raceband
set vtx_channel = 1        # 5658 MHz
set vtx_power = 2          # 200mW
set vtx_low_power_disarm = ON  # Lower power when disarmed
set vtx_pit_mode_freq = 0  # Pit mode frequency (0 = disabled)
```

## Port sèrie

El control VTX requereix un pin UART TX dedicat. Configura el port a la pestanya **Ports** amb el perifèric `IRC Tramp` o `TBS SmartAudio`.

## FPV Consideracions sobre l'ornitòpter

- El pes és crític — tria mòduls lleugers VTX (Tramp Nano, Eachine Nano)
- Muntatge de l'antena: assegureu-vos d'estar lliure de les ales
- Filtret de potència: connecteu l'alimentació VTX després del filtre LC per evitar el soroll del servo al vídeo
- Es recomana el mode Pit per a proves de banc per evitar el sobreescalfament dels mòduls VTX petits