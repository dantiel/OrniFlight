# GPS

GPS omogućuje zadržavanje položaja, povratak kući i navigaciju temeljenu na telemetriji za vaš ornitopter. Značajke GPS u OrniFlight su funkcionalne, ali se smatraju eksperimentalnima — uvijek lete unutar vidnog polja.

## Podržani protokoli

- **UBLOX** (preporučeno) — UBlox binarni protokol, učinkovit i pouzdan
- **NMEA** — Standardni protokol temeljen na tekstu

## Hardver

- BN-880, BN-220 ili slični moduli UBlox M8N GPS+Compass
- Spojite: TX/RX na besplatni UART, plus 5V/GND
- Montirajte GPS dalje od strujnih žica i servo kabela kako biste smanjili smetnje
- Kompas/magnetometar mora biti udaljen od magnetskih izvora (žice za napajanje, servo)

## Konfiguracija

```
feature GPS
set gps_provider = UBLOX
set gps_sbas_mode = AUTO
set gps_auto_baud = ON
set gps_ublox_use_galileo = ON
```

1. Dodijelite serijski priključak GPS u kartici **Portovi** (zadano 115200 baud za UBlox)
2. Omogućite značajku GPS
3. Postavite davatelja
4. Spremite i ponovno pokrenite sustav

## OSD Elementi

GPS podaci prikazani u OSD uključuju:
- Broj satelita i vrsta popravka
- GPS koordinate (šir./duž.)
- Brzina kretanja
- Nadmorska visina (GPS)
- Udaljenost od kuće
- Strelica za smjer kući

## Razmatranja ornitoptera

- GPS antena mora imati pogled na čisto nebo — mjesto postavljanja je kritično s lepetanjem krila
- Kazna težine je značajna za male ornitoptere
- RTH potpomognut GPS (povratak kući) zahtijeva pažljivo podešavanje navigacijskih PID vrijednosti za dinamiku flapping leta