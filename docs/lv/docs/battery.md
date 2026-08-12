# Akumulatora uzraudzība

OrniFlight uzrauga galvenā akumulatora spriegumu, izmantojot ADC (analogo-digitālo pārveidotāju). Tas nodrošina brīdinājumus par zemu akumulatora uzlādes līmeni, izmantojot skaņas signālu, statusa LED un LED joslu modeļus.

## Funkcijas

- Automātiska šūnu skaita noteikšana savienojuma laikā (pamatojoties uz minimālo/maksimālo šūnu spriegumu)
- Brīdinājums par zemu akumulatora uzlādes līmeni ar konfigurējamiem sliekšņiem
- Pašreizējā mAh patēriņa noteikšana (ja to atbalsta FC)
- Spriegums tiek parādīts OSD un tiek pārraidīts, izmantojot telemetriju

## Atbalstītie mērķi

Visi atbalstītie lidojumu kontrolieri (OMNIBUSF4, TINYFISH) ietver VBAT uzraudzību, izmantojot sprieguma dalītāju.

## Savienojumi

**VIENMĒR PĀRBAUDIET POLARITĀTI.** Pirms pievienošanas izmēriet paredzamo spriegumu. Nepareizs spriegums vai apgriezta polaritāte iznīcinās jūsu lidojuma kontrolieri.

### OMNIBUSF4

Pievienojiet galveno akumulatoru VBAT paliktnim. Borta sprieguma dalītājs tieši apstrādā līdz pat 6S.

### TINYFISH

VBAT tiek novirzīts caur plates barošanas ieeju — nav nepieciešams atsevišķs savienojums.

## CLI iestatījumi

```
set vbat_min_cell_voltage = 330       # Minimum per-cell voltage (3.3V)
set vbat_max_cell_voltage = 430       # Maximum per-cell voltage (4.3V)
set vbat_warning_cell_voltage = 350   # Warning threshold (3.5V)
set battery_meter_type = ADC
set current_meter_type = ADC          # If current sensor available
```

## Drošība

LiPo akumulatorus nekad nedrīkst izlādēt zem 3,5 V uz vienu elementu zem slodzes. Zzz3zzz konfigurējamie sliekšņi palīdz nodrošināt drošu darbību un akumulatora ilgmūžību.