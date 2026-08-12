# ONDAS — Oscilējoša normalizēta dinamiskā adaptīvā stabilizācija

## Pamatprincips

Fiksētu spārnu vai parasts gaisa kuģis ģenerē vadības spēkus **nepārtraukti** — vadības virsmas novirze vai RPM izmaiņas rada līdzsvara stāvokļa momentu. Ornitopterim tā nav. Katrs vilces grams, katrs griezes momenta ņūtons ir **saistīts ar fāzi** spārnu sitienu ciklā. Viens un tas pats spēka impulss, kas tiek pielietots dažādos gājiena punktos, rada būtiski atšķirīgus rezultātus.

ONDAS atzīst šo realitāti un modulē stabilizācijas centienus sinhroni ar plivināšanas ciklu.

---

## Cadence — Laika smadzenes

Cadence ir viskritiskākais ONDAS filtrs, jo tas nosaka **kad** korekcija notiek katrā spārna sitienā.

| Insulta fāze | Spēka pielietošanas ietekme |
|---|---|
| Downstroke centrs | Maksimālā pacēluma, apgāšanās autoritāte |
| Uz leju (bremzēšana) | Izraisītā vilkšana → griešanās moments |
| Upstroke centrs | Vilce uz aizmuguri, slīpums uz augšu |
| Uz augšu vērsta gals | Spārnu apvēršana, minimāls efekts |

**Cadence pārbīda modulācijas logu**, lai saskaņotos ar fāzi, kurā aerodinamiskā sviras svira ir garākā. Nepareiza kadence = kaujas spārnu fizika. Pareiza kadence = katrs milivats kļūst par kontroles autoritāti.

### Parametri

| Parametrs | Vērtība | Funkcija |
|-----------|-------|----------|
| `ONDAS_K0` | 1,0 | Bāzes fāzes nobīde |
| `ONDAS_K2` | 10,0 | Fāzes izplatība / asums |
| `ONDAS_PHASE_SCALE` | 0,00005 | Mazs faktors, liels sviras efekts |

---

## Ferocity P — Tūlītēja asimetriskā vilce

Ferocity P palielina **viļņu formas kvadrātu** (trapecveida forma: aiztures pie ±1, kosinusa rampa starp) proporcionāli pašreizējai PID kļūdai.

- Vairāk virzības vienā pusē → tūlītējs brīdis
- Bremzētais spārns gājiena beigās piedzīvo **izraisītu pretestību** — Šis ir pretmirklis
- Ietekme: tieša, proporcionāla, tūlītēja

---

## Ferocity D — Paredzama vilkšanas izmantošana

Ferocity D pabeidz attēlu. Ja P nodrošina vilces asimetriju, D izmanto **kontralaterālā spārna vilkšanu** kā bremzi.

- Nolasa izmaiņu kļūdu līmeni un **paredz**
- Prot apzināti izmantot palēnināta spārna vilkšanu, lai radītu sānsveres / slīpuma momentus
- P+D kopā izveido **diferenciālo momentu pāri** — vilce A pusē, vilkšana B pusē — efektīvāka nekā tikai vilce

---

## Trīs veidi Cadence/Ferocity D Palielina Ferocity

### 1. Tiešā — D palielina P straujas kļūdu maiņas laikā

Brāzmās vai agresīvos manevros `error_rate` ir liels. D to reizina un palielina pamata mežonīgumu. Spārns kļūst *asāks* (vairāk trapecveida), jo P+D kopā prasa vairāk kvadrātveida nekā P atsevišķi. Rezultāts: maksimāla autoritāte tieši kritiskos gadījumos.

### 2. Netiešā — Cadence maina sviras punktu

Cadence modulē *kad* ciklā darbojas mežonība. Loga pārvietošana aerodinamiski jutīgākā fāzē (piem., lejupejošā gājiena centrs pret augšupvirziena galu) nozīmē, ka **tāda pati nežēlības vērtība** rada lielāku efektu — efektīvu pastiprinājumu bez skaitliskām izmaiņām.

### 3. Kombinatoriskā — D × Cadence apstādināšanas laikā

Stāvā: augsts grimšanas ātrums → D nosaka ātrumu → palielina mežonību. Vienlaikus kadence novirza modulāciju lejupslīdes fāzē, kur spārnam ir maksimālais sakodiens. Saspēle: D nodrošina spēku, ritmu īstajā brīdī. Bez kadences D-spēks nonāk nepareizā fāzē un izkliedējas bezjēdzīgi.

---

## Papildu ONDAS parametri

| Parametrs | Funkcija |
|-----------|----------|
| **Balance** | Uz augšu/uz leju vilces simetrija — I termiņa novirze starp gājienu uz augšu un uz leju. Kompensē spārnu asimetriju, ražošanas pielaides un nodilumu |
| **Warp** | Apgāšanās/virzīšanās P → L/R niknuma diferenciālis — labais un kreisais spārns atsevišķi svārstās uz sānsveres ass sānsveres un pagrieziena manevriem |
| **Anchor** | Fāzes noenkurojums — bloķē modulāciju uz noteiktu fāzes atsauci, izturot novirzi |
| **Resonance** | Lidmašīnas korpusa rezonanses kompensācija — izvairās no aizraujošiem lidmašīnas korpusa strukturālajiem režīmiem |

---

## Analogija

**Cadence ir diriģents. Ferocity P un D ir instrumenti.**

Bez diriģenta viņi spēlē —, bet ne kopā. Ar vienu troksnis kļūst par mūziku.

---

## Skatīt arī

- [ONDAS skaņošanas ceļvedis](../../tutorials/ondas_tuning.html) — praktiska skaņošanas procedūra
- [MSP protokols](msp.html) — vadu formāts ONDAS parametriem
- [Lidojuma profili](profiles.html) — profilu apzinoša ONDAS konfigurācija