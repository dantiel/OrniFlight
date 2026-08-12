# Kontrole

OrniFlight koristi standardno RC stick mapiranje s ekstenzijama specifičnim za ornitopter.

## Stick Mapping

| Štap | Os | Primarni učinak |
|-------|------|---------------|
| Prigušnica (lijevo, okomito) | leptir | Amplituda flappinga / potisak |
| Skretanje (lijevo, vodoravno) | Yaw | Diferencijalni potisak krila za okretanje |
| Uspon (desno, okomito) | Pitch | Nagib naprijed/natrag |
| Roll (desno, vodoravno) | Roll | Lijeva/desna obala |

## Načini leta

| Način | Ponašanje štapa |
|------|--------------|
| **ACRO** | Palice kontroliraju kutnu brzinu — bez automatske razine |
| **ANGLE** | Kut upravljanja palicama — automatska razina kada se otpuste |
| **HORIZON** | ANGLE blizu središta, ACRO pri punom otklonu |

ACRO preporučuje se iskusnim pilotima. ANGLE je dobar za prve letove i termalno uzdizanje.

## Kontrole specifične za ornitopter

### INDEPENDENT način

Kada je način rada INDEPENDENT aktivan, svaki servo krila reagira neovisno:
- **Lijeva palica** → servo lijevo krilo
- **Desna palica** → desni servo krilo
- Omogućuje asimetrično flapiranje za agresivne manevre

### način GLIDE

način rada GLIDE zaključava oba krila u vodoravnom položaju. Ornitopter postaje jedrilica:
- **Zaklopka za gas** nema utjecaja na položaj krila
- **Pitch/Roll/Yaw** i dalje utječe na kontrolne površine repa (ako je u opremi)

### Promjena profila

Prebacivanje profila tijekom leta putem kanala AUX omogućuje promjenu parametara PID/ONDAS tijekom leta:
- **Profil 1**: Standardne postavke krstarenja
- **Profil 2**: Postavke visoke agilnosti
- **Profil 3**: Postavke učinkovitosti/klizanja

## Cijene

Konfigurirajte cijene u kartici **PID Tuning**. Za ornitoptere, počnite s konzervativnim stopama — dinamika mlataranja pojačava upravljačke ulaze:
- RC Tečaj: 0,80–1,00
- Super cijena: 0,60–0,70
- Ekspo: 0,20–0,40