# Portas seriais

OrniFlight usa portas seriais para comunicação com periféricos: receptores, GPS, telemetria, controle VTX, registro Blackbox e MSP (conexão do configurador).

## Tipos de porta serial

| Tipo | Descrição | Melhor para |
|------|------------|----------|
| **VCP** | USB Virtual COM Porta — conexão USB direta ao processador | Configurador (MSP) |
| **UART** | Pinos TX/RX de hardware com detecção de sinal de hardware | RX, GPS, Telemetria, VTX, Caixa Preta |
| **SoftSerial** | Série controlada por software em qualquer par de pinos | Largura de banda baixa: apenas telemetria |

VCP não consome um UART — está sempre disponível para o Configurador.

## Atribuição de porta

No OrniFlight Configurator, vá para a aba **Portas** para atribuir funções:

| Função | Zzz31zzz típico | Notas |
|----------|-------------|-------|
| Série RX | UART1 ou UART3 | SBUS, CRSF, IBUS, etc. |
| GPS | UART3 ou UART6 | 57600 ou 115200 bauds |
| Telemetria | Qualquer alfinete TX | SmartPort, HoTT, IBUS |
| VTX (vagabundo/SmartAudio) | Qualquer pino TX | Fio único |
| Caixa preta | Qualquer alfinete TX | OpenLog ou flash integrado |
| MSP | VCP (USB) | Conexão do configurador |

## OMNIBUSF4 Mapeamento de portas

| UART | Pinos | Uso típico |
|------|------|------------|
| VCP | USB | MSP (Configurador) |
| UART1 | TX1/RX1 | Série RX |
| UART3 | TX3/RX3 | GPS ou Telemetria |
| UART6 | TX6/RX6 | Grátis / Caixa preta / VTX |

## SoftSerial

SoftSerial está disponível, mas tem largura de banda limitada. Adequado apenas para telemetria de baixa taxa (por exemplo, 9600 baud SmartPort). Não recomendado para serial RX ou GPS.