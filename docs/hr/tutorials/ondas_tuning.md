# ONDAS Vodič za podešavanje

> *Praktični pratilac teorije ONDAS — kako podesiti svaki parametar prema osjećaju.*

## Redoslijed podešavanja

ONDAS parametri su međusobno ovisni. Podesite ih ovim redoslijedom:

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

## Korak po korak

### 1. Cadence — Pronađite svoju fazu prozora

**Cilj**: Postavite modulaciju tamo gdje vaše krilo ima najveći ugriz.

**Metoda**: 
- Počnite od 50
- Povećanje na 70 — postaje li odgovor na bacanje slabiji?
- Smanjenje na 30 — postaje li odgovor na bacanje jači?
- "Najjača" točka je mjesto gdje je snaga vašeg krila vrhunac

**Znakovi previsokog**: Mješav odgovor, čini se da plovilo "kasni"
**Znakovi preniskog**: Trzaj odgovor, prekoračenje pri bacanju

### 2. Ferocity D — Učvrstite vještinu

**Cilj**: Primarna stabilizacija bez oscilacija.

**Metoda**:
- Početak u 20
- Lebdenje ili stabilan let prema naprijed
- Povećavajte dok ne osjetite da se letjelica "ukrutila"
- Odstupite 5 točaka od mjesta na kojem ste prvi put primijetili oscilaciju

**Znakovi previsoke**: Fine vibracije, zujanje poput motora u servosima
**Znakovi preniskog**: Craft zanosi, osjeća se labavo

### 3. Ferocity P — Hrskavost

**Cilj**: Odgovara, ali ne trza.

**Metoda**:
- Početak u 15
- Bump the roll stick — zagrize li craft odmah?
- Povećavajte dok reakcija štapića ne postane oštra
- Odstupite ako vidite prekoračenje

**Znakovi previsoke**: Zvono nakon unosa sticka, vraćanje
**Znakovi preniskog**: Kašast, odgođen odgovor

### 4. Balance — Podešavanje asimetrije

**Cilj**: Jednak autoritet u oba smjera.

**Metoda**:
- Letite ravno i ravno
- Okrenite se lijevo, obratite pažnju na brzinu odgovora
- Okrenite se desno, obratite pažnju na brzinu odgovora
- Podesite ravnotežu kako biste ih izjednačili

### 5–7. Warp, Anchor, Resonance

Parametri finog podešavanja. Podesite tek nakon što su 1-4 solidne.

| Param | Početak | Podesite kada |
|-------|-------|-------------|
| Warp | 50 | Čini se da je modulacija previše raširena ili previše oštra |
| Anchor | 70 | Želite više/manje sirovog PID umiješanog u |
| Resonance | 30 | Lebdenje nestabilno, ili let prema naprijed čini se zvonjavim |

### 8. Phase 2 — Napredni

| Param | Učinak |
|-------|--------|
| Prescience | Vremenski napredak — viši = modulacija vodi fazu više |
| Espelho | Diferencijalna spojka — čvršće kotrljanje, može smanjiti učinkovitost |
| Saudade | Stroke memory — glatkiji, ali manje osjetljiv |
| SSFF | Izravna injekcija gyro→valova — počinje od 10 |

---

*Cilj je letjelica koja leti kao da želi biti u zraku. Ako se borite protiv toga, odstupite i ponovno podesite od Cadence prema gore.*