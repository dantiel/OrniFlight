# RSSI

RSSI (Received Signal Strength Indicator) visar kvaliteten på din radiolänk. OrniFlight kan hämta RSSI från analog ingång, seriell mottagardata eller protokoll RSSI.

## RSSI Källor

| Källa | Anslutning | Konfiguration |
|--------|--------|--------------|
| **Serial Protocol** | Ingen (över seriell RX tråd) | CRSF, GHST — automatisk |
| **AUX Channel** | Ingen (TX skickar RSSI som kanal) | `set rssi_channel = 8` |
| **Analog ADC** | RSSI pad på FC → Mottagare RSSI ut | `set rssi_adc_channel = 1` |

## Konfiguration

### Seriell RSSI (CRSF/GHST/SBUS)

```
set rssi_src_frame_errors = OFF
set rssi_scale = 100
set rssi_offset = 0
```

RSSI sänds automatiskt av seriella protokoll — ingen extra ledning behövs.

### Analog RSSI

Anslut mottagare RSSI utgång → RSSI pad på flygkontrollern:

```
set rssi_adc_channel = 1      # Use ADC channel 1
set rssi_scale = 100          # Scale to 0-100%
set rssi_offset = 0
```

### AUX Kanal RSSI

Konfigurera din sändare för att skicka RSSI på en specifik kanal, sedan:

```
set rssi_channel = 12         # Aux channel number
set rssi_scale = 100
set rssi_offset = 0
```

## Display

RSSI visas i OSD och kan sändas via telemetri till din radio. Konfigurera varningströsklar:

```
set osd_rssi_alarm = 20        # Warning at 20% RSSI
```

## Ornithopter Range

För ornithoptrar är RSSI avgörande — flaxande vingar skapar dynamiska RF interferensmönster. Övervaka RSSI under första testflygningar för att verifiera tillförlitlig länkprestanda vid alla vingpositioner.