# Praćenje baterije

OrniFlight prati napon glavnog akumulatora putem ADC (analogno-digitalni pretvarač). To omogućuje upozorenja o niskoj razini baterije putem zujalice, statusa LED i LED uzoraka trake.

## Značajke

- Automatsko otkrivanje broja ćelija pri povezivanju (na temelju minimalnog/maksimalnog napona ćelije)
- Upozorenje o niskoj bateriji s podesivim pragovima
- Senzor struje za potrošnju mAh (ako to podržava FC)
- Napon prikazan u OSD i prenesen putem telemetrije

## Podržani ciljevi

Svi podržani kontroleri leta (OMNIBUSF4, TINYFISH) uključuju VBAT nadzor preko razdjelnika napona.

## Veze

**UVIJEK PROVJERITE POLARITET.** Prije spajanja izmjerite očekivane napone. Neispravan napon ili obrnuti polaritet uništit će vaš kontroler leta.

### OMNIBUSF4

Spojite glavnu bateriju na VBAT jastučić. Ugrađeni razdjelnik napona upravlja izravno do 6S.

### TINYFISH

VBAT je usmjeren kroz ulaz napajanja ploče — nije potrebna posebna veza.

## CLI Postavke

```
set vbat_min_cell_voltage = 330       # Minimum per-cell voltage (3.3V)
set vbat_max_cell_voltage = 430       # Maximum per-cell voltage (4.3V)
set vbat_warning_cell_voltage = 350   # Warning threshold (3.5V)
set battery_meter_type = ADC
set current_meter_type = ADC          # If current sensor available
```

## Sigurnost

LiPo baterije se nikada ne smiju prazniti ispod 3,5 V po ćeliji pod opterećenjem. Pragovi koji se mogu konfigurirati OrniFlight osiguravaju siguran rad i dugovječnost baterije.