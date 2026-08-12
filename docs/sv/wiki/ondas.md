# ONDAS — Oscillerande normaliserad dynamisk adaptiv stabilisering

## Kärnprincipen

Ett flygplan med fast vingar eller ett konventionellt flygplan genererar kontrollkrafter **kontinuerligt** — en kontrollyteavböjning eller RPM förändring producerar ett steady-state moment. En ornithopter gör det inte. Varje gram dragkraft, varje Newtons vridmoment, är **fasbunden** inom vingslagscykeln. Samma kraftimpuls som appliceras vid olika punkter i slaget ger fundamentalt olika resultat.

ONDAS erkänner denna verklighet och modulerar stabiliseringsansträngning synkront med flaxningscykeln.

---

## Cadence — Timing Brain

Cadence är det mest kritiska ONDAS-filtret eftersom det bestämmer **när** korrigering sker inom varje vingslag.

| Strokefas | Effekt av tvångsanvändning |
|---|---|
| Downstroke center | Maximalt lyft, rullbehörighet |
| Nedåtgående slut (bromsning) | Inducerad drag → girmoment |
| Uppåtgående mitt | Drag bakåt, uppåt |
| Uppåtslag slut | Vingvändning, minimal effekt |

**Cadence ändrar moduleringsfönstret** för att passa in i fasen där den aerodynamiska spakarmen är längst. Fel kadens = kampvingsfysik. Korrekt kadens = varje milliwatt blir kontrollauktoritet.

### Parametrar

| Parameter | Värde | Funktion |
|-----------|-------|---------|
| `ONDAS_K0` | 1.0 | Basfasoffset |
| `ONDAS_K2` | 10,0 | Fasspridning / skärpa |
| `ONDAS_PHASE_SCALE` | 0,00005 | Liten faktor, stor hävstång |

---

## Ferocity P — Omedelbar asymmetrisk dragkraft

Ferocity P ökar **vågformens fyrkantighet** (trapetsformning: uppehåll vid ±1, cosinusramp mellan) proportionellt mot det aktuella PID-felet.

- Mer dragkraft på ena sidan → omedelbart
- Den bromsade vingen vid slagänden upplever **inducerat motstånd** — detta är motögonblicket
- Effekt: direkt, proportionell, omedelbar

---

## Ferocity D — Föregripande Drag Exploitation

Ferocity D fullbordar bilden. Där P ger dragkraftsasymmetri, utnyttjar D **draget från den kontralaterala vingen** som en broms.

- Läser felfrekvensen för förändring och **förutser**
- Kan medvetet utnyttja draget från en saktad vinge för gir/pitch-ögonblick
- P+D skapar tillsammans ett **differentiellt momentpar** — dragkraft på sida A, dra på sida B — mer effektivt än dragkraft endast

---

## Three Ways Cadence/Ferocity D Ökar Ferocity

### 1. Direkt — D ökar P under snabb feländring

I vindbyar eller aggressiva manövrar är `error_rate` stor. D multiplicerar detta och ökar basens grymhet. Vingen blir *skarpare* (mer trapetsformad) eftersom P+D tillsammans kräver mer kvadratisk än P ensam. Resultat: maximal auktoritet just när det är kritiskt.

### 2. Indirekt — Cadence flyttar hävstångspunkten

Cadence modulerar *när* i cykeln grymhet verkar. Att flytta fönstret till en mer aerodynamiskt känslig fas (t.ex. nedåtgående mitt mot uppåtgående slutet) innebär att **samma grymhetsvärde** ger mer effekt — effektiv förstärkning utan numerisk förändring.

### 3. Kombinatorisk — D × Cadence under återställning av stall

I ett stall: hög sjunkhastighet → D känner av hastigheten → ökar grymheten. Samtidigt skiftar kadens modulering till nedåtslagsfasen där vingen har maximalt bett. Samspelet: D ger kraften, kadens i rätt ögonblick. Utan kadens kommer D-kraft till fel fas och försvinner värdelöst.

---

## Ytterligare ONDAS parametrar

| Parameter | Funktion |
|----------------|--------|
| **Balance** | Upp/ned dragkraftssymmetri — I-term bias mellan uppåtslag och nedåtslag. Kompenserar för vingasymmetri, tillverkningstoleranser och slitage |
| **Warp** | Roll/Yaw P → L/R grymhetsdifferential — höger och vänster vingar klappar oberoende på rullningsaxeln för bank- och svängmanövrar |
| **Anchor** | Fasförankring — låser modulering till en specifik fasreferens, motstår drift |
| **Resonance** | Flygplansresonanskompensation — undviker spännande strukturella lägen för flygplanet |

---

## Analogi

**Cadence är ledaren. Ferocity P och D är instrumenten.**

Utan dirigent spelar de — men inte tillsammans. Med en blir brus till musik.

---

## Se även

- [ONDAS Tuning Guide](../../tutorials/ondas_tuning.html) — praktisk stämningsprocedur
- [MSP Protocol](msp.html) — trådformat för ONDAS parametrar
- [Flygprofiler](profiles.html) — profilmedveten ONDAS-konfiguration