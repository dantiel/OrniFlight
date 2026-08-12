# Zujalo

OrniFlight podržava aktivne zujalice za zvučnu indikaciju statusa i lokaciju izgubljenog modela.

## Funkcije

- **Aktiviraj/Razoružaj** — različiti tonovi
- **Niska baterija** — ponavljajući zvučni signali upozorenja
- **Failsafe** — SOS uzorak
- **Izgubljeni model** — kontinuirani zvučni signal putem prekidača
- **GPS Fix** — ton potvrde na satelitskoj bravi
- **Kalibracija** — obrasci zvučnih signala tijekom kalibracije žiroskopa/ubrzanja
- **RX Signal Lost** — upozorenje kada se veza prijemnika prekine

## Hardver

- Spojite aktivnu zujalicu od 5 V (NE pasivni piezo) na **BUZZ-** i **BUZZ+** jastučiće
- Zujalo pokreće tranzistor na FC — nije potreban vanjski upravljački program za standardne zujalice

## CLI Postavke

```
beeper -GYRO_CALIBRATED     # Disable gyro calibration beeps
beeper -RX_LOST             # Enable receiver lost warning
beeper -ON_USB              # Disable beeper when USB connected
```

## Sigurnost ornitoptera

Biper je posebno koristan za velike ornitoptere koji mogu sletjeti u visoku travu ili lišće. Konfigurirajte način rada BEEPER na trenutnom prekidaču za brzu aktivaciju kada je potrebno.