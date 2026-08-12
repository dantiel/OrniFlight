# Podržani hardver

OrniFlight radi na standardnim kontrolerima leta STM32F3/F4/F7. Osnovna linija je **STM32F3** — letjet će svaka meta F3 sa servo-sposobnim pinovama tajmera.

## Kontrolori leta

| Odbor | MCU | IMU | Bljesak | Prijemnik | Status |
|-------|-----|-----|-------|----------|--------|
| **TINYFISH** | STM32F303 | MPU6000 (SPI) | 256 KB | FrSky D8 (integrirano) | ✅ Primarni |
| **OMNIBUSF4** | STM32F405 | MPU6000 (SPI) | 1 MB + 16 MB SPI | — | ✅ Podržano |

### TINYFISH — Najlakša OrniFlight meta

Dizajniran od strane fishpeppera, TINYFISH je idealan kontroler leta za ornitopter: lagan kao pero, baziran na F3 i nosi **integrirani FrSky D8 prijemnik** na brodu. Nema vanjskog RX, nema dodatnog ožičenja — samo napajanje, servo i letenje.

- **MCU**: STM32F303CCT6 @ 72 MHz
- **Žiroskop**: MPU6000 (SPI, moguć 8 kHz)
- **Flash**: 256 KB na čipu
- **RAM**: 40 KB
- **Prijemnik**: integrirani FrSky D8 (SBUS interno usmjeren na UART2)
- **UART-ovi**: VCP + 2 hardverska UART-a (UART1 besplatno za GPS/CRSF dodatak)
- **Ulaz**: 2-4S LiPo (izravno servo napajanje)
- **Težina**: ~2,5 g

TINYFISH dokazuje da transcendentna kontrola mlataranja ne treba F7. Zzz73zzz pokreće puni ONDAS cjevovod — 10 modulacijskih kanala, trapezoidno krilo ODE, 4 profila leta — unutar 256 KB.

### OMNIBUSF4 — Dostupan radni konj

Klasična meta F4. Jeftin, sveprisutan, sa svim značajkama sa OSD i dovoljno SPI bljeskalice za Blackbox evidentiranje. Kretanje za razvoj i veće gradnje.

- **MCU**: STM32F405RGT6 @ 168 MHz
- **Žiroskop**: MPU6000 (SPI, moguć 8 kHz)
- **Flash**: 1 MB na čipu + 16 MB SPI (Blackbox)
- **RAM**: 192 KB
- **OSD**: AT7456E (kompatibilno sa MAX7456)
- **UART-ovi**: VCP + 5 hardverskih UART-ova
- **Barometar**: BMP280 (neke varijante)
- **Ulaz**: 2-6S LiPo

---

## Anatomija ornitoptera

### Servo krila

OrniFlight kontrolira lupanje kroz PWM servo. Ključne specifikacije:

| Parametar | Tipični raspon |
|-----------|-------------|
| Pulsna širina | 500–2500 µs |
| Centar | 1500 µs |
| Učestalost | 50–330 Hz |
| Kut hoda | ±15–45° |

Za ornitoptere visokih performansi preporučuju se digitalni servo uređaji s brzinom ažuriranja od 330 Hz. Analogni servo uređaji rade na 50 Hz, ali imaju manju preciznost.

### Prijemnik

Podržan je bilo koji protokol serijskog prijemnika. CRSF (TBS Crossfire / ExpressLRS) preporučuje se za:
- Niska latencija (kritično za kontrolu flappinga)
- Ugrađena telemetrija
- RSSI preko protokola (bez dodatnog ožičenja)

### Baterija

- **2S (7.4V)**: Mali ornitopteri, izravno servo pogonjeni
- **3S (11.1V)**: srednji ornitopter, BEC potreban za servo
- **4S (14.8V)**: Veliki ornitopter, preporučuje se vanjski BEC

---

## Podržane periferije

| Periferni | Preko | Bilješke |
|-----------|-----|-------|
| GPS | UART | UBlox M8N ili kompatibilni |
| VTX | UART TX | Skitnica, SmartAudio |
| Kamera | — | Bilo koja analogna kamera FPV |
| Zujalo | BUZZ jastučić | Aktivni zujalica od 5V |
| LED traka | LED jastučić | WS2812 / SK6812 |
| OpenLog | UART TX | Zapisivanje u crnu kutiju |
| Bluetooth | UART | MSP prolaz za mobilno podešavanje |

---

## Buduće mete

OrniFlight ima za cilj podržati dodatne STM32F4/F7 ciljeve gdje je dovoljno resursa UART i timera dostupno za flapping servo kontrolu. Doprinosi su dobrodošli.