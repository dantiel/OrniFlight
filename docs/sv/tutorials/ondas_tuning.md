# ONDAS Tuning Guide

> *Den praktiska följeslagaren till ONDAS Theory — hur man ställer in varje parameter efter känsla.*

## Tuning Order

ONDAS parametrar är beroende av varandra. Ställ in dem i denna sekvens:

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

## Steg för steg

### 1. Cadence — Hitta ditt fasfönster

**Mål**: Placera moduleringen där din vinge har mest bett.

**Metod**: 
- Börja vid 50
- Öka till 70 — blir rollresponsen svagare?
- Minska till 30 — blir rollresponsen starkare?
– Den "starkaste" punkten är där din vings kraftslag toppar

**Tecken på för högt**: Grumpig respons, båten känns "försenad"
**Tecken på för lågt**: Ryckig respons, överskjutning vid kast

### 2. Ferocity D — Steady the Craft

**Mål**: Primär stabilisering utan oscillation.

**Metod**:
- Börjar kl 20
- Sväva eller sväva framåt
- Öka tills du känner att hantverket "stelnar"
- Backa 5 punkter från där du först märker svängning

**Tecken på för högt**: Fina vibrationer, motorliknande surr i servon
**Tecken på för lågt**: Hantverksdrift, känns löst

### 3. Ferocity P — Crispness

**Mål**: Responsiv men inte ryckig.

**Metod**:
- Börjar kl 15
- Bump the roll stick — biter hantverket direkt?
- Öka tills stickresponsen är skarp
- Backa om du ser överskott

**Tecken på för högt**: Ringning efter stickinmatning, studs tillbaka
**Tecken på för lågt**: Grötig, försenad respons

### 4. Balance — Asymmetri Tuning

**Mål**: Lika auktoriteter i båda riktningarna.

**Metod**:
- Flyg rakt och jämnt
- Rulla åt vänster, notera svarshastighet
- Rulla åt höger, notera svarshastighet
- Justera balansen för att utjämna dem

### 5–7. Warp, Anchor, Resonance

Finjustera parametrar. Justera först efter 1-4 är solida.

| Param | Starta | Justera när |
|-------|-------|----------------|
| Warp | 50 | Modulering känns för spridd eller för toppig |
| Anchor | 70 | Vill ha mer/mindre raw PID blandat in |
| Resonance | 30 | Att sväva instabilt eller flyga framåt känns ringigt |

### 8. Phase 2 — Avancerat

| Param | Effekt |
|-------|--------|
| Prescience | Timing advance — högre = modulering leder fas mer |
| Espelho | Differentialkoppling — tätare rulle, kan minska effektiviteten |
| Saudade | Slagminne — mjukare men mindre lyhörd |
| SSFF | Direkt gyro→wave-injektion — börjar kl. 10 |

---

*Målet är ett hantverk som flyger som det vill vara i luften. Om du kämpar mot det, backa och återställa från Cadence up.*