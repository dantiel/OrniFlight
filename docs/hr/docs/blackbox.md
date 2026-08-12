# Zapisivanje u Blackbox

Blackbox bilježi podatke o letu za analizu nakon leta, podešavanje i otklanjanje pogrešaka. OrniFlight podržava bilježenje na ugrađeni flash čip ili vanjski OpenLog uređaj.

## Što se bilježi

- **Žiroskop** — neobrađena i filtrirana kutna brzina po 3 osi
- **Akcelerometar** — 3-osno ubrzanje
- **PID Izlaz** — P, I, D, F doprinosi po osi
- **ONDAS** — Cadence, Ferocity P/D i drugi parametri specifični za lepršanje
- **RC naredbe** — drže pozicije nakon tečaja/izložbe
- **Servo izlaz** — konačni izlaz za svaki servo kanal
- **Baterija** — napon i struja po iteraciji
- **GPS** — položaj, brzina, visina (ako je dostupno)

## Postavljanje

### Ugrađena bljeskalica (OMNIBUSF4)

Zzz34zzz uključuje ugrađenu flash memoriju od 16 MB za Blackbox evidentiranje. Omogući u konfiguratoru:

1. Kartica **Crna kutija** → Postavite `Blackbox logging device` na `Onboard flash`
2. Postavite stopu zapisivanja (preporučeno: `1/N` s N=2-4 za F4 ciljeve)
3. Dodijelite prekidač za početak/zaustavljanje zapisivanja

### Vanjski OpenLog

Spojite OpenLog na besplatni UART TX pin:

1. Kartica **Portovi** → Postavite UART na `Blackbox logging` na 115200 bauda
2. Spojite OpenLog: FC TX → OpenLog RX, plus 5V/GND

## Alati za analizu

- [Blackbox Explorer](https://github.com/betaflight/blackbox-log-viewer) — preglednik zapisa na webu
- `blackbox_decode` — pretvoriti u CSV za prilagođenu analizu

## ONDAS-specifično

Blackbox je bitan za podešavanje ONDAS parametara. Zabilježeni ONDAS podaci uključuju:
- `ondas_cadence_phase` — vrijeme prozora modulacije
- `ondas_ferocity_p` / `ondas_ferocity_d` — asimetrične komponente potiska
- `ondas_balance` — ravnoteža lijevo/desno krilo
- Izlaz po servu pri svakoj iteraciji

To omogućuje preciznu analizu mehanike flapsanja i korekcije asimetrije krila.