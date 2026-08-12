# Prvi bljesak

> *Postavljanje OrniFlight na vaš kontroler leta — korak po korak.*

## Što trebate

- kontroler leta baziran na STM32F4 (OMNIBUSF4, TINYFISH, MATEKF405, itd.)
- USB kabel
- [dfu-util](http://dfu-util.sourceforge.net/) ili STM32CubeProgrammer
- OrniFlight `.hex` datoteka sa [stranice izdanja](https://github.com/dantiel/OrniFlight/releases)

## Korak 1: Uđite u način rada DFU

1. **Držite tipku BOOT** na kontroleru leta
2. **Uključite USB** dok držite gumb
3. **Otpustite** nakon 2 sekunde

Provjerite na macOS/Linuxu:

```
dfu-util -l
```

Trebao bi pokazati `Found DFU: [0483:df11]`

## Korak 2: Flash

```
dfu-util -a 0 -D obj/orniflight_0.4.6_OMNIBUSF4.hex
```

## Korak 3: Prvo pokretanje

1. Isključite USB
2. Ponovno uključite USB (nemojte držati BOOT)
3. Povežite se preko OrniFlight konfiguratora

## Korak 4: Osnovna konfiguracija

U konfiguratoru:

1. **Kartica Portovi**: Konfigurirajte UART za vaš prijemnik (serijski RX)
2. **Konfiguracijska kartica**: Odaberite protokol prijemnika (preporučuje se CRSF)
3. **Kartica Načini rada**: Postavite prekidače ARM, GLIDE/INDEPENDENT i PROFILE
4. **Napredna kartica → ONDAS**: Pregledajte zadane postavke, prvo podesite Cadence

## Rješavanje problema

| Problem | Popravi |
|---------|-----|
| DFU uređaj nije pronađen | Pokušajte s drugim USB kabelom, provjerite gumb BOOT |
| Flash ne radi | Provjerite instalaciju dfu-util, USB dozvole |
| Nema pokretanja nakon bljeskanja | Ponovno bljeskajte, potvrdite da hex odgovara vašem cilju |
| Konfigurator se ne spaja | Provjerite COM port i brzinu prijenosa |

---

*Sljedeće: [Osnovno postavljanje](basic_setup.html) →*