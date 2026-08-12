# RSSI

RSSI (indikator jačine primljenog signala) pokazuje kvalitetu vaše radio veze. OrniFlight može izvoriti RSSI iz analognog ulaza, podataka serijskog prijemnika ili protokola RSSI.

## RSSI Izvori

| Izvor | Veza | Konfiguracija |
|--------|-----------|--------------|
| **Serijski protokol** | Ništa (preko serijske žice RX) | CRSF, GHST — automatski |
| **AUX kanal** | Ništa (TX šalje RSSI kao kanal) | `set rssi_channel = 8` |
| **Analogni ADC** | RSSI pad na FC → Prijemnik RSSI out | `set rssi_adc_channel = 1` |

## Konfiguracija

### Serijski RSSI (CRSF/GHST/SBUS)

```
set rssi_src_frame_errors = OFF
set rssi_scale = 100
set rssi_offset = 0
```

RSSI se automatski prenosi serijskim protokolima — nije potrebno dodatno ožičenje.

### Analogni RSSI

Spojite prijemnik RSSI izlaz → RSSI podloga na kontroleru leta:

```
set rssi_adc_channel = 1      # Use ADC channel 1
set rssi_scale = 100          # Scale to 0-100%
set rssi_offset = 0
```

### AUX kanal RSSI

Konfigurirajte svoj odašiljač za slanje RSSI na određenom kanalu, a zatim:

```
set rssi_channel = 12         # Aux channel number
set rssi_scale = 100
set rssi_offset = 0
```

## Prikaz

RSSI prikazan je u OSD i može se prenijeti putem telemetrije na vaš radio. Konfigurirajte pragove upozorenja:

```
set osd_rssi_alarm = 20        # Warning at 20% RSSI
```

## Raspon ornitoptera

Za ornitoptere, RSSI je kritičan — lepetanje krila stvara dinamične RF uzorke interferencije. Pratite RSSI tijekom početnih probnih letova kako biste potvrdili pouzdanu izvedbu veze na svim položajima krila.