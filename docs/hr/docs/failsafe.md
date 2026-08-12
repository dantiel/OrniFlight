# Sigurno od kvara

OrniFlight ima dvostupanjski sustav koji štiti vaš ornitopter u slučaju gubitka signala prijemnika.

## Dvostupanjski sustav

### Faza 1 — Otkriven gubitak signala

Pokreće se kada:
- Svaki kanal leta ima nevažeću duljinu impulsa
- Prijemnik izvještava o sigurnom načinu rada
- Nema signala s prijemnika tijekom konfiguriranog trajanja

**Akcija**: Svi kanali se prebacuju na rezervne vrijednosti (konfigurirano putem `rxfail`). Kratki prozor za oporavak počinje — ako se signal vrati, normalan let se nastavlja.

### Faza 2 — Vrijeme čuvara je isteklo

Unosi se kada stupanj 1 traje dulje od `failsafe_delay` (zadano: 400 ms) I letjelica je naoružana.

**Procedure** (konfigurirajuće putem `failsafe_procedure`):

| Postupak | Ponašanje |
|-----------|----------|
| **DROP** | Odmah razoružati — krila stati, zrakoplov se spušta |
| **LAND** | Način klizanja — krila zaključana vodoravno, kontrolirano spuštanje |

**LAND** je preporučeni postupak za ornitoptere — drži krila u neutralnom položaju za klizno spuštanje, dajući vremena za oporavak signala.

## CLI Postavke

```
set failsafe_delay = 4         # Guard time in 0.1s (4 = 400ms)
set failsafe_procedure = LAND  # DROP or LAND
set failsafe_throttle = 1000   # Fallback throttle (low)
set failsafe_switch_mode = STAGE1  # Transmitter switch behavior
```

## Prijemnik siguran

Također konfigurirajte fail-safe prijemnika za izlaz **bez impulsa** pri gubitku signala. To omogućuje kontroloru leta da otkrije gubitak i aktivira stupanj 1.

## Testiranje

Ispitajte bez greške **s odspojenom krilnom polugom** na stolu:
1. Dodijelite način rada FAILSAFE prekidaču
2. Naoružajte letjelicu
3. Uključite prekidač →, pridržavajte se sigurnosnog postupka
4. Provjerite odgovara li ponašanje servoa očekivanjima