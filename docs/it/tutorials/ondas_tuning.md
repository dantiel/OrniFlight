# ONDAS Guida alla sintonizzazione

> *Il compagno pratico della teoria ONDAS — su come ottimizzare ogni parametro in base alla sensazione.*

## Ordine di ottimizzazione

I parametri ONDAS sono interdipendenti. Sintonizzarli in questa sequenza:

```
1. Cadence    →  timing
2. Ferocity D →  primary stabilization
3. Ferocity P →  response crispness
4. Balance    →  upstroke/downstroke bias
5. Warp       →  modulation width
6. Anchor     →  dry/wet mix
7. Resonance  →  cycle-to-cycle memory
8. Phase 2    →  advanced (prescience, espelho, saudade, SSFF)
```

## Passo dopo passo

### 1. Cadence — Trova la tua finestra di fase

**Obiettivo**: Posiziona la modulazione dove la tua vela ha più presa.

**Metodo**: 
- Inizia alle 50
- Aumentare a 70 — la risposta al tiro diventa più debole?
- Diminuendo a 30 — la risposta al tiro diventa più forte?
- Il punto "più forte" è dove la corsa di potenza della tua vela raggiunge il picco

**Segni di troppo alto**: risposta debole, l'imbarcazione sembra "ritardata"
**Segni di troppo basso**: risposta a scatti, superamento del rollio

### 2. Ferocity D — Consolida l'imbarcazione

**Obiettivo**: stabilizzazione primaria senza oscillazioni.

**Metodo**:
- Inizio alle 20
- Volo stazionario o in avanti costante
- Aumenta finché non senti l'imbarcazione "irrigidirsi"
- Arretrare di 5 punti dal punto in cui si nota per la prima volta l'oscillazione

**Segni di troppo alto**: vibrazioni leggere, ronzio simile a quello di un motore nei servi
**Segni di troppo basso**: l'imbarcazione va alla deriva, sembra allentata

### 3. Ferocity P — Freschezza

**Obiettivo**: reattivo ma non nervoso.

**Metodo**:
- Inizio alle 15
- Colpendo il roll stick — l'imbarcazione morde immediatamente?
- Aumenta fino a quando la risposta dello stick è nitida
- Se noti un superamento, fai marcia indietro

**Segni di troppo alto**: squillo dopo l'input dello stick, rimbalzo
**Segni di troppo basso**: risposta fiacca e ritardata

### 4. Balance — Accordatura asimmetrica

**Obiettivo**: pari autorità in entrambe le direzioni.

**Metodo**:
- Vola dritto e livellato
- Rotola a sinistra, nota la velocità di risposta
- Rotola a destra, nota la velocità di risposta
- Regola il bilanciamento per equalizzarli

###5–7. Warp, Anchor, Resonance

Parametri di regolazione fine. Regolare solo dopo che 1-4 sono solidi.

| Parametro | Inizio | Regola quando |
|-------|-------|-----|
| Warp | 50| La modulazione sembra troppo estesa o troppo accentuata |
| Anchor | 70| Vuoi più/meno PID grezzo mescolato in |
| Resonance | 30| Il volo stazionario è instabile o il volo in avanti sembra squillante |

### 8. Phase 2 — Avanzato

| Parametro | Effetto |
|-------|--------|
| Prescience | Anticipo di temporizzazione — più alto = la modulazione anticipa la fase più |
| Espelho | Accoppiamento differenziale — rotolo più stretto, può ridurre l'efficienza |
| Saudade | Memoria dei tratti — più fluida ma meno reattiva |
| SSFF | L'iniezione diretta gyro→wave — inizia alle 10 |

---

*L'obiettivo è un velivolo che voli come se volesse essere nell'aria. Se stai combattendo, fai marcia indietro e risintonizzati da Cadence in su.*