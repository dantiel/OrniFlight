#RSSI

RSSI (Indicatore della potenza del segnale ricevuto) mostra la qualità del collegamento radio. OrniFlight può generare RSSI da ingresso analogico, dati del ricevitore seriale o protocollo RSSI.

## RSSI Fonti

| Fonte | Connessione | Configurazione |
|--------|-----------|---------------|
| **Protocollo seriale** | Nessuno (sul cavo seriale RX) | CRSF, GHST — automatico |
| **Canale AUX** | Nessuno (TX invia RSSI come canale) | `set rssi_channel = 8` |
| **Analogico ADC** | pad RSSI acceso FC → Ricevitore RSSI fuori | `set rssi_adc_channel = 1` |

##Configurazione

### Seriale RSSI (CRSF/GHST/SBUS)

```
set rssi_src_frame_errors = OFF
set rssi_scale = 100
set rssi_offset = 0
```

RSSI viene trasmesso automaticamente dai protocolli seriali — non è necessario alcun cablaggio aggiuntivo.

### Analogico RSSI

Collegare il pad del ricevitore RSSI uscita → RSSI sul controller di volo:

```
set rssi_adc_channel = 1      # Use ADC channel 1
set rssi_scale = 100          # Scale to 0-100%
set rssi_offset = 0
```

### AUX Canale RSSI

Configura il tuo trasmettitore per inviare RSSI su un canale specifico, quindi:

```
set rssi_channel = 12         # Aux channel number
set rssi_scale = 100
set rssi_offset = 0
```

##Visualizza

RSSI viene visualizzato in OSD e può essere trasmesso tramite telemetria alla radio. Configura le soglie di avviso:

```
set osd_rssi_alarm = 20        # Warning at 20% RSSI
```

## Gamma degli ornitotteri

Per gli ornitotteri, RSSI è fondamentale. —, il battito delle ali crea schemi di interferenza RF dinamici. Monitora RSSI durante i voli di prova iniziali per verificare le prestazioni affidabili del collegamento in tutte le posizioni delle ali.