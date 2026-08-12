# Första blixten

> *Få in OrniFlight på din flygkontroll — steg för steg.*

## Vad du behöver

- STM32F4-baserad flygkontroller (OMNIBUSF4, TINYFISH, MATEKF405, etc.)
- USB kabel
- [dfu-util](http://dfu-util.sourceforge.net/) eller STM32CubeProgrammer
- OrniFlight `.hex` fil från [release page](https://github.com/dantiel/OrniFlight/releases)

## Steg 1: Gå till DFU-läge

1. **Håll in BOOT-knappen** på din flygkontroll
2. **Sätt i USB** medan du håller ned knappen
3. **Släpp** efter 2 sekunder

Verifiera på macOS/Linux:

```
dfu-util -l
```

Bör visa `Found DFU: [0483:df11]`

## Steg 2: Flash

```
dfu-util -a 0 -D obj/orniflight_0.4.6_OMNIBUSF4.hex
```

## Steg 3: Första start

1. Koppla ur USB
2. Anslut USB igen (håll inte i BOOT)
3. Anslut via OrniFlight Configurator

## Steg 4: Grundläggande konfiguration

I konfiguratorn:

1. **Fliken Portar**: Konfigurera UART för din mottagare (Serial RX)
2. **Konfigurationsfliken**: Välj mottagarprotokoll (CRSF rekommenderas)
3. **Fliken Läges**: Konfigurera omkopplare för ARM, GLIDE/INDEPENDENT och PROFILE
4. **Fliken Avancerat → ONDAS**: Granska standardinställningarna, ställ in Cadence först

## Felsökning

| Problem | Fixa |
|--------|-----|
| DFU enhet hittades inte | Prova en annan USB-kabel, kontrollera BOOT-knappen |
| Flash misslyckas | Kontrollera installationen av dfu-util, USB behörigheter |
| Ingen start efter blixt | Blinka igen, verifiera att hex matchar ditt mål |
| Configurator kommer inte att ansluta | Kontrollera COM-porten och baudhastigheten |

---

*Nästa: [Basic Setup](basic_setup.html) →*