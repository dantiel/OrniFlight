# Serijski portovi

OrniFlight koristi serijske portove za komunikaciju s periferijama: prijemnici, GPS, telemetrija, VTX kontrola, Blackbox logging i MSP (konfiguratorska veza).

## Vrste serijskih priključaka

| Upišite | Opis | Najbolje za |
|------|------------|----------|
| **VCP** | USB Virtualni COM priključak — izravna USB veza s procesorom | Konfigurator (MSP) |
| **UART** | Hardverski TX/RX pinovi s hardverskom detekcijom signala | RX, GPS, Telemetrija, VTX, Blackbox |
| **SoftSerial** | Softverski vođen serijski na bilo kojem paru pinova | Niska propusnost: samo telemetrija |

VCP ne troši fizički UART — uvijek je dostupan za konfigurator.

## Dodjela luka

U OrniFlight konfiguratoru, idite na karticu **Portovi** za dodjelu funkcija:

| Funkcija | Tipično UART | Bilješke |
|----------|-------------|-------|
| Serijski RX | UART1 ili UART3 | SBUS, CRSF, IBUS itd. |
| GPS | UART3 ili UART6 | 57600 ili 115200 bauda |
| Telemetrija | Bilo koji TX pin | SmartPort, HoTT, IBUS |
| VTX (Skitnica/SmartAudio) | Bilo koji TX pin | Jednožilni |
| Crna kutija | Bilo koji TX pin | OpenLog ili ugrađena bljeskalica |
| MSP | VCP (USB) | Veza konfiguratora |

## OMNIBUSF4 Mapiranje porta

| UART | Pribadače | Tipična upotreba |
|------|------|------------|
| VCP | USB | MSP (Konfigurator) |
| UART1 | TX1/RX1 | Serijski RX |
| UART3 | TX3/RX3 | GPS ili telemetrija |
| UART6 | TX6/RX6 | Besplatno / Blackbox / VTX |

## SoftSerial

SoftSerial je dostupan, ali ima ograničenu propusnost. Prikladno samo za telemetriju niske brzine (npr. 9600 bauda SmartPort). Ne preporučuje se za serijski RX ili GPS.