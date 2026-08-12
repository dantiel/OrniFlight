# Visualizzazione su schermo (OSD)

OrniFlight include un OSD (On-Screen Display) integrato che utilizza il chip MAX7456 o AT7456E. OSD sovrappone i dati di volo al tuo feed video FPV.

## Elementi supportati

Configura gli elementi nella scheda **OSD** del configuratore OrniFlight. Trascina e rilascia gli elementi per posizionarli sullo schermo.

### Dati del volo

| Elemento | Visualizza |
|---------|----------|
| Voltaggio della batteria | Voltaggio della batteria principale (es. 14,8 V) |
| Voltaggio medio delle celle | Voltaggio per cella (ad esempio 3,7 V) |
| Sorteggio attuale | Ampere istantanei |
| mAh Disegnata | Capacità cumulativa consumata |
| RSSI | Intensità del segnale dal ricevitore |
| Modalità volo | Modalità corrente (INDEPENDENT, GLIDE, ecc.) |
| Posizione dell'acceleratore | Percentuale attuale di accelerazione |
| Temporizzatore | Tempo di volo / tempo armato |
| Nome artigianale | OrniFlight nome artigianale |

### Specifico per gli ornitotteri

| Elemento | Visualizza |
|----------|----------|
| Frequenza di sbattimento | Frequenza attuale della corsa dell'ala in Hz |
| ONDAS Profilo | Numero del profilo di volo attivo (1-3) |
| Cadence Fase | Offset fase modulazione corrente |
| Angolo del servo | Posizione del servo dell'ala |

## Gestione dei caratteri

OSD utilizza un sistema di visualizzazione basato sui caratteri. La scheda **OSD** del configuratore OrniFlight include un **Gestore font** per caricare caratteri e glifi personalizzati.

## CLI Impostazioni

```
set osd_units = METRIC
set osd_warn_bitmask = 270335  # Warning flag bitmask
set osd_tim1 = 2560            # Timer 1 source
set osd_tim2 = 2561            # Timer 2 source
```

##Attrezzatura

Chip OSD attualmente supportato: **AT7456E** (trovato su OMNIBUSF4 e schede compatibili). MAX7456 è compatibile e rilevato automaticamente.