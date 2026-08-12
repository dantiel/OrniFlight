# Registrazione nella scatola nera

Blackbox registra i dati di volo per l'analisi, la messa a punto e il debug post-volo. OrniFlight supporta la registrazione sul chip flash integrato o sul dispositivo OpenLog esterno.

## Cosa viene registrato

- **Gyro** — velocità angolare a 3 assi grezza e filtrata
- **Accelerometro** — Accelerazione a 3 assi
- **PID Uscita** — Contributi P, I, D, F per asse
- **ONDAS** — Cadence, Ferocity P/D e altri parametri specifici del battito d'ali
- **Comandi RC** — posiziona lo stick dopo i tassi/expo
- **Uscita Servo** — uscita finale su ciascun canale servo
- **Batteria** — tensione e corrente per iterazione
- **GPS** — posizione, velocità, altitudine (se disponibile)

## Configurazione

### Flash integrato (OMNIBUSF4)

OMNIBUSF4 include 16 MB di flash integrato per la registrazione Blackbox. Abilita nel Configuratore:

1. Scheda **Blackbox** → Imposta `Blackbox logging device` su `Onboard flash`
2. Imposta la velocità di registrazione (consigliato: `1/N` con N=2-4 per target F4)
3. Assegnare un interruttore per avviare/interrompere la registrazione

### Esterno OpenLog

Collega OpenLog a un pin UART TX libero:

1. Scheda **Porte** → Imposta UART su `Blackbox logging` a 115200 baud
2. Collegare OpenLog: FC TX → OpenLog RX, più 5 V/GND

## Strumenti di analisi

- [Blackbox Explorer](https://github.com/betaflight/blackbox-log-viewer) — visualizzatore di log basato sul web
- `blackbox_decode` — converti in CSV per analisi personalizzate

## ONDAS-Specifico

Blackbox è essenziale per ottimizzare i parametri ONDAS. I dati ONDAS registrati includono:
- Temporizzazione della finestra di modulazione `ondas_cadence_phase` —
- componenti di spinta asimmetrici `ondas_ferocity_p` / `ondas_ferocity_d` —
- `ondas_balance` — bilanciamento ala sinistra/destra
- Uscita per servo ad ogni iterazione

Ciò consente un'analisi precisa della meccanica del battito d'aria e delle correzioni dell'asimmetria alare.