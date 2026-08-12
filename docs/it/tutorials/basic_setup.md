# Configurazione di base

> *Configura il tuo ornitottero per il primo volo.*

## Lista di controllo pre-volo

Prima di ogni altra cosa:

- [] Il controllore di volo ha lampeggiato con OrniFlight
- [ ] Ricevitore collegato al trasmettitore
- [ ] Servi collegati alle uscite PWM corrette
- [ ] Batteria collegata (ali protette!)

## Configurazione del ricevitore

### CRSF (consigliato)

1. **Scheda Porte**: imposta UART (ad esempio UART1) su "Serial RX"
2. **Scheda Configurazione**: Modalità ricevitore = "Ricevitore basato su seriale", Provider = "CRSF"
3. Spegnere e riaccendere, verificare che gli ingressi dei canali si spostino nella scheda Ricevitore

### SBUS / Altro

Stesso processo — selezionare il protocollo appropriato nella scheda Configurazione.

## Mappatura dei servi

Nella **scheda Servi**:

| Servo | Funzione | Tasso predefinito |
|-------|----------|-------------|
| Servo 0 | Ala sinistra | 250 Hz |
| Servo1 | Ala destra | 250 Hz |
| Servo2 | Cresta/Timone | 50 Hz |

Regola min/max/medio per adattarlo alla portata del tuo servo. Prova con "Override" per verificare la direzione.

## Selezione della modalità di volo

Nella **scheda Modalità**:

1. **ARM**: Assegna a un interruttore (sicurezza!)
2. **ORNITHOPTER INDEPENDENT** o **ORNITHOPTER GLIDE**: scegli la modalità di volo principale
3. **ORNITHOPTER PROFILE**: assegnazione — opzionale per il cambio del profilo in volo

## ONDAS Prima accordatura

Vai alla **sottoscheda Avanzate → ONDAS**:

1. **Cadence Guadagno**: inizia da 50 (metà). Questo è il parametro più importante.
2. **Ferocity D Guadagno**: inizia da 30. Questa è la tua stabilizzazione principale.
3. **Ferocity P Guadagno**: Inizia da 20 per rollio/beccheggio, 0 per imbardata.
4. **Balance Guadagno**: 0 (centrato).

Collega una batteria, **fissa saldamente l'ornitottero** e ARM. Osservare il movimento del servo —: dovrebbe essere un battito regolare e sinusoidale.

## Primo volo

1. Inizia con un leggero lancio nel vento
2. Utilizza la modalità GLIDE per una sensazione di volo naturale
3. Utilizzare la modalità INDEPENDENT quando si desidera il controllo diretto della frequenza
4. Atterra, regola ONDAS, ripeti

---

*Successivo: [ONDAS Guida alla sintonizzazione](ondas_tuning.html) →*