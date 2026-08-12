# PID Tuning

OrniFlight izmanto PID (proporcionālais integrālais atvasinājums) kontrolieri, kas pielāgots lidojumam ar spārnu spārnu. Noregulēšana būtiski atšķiras no parastajiem lidaparātiem, jo ​​vilces spēks ir periodisks.

## Ornitoptera PID Pamati

Atšķirībā no parastajiem lidaparātiem, kur vilces spēks ir gandrīz nepārtraukts, ornitoptera vilce svārstās ar katru spārna gājienu. Tas rada:

- **Vilces pulsācija** ar svārstību frekvenci (parasti 5–15 Hz)
- **No fāzes atkarīga vadības iestāde** — vienai un tai pašai PID izvadei ir atšķirīgs efekts atkarībā no tā, kurā gājiena ciklā tā tiek lietota
- **Savienotā sānsveres dinamika** — asimetriskā spārna vilce vienlaikus ietekmē abas asis

## PID Noteikumi

| Termiņš | Efekts | Ornitoptera piezīme |
|------|--------|------------------|
| **P** | Proporcionāla — tūlītēja korekcija | Izmantojiet konservatīvas vērtības; svārstības ir plivināšanas-sinhronas |
| **Es** | Integrāla — pastāvīga kļūdu labošana | Būtiski, lai saglabātu attieksmi slīdēšanas laikā |
| **D** | Atvasinājums — slāpē svārstības | Pielāgots spārnu gājiena ātrumam, nevis rāmja svārstībām |
| **F** | Feed-forward — tiešā stick uz izvadi | Noderīga skaidrai reakcijai uz ripošanas ass |

## Sākuma vērtības

Vidēja izmēra ornitopteram (1–1,5 m spārnu plētums):

| Ass | P | es | D | F |
|------|---|---|---|---|
| Roll | 25 | 30 | 15 | 30 |
| Piķis | 30 | 35 | 20 | 35 |
| Žāga | 40 | 35 | 10 | 20 |

## Noskaņošanas procedūra

### 1. Vispirms novērtējiet noregulēšanu

Pirms PID regulēšanas iestatiet tarifus, kas jūtas ērti:
- Sāciet ar RC Rate 0,90, Super Rate 0,65, Expo 0,30
- Pielāgojiet savam lidošanas stilam un ornitoptera izmēram

### 2. P Gain

Palieliniet P, līdz redzat svārstības ar svārstību frekvenci, pēc tam atkāpieties par 20%:
- Ripošanas svārstības: spārnu svārstības ar gājiena ātrumu
- Soļa svārstības: svārstīšanās uz priekšu un atpakaļ
- Leņķiskās svārstības: astes kustināšana sinhronizēta ar sitieniem

### 3. D Ieguvums

Palieliniet D, lai mazinātu atlēcienu pēc asas nūjas ievadīšanas:
- Pārāk daudz: servo trīce, pārkaršana
- Pārāk maz: zvana pēc sitiena/piķa apstāšanās

### 4. Es iegūstu

Es iegūstu skaitītāju pastāvīgu novirzi:
- Palieliniet, līdz tiek novērsta novirze
- Pārāk daudz: lēnas svārstības pie 1–2 Hz (zem svārstību ātruma)

## ONDAS Integrācija

ONDAS (Ornitoptera nelineārā dinamiskā aerodinamiskā sistēma) modulē PID izvadi katrā spārna gājienā. Pēc pamata PID regulēšanas:

1. Iestatiet **Cadence Gain** — pārslēdz modulācijas logu uz aerodinamiski optimālo fāzi
2. Iestatiet **Ferocity P** — tūlītēju asimetrisko vilces palielinājumu
3. Iestatiet **Ferocity D** — paredzamo vilkšanas izmantošanu
4. Precīzi noregulējiet **Balance** — kreisā/labā spārna simetriju

Detalizētu procedūru skatiet [ONDAS Tuning Guide](ondas_tuning.html).

## Blackbox analīze

Iespējojiet Blackbox reģistrēšanu, lai vizualizētu PID veiktspēju. Meklējiet:
- **P-termiņa svārstības** pie svārstību frekvences → samazina P
- **I termiņa likvidēšana** ilgstošu pagriezienu laikā → samazina I vai palielina I termiņa atslābumu
- **D-term troksnis** no vibrācijas → vispirms pārbaudiet mehānisko līdzsvaru, pēc tam samaziniet D

## Lidojuma profili

OrniFlight atbalsta 3 pārslēdzamus lidojuma profilus lidojuma laikā:

| Profils | Lietošanas gadījums |
|---------|-----------|
| 1 | Standarta kruīzs |
| 2 | Augsta veiklība / agresīva |
| 3 | Efektivitāte / termiskā paaugstināšanās |