# Telemetrija

Telemetrija šalje podatke o letu od OrniFlight do vašeg radio odašiljača — napon baterije, struju, RSSI, GPS koordinate, nadmorsku visinu i više.

## Podržani protokoli

| Protokol | Radio sustav | Broj žica |
|----------|-------------|------------|
| **CRSF** | Unakrsna vatra / tragač / ELRS | Integriran sa RX (dvosmjerno) |
| **SmartPort** | FrSky | 1 žica (pin TX) |
| **HoTT** | Graupner | 1 žica (TX+TZ) |
| **IBUS** | FlySky | 1 žica (senzor TX) |
| **LTM** | Svjetlosna telemetrija (MWP) | 1 žica (TX) |

## Konfiguracija

1. U konfiguratoru → **Portovi**: postavite UART TX pin na odgovarajući telemetrijski protokol
2. Omogućite značajku telemetrije: `feature TELEMETRY`
3. Po potrebi konfigurirajte inverziju telemetrije

Za **CRSF**, telemetrijom se upravlja automatski — nije potreban poseban priključak.

## SmartPort (FrSky)

SmartPort zahtijeva inverziju signala na F4 procesorima. Ili:
- Koristite kontroler leta s ugrađenim pretvaračem
- Koristite SoftSerial sa `set tlm_inversion = ON`

```
feature TELEMETRY
set tlm_inverted = ON
set tlm_halfduplex = ON
```

## Telemetrijski podaci

OrniFlight prenosi:
- napon VBAT (glavna baterija)
- Trenutna potrošnja / potrošeni mAh
- RSSI (jačina signala)
- Način letenja / status ruke
- GPS koordinate (ako je u opremi)
- Nadmorska visina/vario (ako je barometar)
- ONDAS let profil aktivan