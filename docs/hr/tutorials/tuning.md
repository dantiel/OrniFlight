# PID Ugađanje

OrniFlight koristi PID (Proportional-Integral-Derivative) kontroler prilagođen za let s mahanjem krila. Ugađanje se značajno razlikuje od konvencionalnih zrakoplova zbog periodične prirode flapping potiska.

## Ornitopter PID Osnove

Za razliku od konvencionalnih zrakoplova kod kojih je potisak gotovo kontinuiran, potisak ornitoptera oscilira sa svakim zamahom krila. Ovo stvara:

- **Mreškanje potiska** pri frekvenciji flappinga (obično 5–15 Hz)
- **Ovlaštenje kontrole ovisno o fazi** — isti izlaz PID ima različit učinak ovisno o tome gdje se u ciklusu takta primjenjuje
- **Uparena dinamika roll-yaw** — asimetrični potisak krila utječe na obje osi istovremeno

## PID Uvjeti

| Pojam | Učinak | Ornitopter Napomena |
|------|--------|----------------|
| **P** | Proporcionalna — trenutna korekcija | Koristite konzervativne vrijednosti; titranje je klapno-sinkrono |
| **Ja** | Integralno — trajno ispravljanje pogrešaka | Neophodno za održavanje stava tijekom klizanja |
| **D** | Derivacija — prigušuje oscilacije | Podešen na brzinu zamaha krila, ne na oscilacije okvira |
| **F** | Feed-forward — izravni stick-to-output | Korisno za oštar odgovor na osi kotrljanja |

## Početne vrijednosti

Za ornitopter srednje veličine (1–1,5m raspon krila):

| Os | P | ja | D | F |
|------|---|---|---|---|
| Roll | 25 | 30 | 15 | 30 |
| Pitch | 30 | 35 | 20 | 35 |
| Yaw | 40 | 35 | 10 | 20 |

## Postupak podešavanja

### 1. Prvo ocijenite podešavanje

Prije podešavanja PID, postavite stope koje vam odgovaraju:
- Počnite sa RC Rate 0,90, Super Rate 0,65, Expo 0,30
- Prilagodite svom stilu letenja i veličini ornitoptera

### 2. P Dobitak

Povećajte P dok ne vidite oscilaciju na frekvenciji treptanja, a zatim smanjite za 20%:
- Oscilacija kotrljanja: njihanje krila pri brzini zamaha
- Oscilacija visine: naprijed-natrag bobbing
- Oscilacija skretanja: mahanje repom sinkronizirano s udarcima

### 3. D Dobitak

Povećajte D da ublažite odskok nakon oštrih udaraca palicom:
- Previše: servo podrhtavanje, pregrijavanje
- Premalo: zvoni nakon prestanka okretanja/nagiba

### 4. Ja dobivam

Dobivam brojače ustrajnog zanošenja:
- Povećavajte dok se ne eliminira zanošenje
- Previše: spora oscilacija na 1–2 Hz (ispod stope mlatarenja)

## ONDAS Integracija

ONDAS (Ornithopter nelinearni dinamički aerodinamički sustav) modulira izlaz PID unutar svakog zamaha krila. Nakon osnovnog PID podešavanja:

1. Postavite **Cadence Gain** — pomiče prozor modulacije u aerodinamički optimalnu fazu
2. Postavite **Ferocity P** — trenutno asimetrično pojačanje potiska
3. Postavite **Ferocity D** — anticipatory drag exploitation
4. Fino podesite **Balance** — simetriju lijevog/desnog krila

Pogledajte [ONDAS Vodič za podešavanje](ondas_tuning.html) za detaljan postupak.

## Analiza crne kutije

Omogućite bilježenje Blackboxa za vizualizaciju performansi PID. Potražite:
- **P-term oscilacije** na frekvenciji flappinga → smanjuju P
- **I-term windup** tijekom dugotrajnih okreta → smanjite I ili povećajte I-term opuštanje
- **D-term buka** od vibracija → prvo provjerite mehaničku ravnotežu, a zatim smanjite D

## Profili leta

OrniFlight podržava 3 profila leta koji se mogu mijenjati usred leta:

| Profil | Slučaj upotrebe |
|---------|----------|
| 1 | Standardno krstarenje |
| 2 | Visoka agilnost / agresivnost |
| 3 | Učinkovitost / toplinska visočina |