# RSSI

RSSI (saņemtā signāla stipruma indikators) parāda jūsu radio saites kvalitāti. OrniFlight var iegūt RSSI no analogās ievades, seriālā uztvērēja datiem vai protokola RSSI.

## RSSI Avoti

| Avots | Savienojums | Konfigurācija |
|--------|-----------|----------------|
| **Sērijas protokols** | Nav (pa seriālo RX vadu) | CRSF, GHST — automāts |
| **AUX kanāls** | Nav (TX sūta RSSI kā kanālu) | `set rssi_channel = 8` |
| **Analogā ADC** | RSSI pad uz FC → Uztvērējs RSSI out | `set rssi_adc_channel = 1` |

## Konfigurācija

### Seriāls RSSI (CRSF/GHST/SBUS)

```
set rssi_src_frame_errors = OFF
set rssi_scale = 100
set rssi_offset = 0
```

RSSI tiek pārraidīts automātiski, izmantojot seriālos protokolus. — nav nepieciešami papildu vadi.

### Analogais RSSI

Pievienojiet uztvērēja RSSI izvadi → RSSI spilventiņu uz lidojuma kontroliera:

```
set rssi_adc_channel = 1      # Use ADC channel 1
set rssi_scale = 100          # Scale to 0-100%
set rssi_offset = 0
```

### AUX Kanāls RSSI

Konfigurējiet savu raidītāju, lai nosūtītu RSSI noteiktā kanālā, pēc tam:

```
set rssi_channel = 12         # Aux channel number
set rssi_scale = 100
set rssi_offset = 0
```

## Displejs

RSSI tiek parādīts OSD, un to var pārsūtīt uz radio, izmantojot telemetriju. Konfigurējiet brīdinājuma sliekšņus:

```
set osd_rssi_alarm = 20        # Warning at 20% RSSI
```

## Ornitoptera diapazons

Ornitopteriem RSSI ir ļoti svarīgi, jo — plīvojošie spārni rada dinamiskus RF traucējumu modeļus. Uzraugiet RSSI sākotnējo testa lidojumu laikā, lai pārbaudītu uzticamu savienojuma darbību visās spārnu pozīcijās.