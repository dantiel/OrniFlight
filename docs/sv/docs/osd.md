# On-Screen Display (OSD)

OrniFlight inkluderar en inbyggd OSD (On-Screen Display) som använder MAX7456 eller AT7456E chip. Zzz14zzz lägger över flygdata på ditt FPV-videoflöde.

## Element som stöds

Konfigurera element på fliken **OSD** i OrniFlight Configurator. Dra och släpp element för att placera dem på skärmen.

### Flygdata

| Element | Visar |
|--------|--------|
| Batterispänning | Huvudbatterispänning (t.ex. 14,8V) |
| Genomsnittlig cellspänning | Spänning per cell (t.ex. 3,7V) |
| Aktuell dragning | Momentan förstärkare |
| mAh Drawn | Kumulativ förbrukad kapacitet |
| RSSI | Signalstyrka från mottagare |
| Flygläge | Aktuellt läge (INDEPENDENT, GLIDE, etc.) |
| Gasspjällsläge | Aktuell gasspjällsprocent |
| Timer | Flygtid / beväpnad tid |
| Hantverksnamn | OrniFlight hantverksnamn |

### Ornithopter-specifik

| Element | Visar |
|--------|--------|
| Flaggfrekvens | Aktuell vingslagshastighet i Hz |
| ONDAS Profil | Aktivt flygprofilnummer (1-3) |
| Cadence Fas | Strömmoduleringsfasoffset |
| Servovinkel | Vingservoläge |

## Font Management

OSD använder ett teckenbaserat displaysystem. Zzz8zzz-konfiguratorns **OSD**-flik innehåller en **Teckensnittshanterare** för att ladda upp anpassade teckensnitt och glyfer.

## CLI Inställningar

```
set osd_units = METRIC
set osd_warn_bitmask = 270335  # Warning flag bitmask
set osd_tim1 = 2560            # Timer 1 source
set osd_tim2 = 2561            # Timer 2 source
```

## Hårdvara

För närvarande stödd OSD-chip: **AT7456E** (finns på OMNIBUSF4 och kompatibla kort). MAX7456 är kompatibel och automatiskt upptäckt.