# Puertos serie

OrniFlight utiliza puertos serie para la comunicación con periféricos: receptores, GPS, telemetría, control VTX, registro de Blackbox y MSP (conexión del configurador).

## Tipos de puerto serie

| Tipo | Descripción | Mejor para |
|------|------------|----------|
| **VCP** | USB Virtual COM Puerto — Conexión directa USB al procesador | Configurador (MSP) |
| **UART** | Pines de hardware TX/RX con detección de señal de hardware | RX, GPS, Telemetría, VTX, Blackbox |
| **SoftSerial** | Serie controlada por software en cualquier par de pines | Ancho de banda bajo: solo telemetría |

VCP no consume un UART — físico, siempre está disponible para el Configurador.

## Asignación de puerto

En OrniFlight Configurator, vaya a la pestaña **Puertos** para asignar funciones:

| Función | Típico UART | Notas |
|----------|-------------|-------|
| Serie RX | UART1 o UART3 | SBUS, CRSF, IBUS, etc. |
| GPS | UART3 o UART6 | 57600 o 115200 baudios |
| Telemetría | Cualquier pin TX | SmartPort, HoTT, IBUS |
| VTX (Vagabundo/SmartAudio) | Cualquier pin TX | Un solo cable |
| Caja negra | Cualquier pin TX | OpenLog o flash integrado |
| MSP | VCP (USB) | Conexión del configurador |

## OMNIBUSF4 Asignación de puertos

| UART | Pines | Uso típico |
|------|------|------------|
| VCP | USB | MSP (Configurador) |
| UART1 | TX1/RX1 | Serie RX |
| UART3 | TX3/RX3 | GPS o Telemetría |
| UART6 | TX6/RX6 | Gratis / Caja negra / VTX |

## SoftSerialz

SoftSerial está disponible pero tiene un ancho de banda limitado. Adecuado sólo para telemetría de baja velocidad (por ejemplo, 9600 baudios SmartPort). No recomendado para serie RX o GPS.