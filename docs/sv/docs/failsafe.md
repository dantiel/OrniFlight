# Felsäker

OrniFlight har ett tvåstegs felsäkert system för att skydda din ornithopter vid förlust av mottagarens signal.

## Tvåstegssystem

### Steg 1 — Signalförlust upptäckt

Utlöst när:
- Alla flygkanaler har ogiltig pulslängd
- Mottagaren rapporterar felsäkert läge
- Ingen signal från mottagaren under en konfigurerad varaktighet

**Åtgärd**: Alla kanaler växlar till reservvärden (konfigureras via `rxfail`). Ett kort återställningsfönster börjar — om signalen återkommer, normal flygning återupptas.

### Steg 2 — Guard Time har gått ut

Anges när steg 1 varar längre än `failsafe_delay` (standard: 400ms) OCH farkosten är beväpnad.

**Procedur** (konfigurerbar via `failsafe_procedure`):

| Tillvägagångssätt | Beteende |
|----------------|--------|
| **DROP** | Avväpna omedelbart — vingar stannar, flygplan sjunker |
| **LAND** | Glidläge — vingar låsta horisontellt, kontrollerad nedstigning |

**LAND** är den rekommenderade proceduren för ornithoptrar — den håller vingarna i neutralt läge för en glidande nedstigning, vilket ger tid för signalåterställning.

## CLI Inställningar

```
set failsafe_delay = 4         # Guard time in 0.1s (4 = 400ms)
set failsafe_procedure = LAND  # DROP or LAND
set failsafe_throttle = 1000   # Fallback throttle (low)
set failsafe_switch_mode = STAGE1  # Transmitter switch behavior
```

## Mottagare felsäker

Konfigurera även din mottagares felsäkra att mata ut **inga pulser** vid signalförlust. Detta gör att flygledaren kan upptäcka förlusten och aktivera steg 1.

## Testning

Testa felsäkert **med vinglänkage frånkopplat** på bänken:
1. Tilldela FAILSAFE-läge till en switch
2. Beväpna farkosten
3. Växla omkopplaren → observera felsäker procedur
4. Verifiera servobeteendet matchar förväntningarna