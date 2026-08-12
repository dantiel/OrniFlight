# Videosändare (VTX)

OrniFlight stöder VTX-kontroll för FPV ornithopters. VTX-moduler kan konfigureras via OrniFlight Configurator, MSP eller CLI — inställningsband, kanal, effektnivå och pit-läge.

## Protokoll som stöds

1. **IRC Tramp** — Vanlig på små VTX-moduler, idealisk för lättvikts FPV ornithoptrar
2. **TBS SmartAudio** — Digitalt protokoll med stöd för gropläge
3. **RTC6705** — Direkt SPI-kontroll på kort med integrerad VTX (t.ex. SPRACINGF3NEO)

## Konfiguration

VTX-inställningar hanteras via fliken **VTX** i OrniFlight Configurator, eller via CLI:

```
set vtx_band = 5           # Raceband
set vtx_channel = 1        # 5658 MHz
set vtx_power = 2          # 200mW
set vtx_low_power_disarm = ON  # Lower power when disarmed
set vtx_pit_mode_freq = 0  # Pit mode frequency (0 = disabled)
```

## Seriell port

VTX kontroll kräver en dedikerad UART TX pin. Konfigurera porten på fliken **Portar** med `IRC Tramp` eller `TBS SmartAudio` kringutrustning.

## FPV Ornithopter-överväganden

- Vikt är avgörande — välj lätta VTX-moduler (Tramp Nano, Everyine Nano)
- Antennmontering: säkerställ avstånd från flaxande vingar
- Strömfiltrering: anslut VTX ström efter LC filter för att undvika servobrus i video
- Pit-läge rekommenderas för bänktestning för att undvika överhettning av små VTX-moduler