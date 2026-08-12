# ONDAS Guia d'afinació

> *El company pràctic de ONDAS Teoria — com ajustar cada paràmetre per la sensació.*

## Ordre d'afinació

Els paràmetres ONDAS són interdependents. Sintonitza'ls en aquesta seqüència:

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

## Pas a pas

### 1. Cadence — Trobeu la vostra finestra de fase

**Objectiu**: col·loca la modulació on la teva ala tingui més mossegada.

**Mètode**: 
- Comença a les 50
- Augmenta a 70 —, la resposta del rodatge es fa més feble?
- Disminueix a 30 —, la resposta del rodatge es fa més forta?
- El punt "més fort" és el punt màxim de la potència de la teva ala

**Signes de massa alt**: resposta suau, l'artesania se sent "retardada"
**Signes de massa baix**: Resposta brusca, rebasament en tirada

### 2. Ferocity D — Estira l'ofici

**Objectiu**: Estabilització primària sense oscil·lació.

**Mètode**:
- Comença a les 20
- Vol estacionari o constant cap endavant
- Augmenteu fins que sentiu que l'embarcació "s'endureix"
- Enrere 5 punts des d'on noteu per primera vegada l'oscil·lació

**Signes de massa alt**: vibració fina, brunzit semblant a un motor als servos
**Signes de massa baix**: l'artesania deriva, se sent solta

### 3. Ferocity P — Cruixent

**Objectiu**: responsiu, però no inquietant.

**Mètode**:
- Comença a les 15
- Copeja el pal de rotlle — l'embarcació mossega immediatament?
- Augmenteu fins que la resposta del pal sigui nítida
- Fes marxa enrere si veus un excés

**Signes de massa alt**: so després d'introduir el pal, rebot
**Signes de massa baix**: resposta suau i retardada

### 4. Balance — Afinació d'asimetria

**Objectiu**: autoritat igual en ambdues direccions.

**Mètode**:
- Volar recte i nivell
- Roda cap a l'esquerra, nota la velocitat de resposta
- Roda cap a la dreta, nota la velocitat de resposta
- Ajustar l'equilibri per igualar-los

### 5–7. Warp, Anchor, Resonance

Ajustament dels paràmetres. Ajusteu només després que 1-4 siguin sòlids.

| Param | Inici | Ajusta quan |
|-------|--------|--------------|
| Warp | 50 | La modulació se sent massa estesa o massa punta |
| Anchor | 70 | Voleu més/menys PID cru barrejat amb |
| Resonance | 30 | El vol flotant inestable o el vol cap endavant sembla sonar |

### 8. Phase 2 — Avançat

| Param | Efecte |
|--------|--------|
| Prescience | Avanç de temporització — més alt = la modulació porta més fase |
| Espelho | Acoblament diferencial — rotllo més ajustat, pot reduir l'eficiència |
| Saudade | Memòria de traç — més suau però menys sensible |
| SSFF | Injecció directa gyro→wave — comença a les 10 |

---

*L'objectiu és una embarcació que vola com si vol estar a l'aire. Si lluites, fes marxa enrere i torna a sintonitzar des de Cadence amunt.*