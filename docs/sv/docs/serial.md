# Seriella portar

OrniFlight använder seriella portar för kommunikation med kringutrustning: mottagare, GPS, telemetri, VTX-kontroll, Blackbox-loggning och MSP (Configurator-anslutning).

## Seriella porttyper

| Skriv | Beskrivning | Bäst för |
|------|----------------|--------|
| **VCP** | USB Virtuell COM Port — direkt USB anslutning till processor | Konfigurator (MSP) |
| **UART** | Hårdvara TX/RX stift med hårdvarusignaldetektering | RX, GPS, Telemetri, VTX, Blackbox |
| **SoftSerial** | Programvarudriven serie på valfritt stiftpar | Låg bandbredd: endast telemetri |

VCP förbrukar inte en fysisk UART — den är alltid tillgänglig för konfiguratorn.

## Port Tilldelning

I OrniFlight Configurator, gå till fliken **Portar** för att tilldela funktioner:

| Funktion | Typiskt UART | Anteckningar |
|--------|-------------|--------|
| Seriell RX | UART1 eller UART3 | SBUS, CRSF, IBUS, etc. |
| GPS | UART3 eller UART6 | 57600 eller 115200 baud |
| Telemetri | Alla TX-stift | SmartPort, HoTT, IBUS |
| VTX (Tramp/SmartAudio) | Alla TX-stift | Enkeltråd |
| Blackbox | Alla TX-stift | OpenLog eller inbyggd blixt |
| MSP | VCP (USB) | Konfiguratoranslutning |

## OMNIBUSF4 Portmappning

| UART | Pins | Typisk användning |
|------|------|--------|
| VCP | USB | MSP (Konfigurator) |
| UART1 | TX1/RX1 | Seriell RX |
| UART3 | TX3/RX3 | GPS eller telemetri |
| UART6 | TX6/RX6 | Gratis / Blackbox / VTX |

## SoftSerial

SoftSerial är tillgängligt men har begränsad bandbredd. Lämplig endast för telemetri med låg hastighet (t.ex. 9600 baud SmartPort). Rekommenderas inte för seriell RX eller GPS.