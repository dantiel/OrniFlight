# Transmisor de vídeo (VTX)

OrniFlight admite el control VTX para ornitópteros FPV. Los módulos VTX se pueden configurar a través del configurador OrniFlight, MSP o CLI — configurando banda, canal, nivel de potencia y modo pit.

## Protocolos admitidos

1. **IRC Tramp** — Común en módulos pequeños VTX, ideal para ornitópteros ligeros FPV
2. **TBS SmartAudio** — Protocolo digital compatible con modo pit
3. **RTC6705** — Control directo SPI en placas con VTX integrado (p. ej. SPRACINGF3NEO)

## Configuración

La configuración de VTX se administra a través de la pestaña **VTX** en el Configurador de OrniFlight, o mediante CLI:

```
set vtx_band = 5           # Raceband
set vtx_channel = 1        # 5658 MHz
set vtx_power = 2          # 200mW
set vtx_low_power_disarm = ON  # Lower power when disarmed
set vtx_pit_mode_freq = 0  # Pit mode frequency (0 = disabled)
```z

## Puerto serie

El control VTX requiere un pin UART TX dedicado. Configure el puerto en la pestaña **Puertos** con el periférico `IRC Tramp` o `TBS SmartAudio`.

## FPV Consideraciones sobre el ornitóptero

- El peso es crítico — elija módulos livianos VTX (Tramp Nano, Eachine Nano)
- Montaje de la antena: asegúrese de que haya espacio libre para las alas batientes.
- Filtrado de potencia: conecte la alimentación del VTX después del filtro LC para evitar el ruido del servo en el vídeo.
- Se recomienda el modo Pit para pruebas en banco para evitar el sobrecalentamiento de módulos pequeños VTX