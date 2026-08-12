# LED Striscia

OrniFlight supporta strisce WS2812/SK6812 LED indirizzabili per l'indicazione dello stato e il feedback visivo.

##Configurazione

Le strisce LED sono configurate nella scheda **LED Strip** del configuratore OrniFlight. Ciascuna posizione, colore e funzione LED può essere impostata individualmente.

## Funzioni

| Funzione | Effetto visivo |
|----------|--------------|
| Indicatore della batteria | Sfumatura di colore dal verde → giallo → rosso |
| RSSI | Visualizzazione della potenza del segnale |
| Stato inserimento | Cambio colore all'attivazione/disattivazione |
| Modalità volo | Colori specifici della modalità |
| Attenzione | Sequenze di lampeggiamento per batteria scarica, failsafe |
| Indicatore di sbattimento | Impulso alla frequenza di battito attuale |
| Direzione della spinta | Spostamento di colore che indica l'uscita di rollio/beccheggio/imbardata |
| GPS | Blocco satellitare e direzione casa |

##Attrezzatura

- LED WS2812 o SK6812 RGB
- Collegati al pad/pin **LED** sul controller di volo
- Alimentare i LED da uno BEC (NON alimentare da 3,3 V — utilizzare 5 V)
- Per strisce lunghe (>8 LED), collegare l'alimentazione a 5 V direttamente ai cuscinetti della batteria, non tramite FC

## Uso dell'ornitottero

L'**Indicatore di sbattimento** è esclusivo dei LED OrniFlight — che pulsano in sincronia con la frequenza del battito delle ali, fornendo una rappresentazione visiva del ritmo del battito d'ali e aiutando a regolare i parametri della cadenza ONDAS.