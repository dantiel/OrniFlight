# ONDAS — Oscilirajuća normalizirana dinamička adaptivna stabilizacija

## Temeljni princip

Zrakoplov s fiksnim krilima ili konvencionalni zrakoplov generira upravljačke sile **kontinuirano** — otklon upravljačke površine ili RPM promjena proizvodi moment stabilnog stanja. Ornitopter ne. Svaki gram potiska, svaki Newton okretnog momenta, **fazno je povezan** unutar ciklusa otkucaja krila. Isti impuls sile primijenjen na različitim točkama zaveslaja daje bitno različite rezultate.

ONDAS priznaje ovu stvarnost i modulira napor stabilizacije sinkrono s ciklusom mlataranja.

---

## Cadence — Mozak za mjerenje vremena

Cadence je najkritičniji ONDAS filter jer određuje **kada** se korekcija događa unutar svakog otkucaja krila.

| Faza moždanog udara | Učinak primjene sile |
|---|---|
| Downstroke centar | Maksimalni uzgon, autoritet kotrljanja |
| Kraj hoda prema dolje (kočenje) | Inducirani otpor → moment skretanja |
| Upstroke centar | Potisak unatrag, podizanje |
| Uzlazni kraj | Preokret krila, minimalni učinak |

**Cadence pomiče prozor modulacije** kako bi se uskladio s fazom u kojoj je krak aerodinamičke poluge najduži. Pogrešna kadenca = fizika borbenog krila. Ispravna kadenca = svaki milivat postaje kontrolno tijelo.

### Parametri

| Parametar | Vrijednost | Funkcija |
|-----------|-------|----------|
| `ONDAS_K0` | 1.0 | Pomak osnovne faze |
| `ONDAS_K2` | 10,0 | Fazno širenje / oštrina |
| `ONDAS_PHASE_SCALE` | 0,00005 | Mali faktor, velika poluga |

---

## Ferocity P — Trenutačni asimetrični potisak

Ferocity P povećava **kvadratnost valnog oblika** (trapezoidno oblikovanje: zadržavanje na ±1, kosinusna rampa između) proporcionalno trenutnoj pogrešci PID.

- Više potiska na jednu stranu → trenutno
- Zakočeno krilo na kraju zamaha doživljava **inducirani otpor** — ovo je protutrenutak
- Učinak: izravan, proporcionalan, trenutan

---

## Ferocity D — Anticipatory Drag Exploitation

Ferocity D upotpunjuje sliku. Gdje P osigurava asimetriju potiska, D koristi **otpor kontralateralnog krila** kao kočnicu.

- Čita stopu pogreške promjene i **predviđa**
- Može namjerno iskoristiti otpor usporenog krila za trenutke skretanja/nagiba
- P+D zajedno stvaraju **diferencijalni momentni par** — potisak na strani A, povlačenje na strani B — učinkovitiji od samo potiska

---

## Tri načina Cadence/Ferocity D povećavaju Ferocity

### 1. Izravni — D pojačava P tijekom brze promjene pogreške

U naletima ili agresivnim manevrima, `error_rate` je velik. D to množi i dodaje osnovnoj žestini. Krilo postaje *oštrije* (trapezoidnije) jer P+D zajedno zahtijevaju više pravokutnosti nego P sam. Rezultat: maksimalan autoritet upravo kada je kritično.

### 2. Indirektno — Cadence pomiče točku poluge

Cadence modulira *kada* u ciklusu djeluje žestina. Pomicanje prozora u aerodinamički osjetljiviju fazu (npr. središte zaveslaja prema dolje u odnosu na kraj zaveslaja) znači da **ista vrijednost žestine** proizvodi više učinka — učinkovito pojačavanje bez numeričke promjene.

### 3. Kombinacija — D × Cadence tijekom oporavka od zastoja

U zastoju: visoka stopa potonuća → D otkriva brzinu → povećava žestinu. Istovremeno, kadenca pomiče modulaciju u fazu zaveslaja u kojoj krilo ima maksimalni zagriz. Međudjelovanje: D daje snagu, kadencu pravi trenutak. Bez kadence, D-force dolazi u krivu fazu i beskorisno se raspršuje.

---

## Dodatni ONDAS parametri

| Parametar | Funkcija |
|-----------|----------|
| **Balance** | Simetrija potiska gore/dolje — I-term pristranost između zaveslaja prema gore i dolje. Kompenzira asimetriju krila, proizvodne tolerancije i trošenje |
| **Warp** | Roll/Yaw P → L/R ferocity diferencijal — desno i lijevo krilo neovisno o osi zakretanja za manevre nagiba i skretanja |
| **Anchor** | Fazno sidrenje — zaključava modulaciju na određenu referencu faze, odupirući se pomaku |
| **Resonance** | Kompenzacija rezonancije konstrukcije zrakoplova — izbjegava uzbudljive strukturne modove konstrukcije zrakoplova |

---

## Analogija

**Cadence je dirigent. Ferocity P i D su instrumenti.**

Bez dirigenta sviraju — ali ne zajedno. S jednim, buka postaje glazba.

---

## Vidi također

- [ONDAS Vodič za ugađanje](../../tutorials/ondas_tuning.html) — praktični postupak ugađanja
- [MSP protokol](msp.html) — format žice za ONDAS parametre
- [Profili leta](profiles.html) — konfiguracija svjesna profila ONDAS