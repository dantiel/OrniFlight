# ONDAS — Stabilizzazione adattiva dinamica normalizzata oscillante

## Il principio fondamentale

Un velivolo ad ala fissa o convenzionale genera forze di controllo **continuamente** — una deflessione della superficie di controllo o un cambiamento RPM produce un momento stazionario. Un ornitottero no. Ogni grammo di spinta, ogni Newton di coppia, è **legato in fase** all'interno del ciclo del battito d'ali. Lo stesso impulso di forza applicato in punti diversi della corsa produce risultati fondamentalmente diversi.

ONDAS riconosce questa realtà e modula lo sforzo di stabilizzazione in modo sincrono con il ciclo di sbattimento.

---

## Cadence — Il cervello del cronometraggio

Cadence è il filtro ONDAS più critico perché determina **quando** avviene la correzione all'interno di ciascun battito d'ala.

| Fase di corsa | Effetto dell'applicazione della forza |
|---|---|
| Centro corsa discendente | Portanza massima, autorità di rollio |
| Fine discesa (frenata) | Trascinamento indotto → momento di imbardata |
| Centro salita | Spinta all'indietro, beccheggio |
| Fine salita | Inversione dell'ala, effetto minimo |

**Cadence sposta la finestra di modulazione** per allinearla con la fase in cui il braccio della leva aerodinamica è più lungo. Cadenza sbagliata = lotta alla fisica delle ali. Cadenza corretta = ogni milliwatt diventa autorità di controllo.

### Parametri

| Parametro | Valore | Funzione |
|-----------|-------|----------|
| `ONDAS_K0` | 1.0 | Offset fase base |
| `ONDAS_K2` | 10.0 | Diffusione di fase/nitidezza |
| `ONDAS_PHASE_SCALE` | 0.00005 | Piccolo fattore, grande leva finanziaria |

---

## Ferocity P — Spinta asimmetrica immediata

Ferocity P aumenta la **ortogonalità della forma d'onda** (forma trapezoidale: sosta su ±1, rampa coseno tra) proporzionalmente all'errore PID corrente.

- Più spinta da un lato → momento immediato
- L'ala frenata a fine corsa sperimenta una **resistenza indotta** — questo è il contromomento
- Effetto: diretto, proporzionale, immediato

---

## Ferocity D — Sfruttamento anticipato della resistenza

Ferocity D completa il quadro. Laddove P fornisce asimmetria di spinta, D sfrutta la **resistenza dell'ala controlaterale** come freno.

- Legge il tasso di variazione dell'errore e **anticipa**
- Può sfruttare deliberatamente la resistenza di un'ala rallentata per i momenti di imbardata/beccheggio
- P+D insieme creano una **coppia di momenti differenziali** — spinta sul lato A, trascinamento sul lato B — più efficiente della sola spinta

---

## Tre modi Cadence/Ferocity D Aumenta Ferocity

### 1. — D diretto aumenta P durante il cambiamento rapido dell'errore

Nelle raffiche o nelle manovre aggressive, `error_rate` è ampio. D lo moltiplica e lo aggiunge alla ferocia di base. L'ala diventa *più affilata* (più trapezoidale) perché P+D insieme richiedono più ortogonalità rispetto a P da solo. Risultato: massima autorità proprio quando è critico.

### 2. Indiretto — Cadence sposta il punto di leva finanziaria

Cadence modula *quando* nel ciclo agisce la ferocia. Spostare la finestra in una fase più sensibile dal punto di vista aerodinamico (ad esempio, centro della corsa verso il basso rispetto alla fine della corsa verso l'alto) significa che lo **stesso valore di ferocia** produce un effetto — più efficace, amplificato senza variazione numerica.

### 3. Combinatorio — D × Cadence durante il recupero dallo stallo

In stallo: alto tasso di caduta → D rileva il tasso di → che aumenta la ferocia. Allo stesso tempo, la cadenza sposta la modulazione nella fase di discesa dove l'ala ha la massima aderenza. L'interazione: D fornisce la forza, la cadenza il momento giusto. Senza cadenza, la Forza D arriva nella fase sbagliata e si dissipa inutilmente.

---

## Parametri ONDAS aggiuntivi

| Parametro | Funzione |
|-----------|----------|
| **Balance** | Simmetria della spinta su/giù — Distorsione a I-termine tra corsa in salita e corsa in discesa. Compensa l'asimmetria delle ali, le tolleranze di fabbricazione e l'usura |
| **Warp** | Roll/Yaw P → Differenziale ferocia L/R — le ali destra e sinistra sbattono indipendentemente sull'asse di rollio per manovre di virata e virata |
| **Anchor** | L'ancoraggio di fase — blocca la modulazione su un riferimento di fase specifico, resistendo alla deriva |
| **Resonance** | La compensazione della risonanza della cellula — evita eccitanti modalità strutturali della cellula |

---

## Analogia

**Cadence è il direttore d'orchestra. Ferocity P e D sono gli strumenti.**

Senza direttore d'orchestra suonano — ma non insieme. Con uno il rumore diventa musica.

---

## Vedi anche

- [Guida alla sintonizzazione ONDAS](../../tutorials/ondas_tuning.html) procedura pratica di sintonizzazione —
- [Protocollo MSP](msp.html) formato cavo — per i parametri ONDAS
- [Profili di volo](profiles.html) configurazione — ONDAS compatibile con il profilo