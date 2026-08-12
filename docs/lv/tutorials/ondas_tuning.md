# ONDAS Tuning Guide

> *Praktiskais ONDAS teorijas pavadonis — kā pielāgot katru parametru pēc sajūtas.*

## Noskaņošanas pasūtījums

ONDAS parametri ir savstarpēji atkarīgi. Noskaņojiet tos šādā secībā:

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

## Soli pa solim

### 1. Cadence — Atrodiet savu fāzes logu

**Mērķis**: novietojiet modulāciju tur, kur jūsu spārnam ir visvairāk koduma.

**Metode**: 
- Sāciet no 50
- Palielināt līdz 70 — vai reakcija uz ripošanu kļūst vājāka?
- Samaziniet līdz 30 — vai reakcija uz ripošanu kļūst spēcīgāka?
- "Spēcīgākais" punkts ir jūsu spārna spēka sitiena maksimums

**Pazīmes par pārāk augstu**: neskaidra reakcija, šķiet, ka darbs ir "aizkavējies"
**Pazīmes par pārāk zemu līmeni**: saraustīta reakcija, pārsniegums ripošanā

### 2. Ferocity D — Steady the Craft

**Mērķis**: primārā stabilizācija bez svārstībām.

**Metode**:
- Sākums pulksten 20
- Lidojiet kursoru vai vienmērīgi virzieties uz priekšu
- Palieliniet, līdz jūtat, ka kuģis "stingst"
- Atkāpieties par 5 punktiem no vietas, kur pirmo reizi pamanāt svārstības

**Pazīmes par pārāk augstu**: smalka vibrācija, motoram līdzīga buzz servos
**Pārāk zema līmeņa pazīmes**: amatniecība dreifē, jūtas vaļīga

### 3. Ferocity P — Kraukšķīgums

**Mērķis**: atsaucīgs, bet ne raustošs.

**Metode**:
- Sākums pulksten 15
- Bump the roll stick — vai kuģis uzreiz iekož?
- Palieliniet, līdz nūjas reakcija ir kraukšķīga
- Atkāpieties, ja redzat pārsniegumu

**Pazīmes par pārāk augstu**: zvana pēc nūjas ievades, atlēciens
**Pazīmes par pārāk zemu**: niezoša, novēlota reakcija

### 4. Balance — Asimetrijas skaņošana

**Mērķis**: vienlīdzīga autoritāte abos virzienos.

**Metode**:
- Lidojiet taisni un horizontāli
- Ritiniet pa kreisi, ievērojiet reakcijas ātrumu
- Ritiniet pa labi, ievērojiet reakcijas ātrumu
- Pielāgojiet līdzsvaru, lai tos izlīdzinātu

### 5–7. Warp, Anchor, Resonance

Parametru precizēšana. Pielāgojiet tikai pēc tam, kad 1–4 ir cieti.

| Param | Sākt | Pielāgot Kad |
|-------|-------|--------------|
| Warp | 50 | Modulācija šķiet pārāk izkliedēta vai pārāk izteikta |
| Anchor | 70 | Vēlaties vairāk/mazāk neapstrādātu PID mix in |
| Resonance | 30 | Lidošana ir nestabila vai lidojums uz priekšu jūtas niezošs |

### 8. Phase 2 — Advanced

| Param | Efekts |
|-------|--------|
| Prescience | Laika avanss — lielāks = modulācijas vadu fāze vairāk |
| Espelho | Diferenciāļa sakabe — stingrāka roll, var samazināt efektivitāti |
| Saudade | Insulta atmiņa — vienmērīgāka, bet mazāk atsaucīga |
| SSFF | Tiešā gyro→wave injekcija — sākums 10 |

---

*Mērķis ir kuģis, kas lido tā, it kā gribētu būt gaisā. Ja cīnāties pret to, atkāpieties un pārskaņojiet no Cadence uz augšu.*