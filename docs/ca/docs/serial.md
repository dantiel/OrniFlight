# Ports sèrie

OrniFlight utilitza ports sèrie per a la comunicació amb perifèrics: receptors, GPS, telemetria, control VTX, registre Blackbox i MSP (connexió del configurador).

## Tipus de port sèrie

| Tipus | Descripció | Millor per |
|------|-------------|-----------|
| **VCP** | USB Port virtual COM — connexió directa USB al processador | Configurador (MSP) |
| **UART** | Pins TX/RX de maquinari amb detecció de senyal de maquinari | RX, GPS, Telemetria, VTX, Blackbox |
| **SoftSerial** | Serial impulsat per programari en qualsevol parell de pins | Ample de banda baix: només telemetria |

VCP no consumeix un UART — físic, sempre està disponible per al Configurador.

## Assignació de ports

A OrniFlight Configurator, aneu a la pestanya **Ports** per assignar funcions:

| Funció | UART típic | Notes |
|----------|-------------|-------|
| Serial RX | UART1 o UART3 | SBUS, CRSF, IBUS, etc. |
| GPS | UART3 o UART6 | 57600 o 115200 bauds |
| Telemetria | Qualsevol pin TX | SmartPort, HoTT, IBUS |
| VTX (Tramp/SmartAudio) | Qualsevol pin TX | Un sol cable |
| Caixa negra | Qualsevol pin TX | OpenLog o flash integrat |
| MSP | VCP (USB) | Connexió del configurador |

## OMNIBUSF4 Mapatge de ports

| UART | Pins | Ús típic |
|------|-------|-------------|
| VCP | USB | MSP (Configurador) |
| UART1 | TX1/RX1 | Serial RX |
| UART3 | TX3/RX3 | GPS o Telemetria |
| UART6 | TX6/RX6 | Gratuït / Blackbox / VTX |

## SoftSerial

SoftSerial està disponible, però té una amplada de banda limitada. Apte només per a telemetria de baixa velocitat (p. ex., 9600 bauds SmartPort). No recomanat per a sèrie RX o GPS.