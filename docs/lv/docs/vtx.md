# Video raidītājs (VTX)

OrniFlight atbalsta VTX vadību FPV ornitopteriem. VTX moduļus var konfigurēt, izmantojot OrniFlight Configurator, MSP vai CLI — iestatīšanas joslu, kanālu, jaudas līmeni un bedres režīmu.

## Atbalstītie protokoli

1. **IRC Tramp** — Izplatīts maziem VTX moduļiem, ideāli piemērots viegliem FPV ornitopteriem
2. **TBS SmartAudio** — Digitālais protokols ar bedres režīma atbalstu
3. **RTC6705** — Tieša SPI vadība uz dēļiem ar integrētu VTX (piemēram, SPRACINGF3NEO)

## Konfigurācija

Zzz26zzz iestatījumi tiek pārvaldīti, izmantojot cilni **VTX** programmā OrniFlight Configurator vai CLI:

```
set vtx_band = 5           # Raceband
set vtx_channel = 1        # 5658 MHz
set vtx_power = 2          # 200mW
set vtx_low_power_disarm = ON  # Lower power when disarmed
set vtx_pit_mode_freq = 0  # Pit mode frequency (0 = disabled)
```

## Seriālais ports

VTX vadībai ir nepieciešams īpašs UART TX tapa. Konfigurējiet portu cilnē **Porti**, izmantojot `IRC Tramp` vai `TBS SmartAudio` perifērijas ierīci.

## FPV Ornitoptera apsvērumi

- Svars ir kritisks — izvēlieties vieglos VTX moduļus (Tramp Nano, Eachine Nano)
- Antenas stiprinājums: nodrošiniet atstarpi no plīvojošiem spārniem
- Jaudas filtrēšana: pievienojiet VTX jaudu pēc LC filtra, lai izvairītos no servo trokšņa video
- Bedru režīms ir ieteicams testēšanai uz stenda, lai izvairītos no mazu VTX moduļu pārkaršanas