# Failsafe

OrniFlight ha un sistema di sicurezza a due stadi per proteggere il tuo ornitottero in caso di perdita del segnale del ricevitore.

## Sistema a due stadi

### Rilevata perdita di segnale fase 1 —

Attivato quando:
- Qualsiasi canale di volo ha una lunghezza dell'impulso non valida
- Il ricevitore segnala la modalità failsafe
- Nessun segnale dal ricevitore per una durata configurata

**Azione**: tutti i canali passano ai valori di fallback (configurati tramite `rxfail`). Inizia una breve finestra di recupero — se il segnale ritorna, il volo normale riprende.

### Fase 2 — Tempo di guardia scaduto

Si entra quando la Fase 1 persiste per più di `failsafe_delay` (predefinito: 400 ms) E il velivolo è armato.

**Procedure** (configurabili tramite `failsafe_procedure`):

| Procedura | Comportamento |
|-----------|----------|
| **DROP** | Disarmare immediatamente — le ali si fermano, l'aereo scende |
| **LAND** | Modalità planata — ali bloccate in orizzontale, discesa controllata |

**LAND** è la procedura consigliata per gli ornitotteri — mantiene le ali in posizione neutra per una discesa planata, dando il tempo per il recupero del segnale.

## CLI Impostazioni

```
set failsafe_delay = 4         # Guard time in 0.1s (4 = 400ms)
set failsafe_procedure = LAND  # DROP or LAND
set failsafe_throttle = 1000   # Fallback throttle (low)
set failsafe_switch_mode = STAGE1  # Transmitter switch behavior
```

## Failsafe del ricevitore

Configura anche il fail-safe del tuo ricevitore in modo che non emetta **nessun impulso** in caso di perdita di segnale. Ciò consente al controllore di volo di rilevare la perdita e attivare la Fase 1.

## Test

Prova il failsafe **con il collegamento dell'ala scollegato** sul banco:
1. Assegna la modalità FAILSAFE a un interruttore
2. Armare l'imbarcazione
3. Attivare l'interruttore → e osservare la procedura di failsafe
4. Verificare che il comportamento del servo corrisponda alle aspettative