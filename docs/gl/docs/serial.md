# Portos serie

OrniFlight uses serial ports for communication with peripherals: receivers, GPS, telemetry, VTX control, Blackbox logging, and MSP (Configurator connection).

## Tipos de portos serie

| Tipo | Descrición | Mellor para |
|------|-------------|-----------|
| **VCP** | USB Puerto COM virtual — conexión directa USB ao procesador | Configurador (MSP) |
| **UART** | Pins TX/RX de hardware con detección de sinal de hardware | RX, GPS, Telemetría, VTX, Blackbox |
| **SoftSerial** | Serie controlada por software en calquera par de pines | Ancho de banda baixo: só telemetría |

VCP non consume un UART — físico, sempre está dispoñible para o Configurador.

## Asignación de portos

En OrniFlight Configurator, vai á pestana **Portos** para asignar funcións:

| Función | Típico UART | Notas |
|----------|-------------|-------|
| Serie RX | UART1 ou UART3 | SBUS, CRSF, IBUS, etc. |
| GPS | UART3 ou UART6 | 57600 or 115200 baud |
| Telemetría | Calquera pin TX | SmartPort, HoTT, IBUS |
| VTX (Tramp/SmartAudio) | Calquera pin TX | Un fío |
| Caixa negra | Calquera pin TX | OpenLog ou flash integrado |
| MSP | VCP (USB) | Conexión do configurador |

## OMNIBUSF4 Mapeo de portos

| UART | Pins | Uso típico |
|------|-------|------------|
| VCP | USB | MSP (Configurador) |
| UART1 | TX1/RX1 | Serial RX |
| UART3 | TX3/RX3 | GPS ou Telemetría |
| UART6 | TX6/RX6 | Gratis / Blackbox / VTX |

## SoftSerial

SoftSerial está dispoñible pero ten un ancho de banda limitado. Axeitado só para telemetría de baixa velocidade (por exemplo, 9600 baudios SmartPort). Non recomendado para Serial RX ou GPS.