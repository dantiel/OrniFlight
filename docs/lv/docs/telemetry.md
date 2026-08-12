# Telemetrija

Telemetrija nosūta lidojuma datus no OrniFlight uz jūsu radio raidītāju — akumulatora spriegumu, strāvu, RSSI, GPS koordinātas, augstumu un daudz ko citu.

## Atbalstītie protokoli

| Protokols | Radio sistēma | Vadu skaits |
|----------|-------------|-------------|
| **CRSF** | Crossfire / Tracer / ELRS | Integrēts ar RX (divvirzienu) |
| **SmartPort** | FrSky | 1 vads (TX tapa) |
| **HoTT** | Graupner | 1 vads (TX+TZ) |
| **IBUS** | FlySky | 1 vads (sensors TX) |
| **LTM** | Gaismas telemetrija (MWP) | 1 vads (TX) |

## Konfigurācija

1. Programmā Configurator → **Ports**: iestatiet UART TX tapu uz atbilstošo telemetrijas protokolu.
2. Iespējot telemetrijas funkciju: `feature TELEMETRY`
3. Ja nepieciešams, konfigurējiet telemetrijas inversiju

**CRSF** telemetrija tiek apstrādāta automātiski —, nav nepieciešams atsevišķs ports.

## SmartPort (FrSky)

SmartPort prasa signāla inversiju F4 procesoros. Vai nu:
- Izmantojiet lidojuma kontrolieri ar iebūvētu invertoru
- Izmantojiet SoftSerial ar `set tlm_inversion = ON`

```
feature TELEMETRY
set tlm_inverted = ON
set tlm_halfduplex = ON
```

## Telemetrijas dati

OrniFlight pārraida:
- VBAT spriegums (galvenais akumulators)
- Pašreizējais patēriņš / patērētais mAh
- RSSI (signāla stiprums)
- Lidojuma režīms / rokas statuss
- GPS koordinātas (ja ir aprīkojumā)
- Augstums/vario (ja barometrs)
- ONDAS lidojuma profils ir aktīvs