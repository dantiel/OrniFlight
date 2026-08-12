# Porte seriali

OrniFlight utilizza porte seriali per la comunicazione con le periferiche: ricevitori, GPS, telemetria, controllo VTX, registrazione Blackbox e MSP (connessione al configuratore).

## Tipi di porte seriali

| Digitare | Descrizione | Ideale per |
|------|------------|----------|
| **VCP** | USB Porta COM virtuale — connessione diretta USB al processore | Configuratore (MSP) |
| **UART** | Pin hardware TX/RX con rilevamento del segnale hardware | RX, GPS, Telemetria, VTX, Scatola nera |
| **SoftSerial** | Seriale gestita dal software su qualsiasi coppia di pin | Larghezza di banda ridotta: solo telemetria |

VCP non consuma un fisico UART — è sempre disponibile per il Configuratore.

## Assegnazione del porto

Nel OrniFlight Configurator, vai alla scheda **Porte** per assegnare le funzioni:

| Funzione | Tipico UART | Note |
|----------|-------------|-------|
| Seriale RX | UART1 o UART3 | SBUS, CRSF, IBUS, ecc. |
| GPS | UART3 o UART6 | 57600 o 115200 baud |
| Telemetria | Qualsiasi TX pin | SmartPort, HoTT, IBUS |
| VTX (Vagabondo/SmartAudio) | Qualsiasi TX pin | Filo singolo |
| Scatola nera | Qualsiasi TX pin | OpenLog o flash integrato |
| MSP | VCP (USB) | Collegamento al configuratore |

## OMNIBUSF4 Mappatura delle porte

| UART | Perni | Uso tipico |
|------|------|------------|
| VCP | USB | MSP (Configuratore) |
| UART1 | TX1/RX1 | Seriale RX |
| UART3 | TX3/RX3 | GPS o Telemetria |
| UART6 | TX6/RX6 | Gratuito / Scatola nera / VTX |

##SoftSerial

SoftSerial è disponibile ma ha una larghezza di banda limitata. Adatto solo per telemetria a bassa velocità (ad esempio 9600 baud SmartPort). Non consigliato per seriale RX o GPS.