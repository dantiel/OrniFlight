# Zumer

OrniFlight atbalsta aktīvos skaņas signālus skaņas statusa indikācijai un pazaudētā modeļa atrašanās vietai.

## Funkcijas

- **Ieslēgt/izslēgt** — atšķirīgi toņi
- **Zems akumulatora uzlādes līmenis** — atkārtojas brīdinājuma skaņas signāli
- **Failsafe** — SOS modelis
- **Lost Model** — nepārtraukts pīkstiens, izmantojot slēdzi
- **GPS Fix** — apstiprinājuma signāls satelīta bloķēšanā
- **Kalibrēšana** — pīkstienu modeļi žiroskopa/paātrinājuma kalibrēšanas laikā
- **RX signāls pazudis** — brīdinājums, kad uztvērēja savienojums pazūd

## Aparatūra

- Pievienojiet 5 V aktīvo zummeru (NAV pasīvo pjezo) ar **BUZZ-** un **BUZZ+** spilventiņiem
- Zummeru darbina FC — tranzistors. standarta zummeriem nav nepieciešams ārējs draiveris

## CLI Iestatījumi

```
beeper -GYRO_CALIBRATED     # Disable gyro calibration beeps
beeper -RX_LOST             # Enable receiver lost warning
beeper -ON_USB              # Disable beeper when USB connected
```

## Ornitoptera drošība

Pīkstulis ir īpaši noderīgs lieliem ornitopteriem, kas var iekrist augstā zālē vai lapotnē. Konfigurējiet BEEPER režīmu uz īstermiņa slēdzi, lai vajadzības gadījumā ātri aktivizētu.