# Transmissor de vídeo (VTX)

OrniFlight suporta controle VTX para ornitópteros FPV. Os módulos VTX podem ser configurados por meio do configurador OrniFlight, MSP ou CLI — configuração de banda, canal, nível de potência e modo pit.

## Protocolos Suportados

1. **IRC Tramp** — Comum em pequenos módulos VTX, ideal para ornitópteros FPV leves
2. **TBS SmartAudio** — Protocolo digital com suporte ao modo pit
3. **RTC6705** — Controle direto SPI em placas com VTX integrado (por exemplo, SPRACINGF3NEO)

## Configuração

As configurações do VTX são gerenciadas através da guia **VTX** no configurador OrniFlight ou via CLI:

```
set vtx_band = 5           # Raceband
set vtx_channel = 1        # 5658 MHz
set vtx_power = 2          # 200mW
set vtx_low_power_disarm = ON  # Lower power when disarmed
set vtx_pit_mode_freq = 0  # Pit mode frequency (0 = disabled)
```

## Porta serial

O controle VTX requer um pino UART TX dedicado. Configure a porta na aba **Portas** com o periférico `IRC Tramp` ou `TBS SmartAudio`.

## FPV Considerações sobre ornitópteros

- O peso é crítico — escolha módulos VTX leves (Tramp Nano, Eachine Nano)
- Montagem da antena: garanta a folga das asas batendo
- Filtragem de energia: conecte a alimentação VTX após o filtro LC para evitar ruído servo no vídeo
- O modo Pit é recomendado para testes de bancada para evitar o superaquecimento de pequenos módulos VTX