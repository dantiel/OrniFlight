# Serielle Ports

OrniFlight verwendet serielle Schnittstellen für die Kommunikation mit Peripheriegeräten: Empfänger, GPS, Telemetrie, VTX-Steuerung, Blackbox-Protokollierung und MSP (Konfiguratorverbindung).

## Serielle Porttypen

| Geben Sie | ein Beschreibung | Am besten für |
|------|------------|----------|
| **VCP** | USB Virtueller COM Port — direkte USB Verbindung zum Prozessor | Konfigurator (MSP) |
| **UART** | Hardware-Pins TX/RX mit Hardware-Signalerkennung | RX, GPS, Telemetrie, VTX, Blackbox |
| **SoftSerial** | Softwaregesteuerte serielle Schnittstelle auf jedem Pin-Paar | Geringe Bandbreite: nur Telemetrie |

VCP verbraucht kein physisches UART —, es ist immer für den Konfigurator verfügbar.

## Portzuweisung

Gehen Sie im OrniFlight-Konfigurator zur Registerkarte **Ports**, um Funktionen zuzuweisen:

| Funktion | Typisch UART | Notizen |
|----------|-------------|-------|
| Seriennummer RX | UART1 oder UART3 | SBUS, CRSF, IBUS usw. |
| GPS | UART3 oder UART6 | 57600 oder 115200 Baud |
| Telemetrie | Beliebiger TX-Pin | SmartPort, HoTT, IBUS |
| VTX (Tramp/SmartAudio) | Beliebiger TX-Pin | Eindrahtig |
| Blackbox | Beliebiger TX-Pin | OpenLog oder Onboard-Flash |
| MSP | VCP (USB) | Konfigurator-Anbindung |

## OMNIBUSF4 Portzuordnung

| UART | Stifte | Typische Verwendung |
|------|------|------------|
| VCP | USB | MSP (Konfigurator) |
| UART1 | TX1/RX1 | Seriennummer RX |
| UART3 | TX3/RX3 | GPS oder Telemetrie |
| UART6 | TX6/RX6 | Kostenlos / Blackbox / VTX |

## SoftSerial

SoftSerial ist verfügbar, hat aber eine begrenzte Bandbreite. Nur für Telemetrie mit niedriger Rate geeignet (z. B. 9600 Baud SmartPort). Nicht empfohlen für Serial RX oder GPS.