# Osnovno postavljanje

> *Konfigurirajte svoj ornitopter za prvi let.*

## Kontrolni popis prije leta

Prije bilo čega drugog:

- [ ] Kontrola leta bljeskala je OrniFlight
- [ ] Prijemnik povezan s odašiljačem
- [ ] Servo povezani na ispravne PWM izlaze
- [ ] Baterija spojena (krila osigurana!)

## Postavljanje prijemnika

### CRSF (preporučeno)

1. **Kartica Portovi**: Postavite UART (npr. UART1) na "Serijski RX"
2. **Konfiguracijska kartica**: Receiver Mode = "Serial-based receiver", Provider = "CRSF"
3. Uključite napajanje, provjerite pomicanje ulaza kanala na kartici Prijemnik

### SBUS / Ostalo

Isti proces — odaberite odgovarajući protokol na kartici Konfiguracija.

## Servo mapiranje

U kartici **Servos**:

| Servo | Funkcija | Zadana stopa |
|-------|----------|-------------|
| Servo 0 | Lijevo krilo | 250 Hz |
| Servo 1 | Desno krilo | 250 Hz |
| Servo 2 | Grb/kormilo | 50 Hz |

Podesite min/max/sredinu kako bi odgovarali rasponu vašeg servo uređaja. Testirajte s "Override" za potvrdu smjera.

## Odabir načina letenja

Na kartici **Načini rada**:

1. **ARM**: Dodijelite prekidaču (sigurnost!)
2. **ORNITHOPTER INDEPENDENT** ili **ORNITHOPTER GLIDE**: Odaberite primarni način leta
3. **ORNITHOPTER PROFILE**: Dodatna dodjela — za promjenu profila tijekom leta

## ONDAS Prvo podešavanje

Idite na podkarticu **Napredno → ONDAS**:

1. **Cadence dobitak**: Počnite od 50 (sredina). Ovo je najvažniji parametar.
2. **Ferocity D dobitak**: Počnite od 30. Ovo je vaša primarna stabilizacija.
3. **Ferocity P Gain**: Počnite od 20 za roll/pitch, 0 za skretanje.
4. **Balance pojačanje**: 0 (centrirano).

Priključite bateriju, **čvrsto pričvrstite ornitopter** i ARM. Promatrajte kretanje servo —, trebalo bi biti glatko, sinusoidno treptanje.

## Prvi let

1. Počnite s blagim bacanjem u vjetar
2. Koristite način rada GLIDE za prirodan osjećaj uzdizanja
3. Koristite način INDEPENDENT kada želite izravnu kontrolu frekvencije
4. Sletite, podesite ONDAS, ponovite

---

*Sljedeće: [ONDAS Vodič za podešavanje](ondas_tuning.html) →*