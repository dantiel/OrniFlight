# Seriālie porti

OrniFlight izmanto seriālos portus saziņai ar perifērijas ierīcēm: uztvērēju, GPS, telemetriju, VTX vadību, Blackbox reģistrēšanu un MSP (konfiguratora savienojums).

## Seriālo portu veidi

| Tips | Apraksts | Labākais |
|------|------------|----------|
| **VCP** | USB Virtuālais COM Ports — tiešs USB savienojums ar procesoru | Konfigurators (MSP) |
| **UART** | Aparatūras TX/RX tapas ar aparatūras signāla noteikšanu | RX, GPS, Telemetrija, VTX, Blackbox |
| **SoftSerial** | Programmatūras vadīts seriāls uz jebkura kontaktu pāra | Mazs joslas platums: tikai telemetrija |

VCP nepatērē fizisku UART — tas vienmēr ir pieejams konfiguratoram.

## Ostas piešķiršana

Programmā OrniFlight Configurator atveriet cilni **Porti**, lai piešķirtu funkcijas:

| Funkcija | Tipisks UART | Piezīmes |
|----------|-------------|-------|
| Seriāls RX | UART1 vai UART3 | SBUS, CRSF, IBUS utt. |
| GPS | UART3 vai UART6 | 57600 vai 115200 bodi |
| Telemetrija | Jebkurš TX pin | SmartPort, HoTT, IBUS |
| VTX (Tramp/SmartAudio) | Jebkurš TX pin | Vienvada |
| Blackbox | Jebkurš TX pin | OpenLog vai iebūvēta zibspuldze |
| MSP | VCP (USB) | Konfiguratora savienojums |

## OMNIBUSF4 Portu kartēšana

| UART | Piespraudes | Tipisks lietojums |
|------|------|-------------|
| VCP | USB | MSP (konfigurators) |
| UART1 | TX1/RX1 | Seriāls RX |
| UART3 | TX3/RX3 | GPS vai telemetrija |
| UART6 | TX6/RX6 | Bezmaksas / Blackbox / VTX |

## SoftSerial

SoftSerial ir pieejams, taču tam ir ierobežots joslas platums. Piemērots tikai zema ātruma telemetrijai (piemēram, 9600 bodi SmartPort). Nav ieteicams Serial RX vai GPS.