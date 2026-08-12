# Transmisor de vídeo (VTX)

OrniFlight admite o control VTX para ornitópteros FPV. Os módulos VTX pódense configurar mediante o Configurador OrniFlight, MSP ou CLI — axustando a banda, a canle, o nivel de potencia e o modo pit.

## Protocolos admitidos

1. **IRC Tramp** — Común en módulos VTX pequenos, ideal para ornitópteros FPV lixeiros
2. **TBS SmartAudio** — Protocolo dixital con compatibilidade co modo pit
3. **RTC6705** — Control directo SPI en placas con VTX integrado (por exemplo, SPRACINGF3NEO)

## Configuración

A configuración de VTX xestionase a través da pestana **VTX** en OrniFlight Configurator ou a través de CLI:

zz0zzz

## Porto de serie

O control VTX require un pin UART TX dedicado. Configure o porto na pestana **Portos** co periférico `IRC Tramp` ou `TBS SmartAudio`.

## FPV Consideracións sobre os ornitópteros

- O peso é fundamental — elixe módulos lixeiros VTX (Tramp Nano, Eachine Nano)
- Montaxe da antena: garantir a distancia das ás que batan
- Filtrado de potencia: conecta a alimentación VTX despois do filtro LC para evitar o ruído do servo no vídeo
- Recoméndase o modo Pit para probas en banco para evitar quentar os módulos pequenos VTX