# Summer

OrniFlight stöder aktiva summer för hörbar statusindikering och plats för förlorad modell.

## Funktioner

- **Avaktivera/avaktivera** — distinkta toner
- **Lågt batteri** — upprepade varningspip
- **Feilsäkert** — SOS mönster
- **Förlorad modell** — kontinuerlig pipsignal via switch
- **GPS Fix** — bekräftelseton på satellitlås
- **Kalibrering** — pipmönster under gyro/accel-kalibrering
- **RX Signal Lost** — varning när mottagarens anslutning avbryts

## Hårdvara

- Anslut en 5V aktiv summer (INTE en passiv piezo) till **BUZZ-** och **BUZZ+** pads
- Summern drivs av en transistor på FC — ingen extern drivrutin behövs för standard summer

## CLI Inställningar

```
beeper -GYRO_CALIBRATED     # Disable gyro calibration beeps
beeper -RX_LOST             # Enable receiver lost warning
beeper -ON_USB              # Disable beeper when USB connected
```

## Ornithopter Safety

Piparen är särskilt användbar för stora ornithoptrar som kan landa i högt gräs eller löv. Konfigurera BEEPER-läget på en momentan omkopplare för snabb aktivering vid behov.