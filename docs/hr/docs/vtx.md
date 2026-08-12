# Video odašiljač (VTX)

OrniFlight podržava VTX kontrolu za FPV ornitoptere. Moduli VTX mogu se konfigurirati putem konfiguratora OrniFlight, MSP ili CLI — postavljanjem pojasa, kanala, razine snage i načina rada u jami.

## Podržani protokoli

1. **IRC Tramp** — Čest na malim VTX modulima, idealan za lagane FPV ornitoptere
2. **TBS SmartAudio** — Digitalni protokol s podrškom za pit mode
3. **RTC6705** — Izravna kontrola SPI na pločama s integriranim VTX (npr. SPRACINGF3NEO)

## Konfiguracija

VTX postavkama se upravlja putem kartice **VTX** u OrniFlight konfiguratoru ili putem CLI:

```
set vtx_band = 5           # Raceband
set vtx_channel = 1        # 5658 MHz
set vtx_power = 2          # 200mW
set vtx_low_power_disarm = ON  # Lower power when disarmed
set vtx_pit_mode_freq = 0  # Pit mode frequency (0 = disabled)
```

## Serijski priključak

VTX kontrola zahtijeva namjenski UART TX pin. Konfigurirajte priključak na kartici **Priključci** s periferijom `IRC Tramp` ili `TBS SmartAudio`.

## FPV Razmatranja ornitoptera

- Težina je kritična — odaberite lagane VTX module (Tramp Nano, Everyine Nano)
- Montaža antene: osigurajte udaljenost od mahanja krilima
- Filtriranje snage: priključite napajanje VTX nakon filtra LC kako biste izbjegli servo šum u videu
- Pit mod se preporučuje za testiranje na stolu kako bi se izbjeglo pregrijavanje malih VTX modula