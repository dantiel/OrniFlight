# Pamata iestatīšana

> *Konfigurējiet savu ornitopteri pirmajam lidojumam.*

## Kontrolsaraksts pirms lidojuma

Pirms visa cita:

- [ ] Lidojuma kontrolieris mirgo ar OrniFlight
- [ ] Uztvērējs ir saistīts ar raidītāju
- [ ] Servo pieslēgti pareizajām PWM izejām
- [ ] Akumulators ir pievienots (spārni nostiprināti!)

## Uztvērēja iestatīšana

### CRSF (ieteicams)

1. **Cilne Ports**: iestatiet UART (piem., UART1) uz "Serial RX"
2. ** Konfigurācijas cilne**: uztvērēja režīms = "seriāls uztvērējs", nodrošinātājs = "CRSF"
3. Strāvas padeves cikls, pārbaudiet, vai kanālu ieejas pārvietojas cilnē Uztvērējs

### SBUS / Cits

Tas pats process — atlasiet atbilstošo protokolu cilnē Konfigurācija.

## Servo kartēšana

Cilnē **Servos**:

| Servo | Funkcija | Noklusējuma likme |
|-------|----------|-------------|
| Servo 0 | Kreisais spārns | 250 Hz |
| Servo 1 | Labais spārns | 250 Hz |
| Servo 2 | Crest/Stūre | 50 Hz |

Pielāgojiet min/max/vidējo, lai atbilstu jūsu servo diapazonam. Lai pārbaudītu virzienu, pārbaudiet, izmantojot opciju Override.

## Lidojuma režīma izvēle

Cilnē **Režīmi**:

1. **ARM**: piešķiriet slēdzim (drošība!)
2. **ORNITHOPTER INDEPENDENT** vai **ORNITHOPTER GLIDE**: izvēlieties savu galveno lidojuma režīmu
3. **ORNITHOPTER PROFILE**: izvēles — piešķiršana profila pārslēgšanai lidojuma laikā.

## ONDAS Pirmā skaņošana

Dodieties uz **Papildu → ONDAS apakšcilni**:

1. **Cadence pieaugums**: sāciet no 50 (vidus). Šis ir vissvarīgākais parametrs.
2. **Ferocity D pieaugums**: sāciet no 30. Šī ir jūsu galvenā stabilizācija.
3. **Ferocity P pieaugums**: sāciet ar 20, lai ripotu/soļu, 0, lai pagrieztos.
4. **Balance pieaugums**: 0 (centrā).

Pievienojiet akumulatoru, **nostipriniet ornitopteri stingri** un ARM. Ievērojiet servo kustību — tai jābūt gludai, sinusoidālai plivināšanai.

## Pirmais lidojums

1. Sāciet ar maigu metienu vējā
2. Izmantojiet GLIDE režīmu, lai iegūtu dabisku planējošo sajūtu
3. Izmantojiet INDEPENDENT režīmu, ja vēlaties tiešu frekvences vadību
4. Nozemējiet, noregulējiet ONDAS, atkārtojiet

---

*Nākamais: [ONDAS skaņošanas ceļvedis](ondas_tuning.html) →*