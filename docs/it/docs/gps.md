#GPS

GPS consente il mantenimento della posizione, il ritorno a casa e la navigazione basata sulla telemetria per il tuo ornitottero. Le funzionalità GPS in OrniFlight sono funzionali ma considerate sperimentali. — vola sempre entro la linea di vista visiva.

## Protocolli supportati

- **UBLOX** (consigliato) — Protocollo binario UBlox, efficiente e affidabile
- **NMEA** — Protocollo standard basato su testo

##Attrezzatura

- moduli BN-880, BN-220 o simili UBlox M8N GPS+Compass
- Collegare: TX/RX a uno UART libero, più 5V/GND
- Montare GPS lontano dai cavi di alimentazione e dai cavi dei servo per ridurre al minimo le interferenze
- La bussola/magnetometro deve essere lontano da fonti magnetiche (cavi di alimentazione, servi)

##Configurazione

```
feature GPS
set gps_provider = UBLOX
set gps_sbas_mode = AUTO
set gps_auto_baud = ON
set gps_ublox_use_galileo = ON
```

1. Assegna la porta seriale a GPS nella scheda **Porte** (predefinito 115200 baud per UBlox)
2. Abilita la funzione GPS
3. Imposta fornitore
4. Salva e riavvia

## OSD Elementi

I dati GPS visualizzati in OSD includono:
- Conteggio dei satelliti e tipo di correzione
- coordinate GPS (lat/lon)
- Velocità al suolo
- Altitudine (GPS)
- Distanza da casa
- Freccia direzione Home

## Considerazioni sugli ornitotteri

- L'antenna GPS deve avere una visuale del cielo limpida. La posizione di montaggio — è fondamentale con le ali che sbattono
- La penalità di peso è significativa sui piccoli ornitotteri
- GPS-assistito RTH (ritorno alla casa) richiede un'attenta regolazione dei valori di navigazione PID per le dinamiche di volo battenti