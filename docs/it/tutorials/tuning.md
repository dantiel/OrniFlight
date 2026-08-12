# PID Sintonia

OrniFlight utilizza un controller PID (Proporzionale-Integrale-Derivativo) adattato per il volo ad ala battente. La messa a punto differisce significativamente da quella degli aerei convenzionali a causa della natura periodica della spinta sbattente.

## Nozioni di base sull'ornitottero PID

A differenza degli aerei convenzionali in cui la spinta è quasi continua, la spinta degli ornitotteri oscilla ad ogni colpo d'ala. Questo crea:

- **Ondulazione della spinta** alla frequenza di sbattimento (tipicamente 5–15 Hz)
- **Autorità di controllo dipendente dalla fase** — la stessa uscita PID ha effetti diversi a seconda del punto del ciclo di corsa in cui viene applicata
- **Dinamica roll-yaw accoppiata** — la spinta asimmetrica dell'ala influisce su entrambi gli assi contemporaneamente

## PID Termini

| Termine | Effetto | Nota sull'ornitottero |
|------|--------|-----------------|
| **P** | Correzione immediata proporzionale — | Utilizzare valori conservativi; l'oscillazione è sincrona al battito delle ali |
| **Io** | Correzione errori persistenti integrali — | Indispensabile per mantenere l'assetto durante le planate |
| **D** | Il derivato — smorza le oscillazioni | Sintonizzato sulla frequenza della corsa dell'ala, non sulle oscillazioni del telaio |
| **Cazzo** | Feed-forward — stick-to-output diretto | Utile per una risposta nitida sull'asse di rollio |

## Valori iniziali

Per un ornitottero di medie dimensioni (apertura alare 1–1,5 m):

| Asse | P| Io | D | F |
|------|---|---|---|---|
| Rotolo | 25| 30| 15| 30|
| Passo | 30| 35| 20| 35|
| Imbardata | 40| 35| 10| 20|

## Procedura di ottimizzazione

### 1. Prima la regolazione della velocità

Prima di accordare PID, imposta le frequenze che ti sembrano comode:
- Inizia con RC Tasso 0,90, Super Tasso 0,65, Expo 0,30
- Adatta al tuo stile di volo e alle dimensioni dell'ornitottero

### 2. Guadagno P

Aumenta P finché non vedi l'oscillazione alla frequenza di sbattimento, quindi diminuisci del 20%:
- Oscillazione del rollio: oscillazione dell'ala alla frequenza della corsa
- Oscillazione del passo: bobbing avanti-indietro
- Oscillazione dell'imbardata: scodinzolio sincronizzato con i colpi

### 3. Guadagno D

Aumenta D per smorzare il rimbalzo dopo input bruschi della levetta:
- Troppo: jitter del servo, surriscaldamento
- Troppo poco: squillo dopo l'arresto del rollio/beccheggio

### 4. Ci guadagno

Ottengo contatori deriva persistente:
- Aumentare fino all'eliminazione della deriva
- Troppo: oscillazione lenta a 1–2 Hz (al di sotto della velocità di sbattimento)

## ONDAS Integrazione

ONDAS (Ornithopter Nonlinear Dynamic Aerodynamic System) modula l'uscita PID all'interno di ogni colpo d'ala. Dopo l'accordatura base di PID:

1. Imposta **Cadence Gain** — sposta la finestra di modulazione sulla fase aerodinamicamente ottimale
2. Imposta **Ferocity P** — immediato aumento della spinta asimmetrica
3. Impostare **Ferocity D** — sfruttamento anticipato della resistenza
4. Perfeziona **Balance** — la simmetria dell'ala sinistra/destra

Vedere la [Guida alla sintonizzazione ONDAS](ondas_tuning.html) per la procedura dettagliata.

## Analisi della scatola nera

Abilita la registrazione Blackbox per visualizzare le prestazioni PID. Cerca:
- **Oscillazione del termine P** alla frequenza di battito → riduce P
- **Avvolgimento del termine I** durante le virate sostenute → riduce il rilassamento del I termine o aumenta il relax del termine I
- **Rumore del termine D** derivante dalle vibrazioni → controllare prima il bilanciamento meccanico, quindi ridurre D

## Profili di volo

OrniFlight supporta 3 profili di volo commutabili durante il volo:

| Profilo | Caso d'uso |
|---------|----------|
| 1| Crociera standard |
| 2| Elevata agilità/aggressività |
| 3| Efficienza / impennata termica |