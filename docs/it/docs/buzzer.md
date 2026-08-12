#Cicalino

OrniFlight supporta cicalini attivi per l'indicazione acustica dello stato e la posizione del modello smarrito.

## Funzioni

- **Inserisci/Disinserisci** — toni distinti
- **Batteria scarica** — ripetuti segnali acustici di avviso
- Modello **Failsafe** — SOS
- **Modello perduto** — segnale acustico continuo tramite interruttore
- **GPS Correzione** — tono di conferma sull'aggancio del satellite
- **Calibrazione** Sequenza di segnali acustici — durante la calibrazione del giroscopio/accelerazione
- **RX Segnale perso** Avviso — quando la connessione del ricevitore si interrompe

##Attrezzatura

- Collega un cicalino attivo da 5 V (NON un piezo passivo) ai pad **BUZZ-** e **BUZZ+**
- Il cicalino è pilotato da un transistor sul FC —, non è necessario alcun driver esterno per i cicalini standard

## CLI Impostazioni

```
beeper -GYRO_CALIBRATED     # Disable gyro calibration beeps
beeper -RX_LOST             # Enable receiver lost warning
beeper -ON_USB              # Disable beeper when USB connected
```

## Sicurezza degli ornitotteri

Il segnale acustico è particolarmente utile per i grandi ornitotteri che potrebbero atterrare nell'erba alta o nel fogliame. Configura la modalità BEEPER su un interruttore momentaneo per un'attivazione rapida quando necessario.