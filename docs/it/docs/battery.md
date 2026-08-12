# Monitoraggio della batteria

OrniFlight monitora la tensione della batteria principale tramite ADC (convertitore analogico-digitale). Ciò consente avvisi di batteria scarica tramite cicalino, stato LED e motivi di strisce LED.

## Caratteristiche

- Rilevamento automatico del conteggio delle celle alla connessione (in base alle tensioni min/max delle celle)
- Avviso di batteria scarica con soglie configurabili
- Rilevamento corrente per consumo mAh (se supportato da FC)
- Tensione visualizzata in OSD e trasmessa tramite telemetria

## Obiettivi supportati

Tutti i controller di volo supportati (OMNIBUSF4, TINYFISH) includono il monitoraggio VBAT tramite partitore di tensione.

## Connessioni

**VERIFICARE SEMPRE LA POLARITÀ.** Misurare le tensioni previste prima del collegamento. Una tensione errata o una polarità invertita distruggeranno il tuo controller di volo.

### OMNIBUSF4

Collegare la batteria principale al pad VBAT. Il partitore di tensione integrato gestisce direttamente fino a 6S.

### TINYFISH

VBAT viene instradato attraverso l'ingresso di alimentazione della scheda — non è necessaria alcuna connessione separata.

## CLI Impostazioni

```
set vbat_min_cell_voltage = 330       # Minimum per-cell voltage (3.3V)
set vbat_max_cell_voltage = 430       # Maximum per-cell voltage (4.3V)
set vbat_warning_cell_voltage = 350   # Warning threshold (3.5V)
set battery_meter_type = ADC
set current_meter_type = ADC          # If current sensor available
```

## Sicurezza

Le batterie LiPo non devono mai essere scaricate al di sotto di 3,5 V per cella sotto carico. Le soglie configurabili di OrniFlight aiutano a garantire un funzionamento sicuro e la longevità della batteria.