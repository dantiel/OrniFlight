# GPS

GPS möjliggör positionshållning, återgång till hemmet och telemetribaserad navigering för din ornithopter. GPS funktioner i OrniFlight är funktionella men anses vara experimentella — flyger alltid inom visuell synlinje.

## Protokoll som stöds

- **UBLOX** (rekommenderas) — UBlox binärt protokoll, effektivt och pålitligt
- **NMEA** — Textbaserat standardprotokoll

## Hårdvara

- BN-880, BN-220 eller liknande UBlox M8N GPS+Compass-moduler
- Anslut: TX/RX till en gratis UART, plus 5V/GND
- Montera GPS borta från strömkablar och servokablar för att minimera störningar
- Kompass/magnetometer måste vara borta från magnetiska källor (strömkablar, servon)

## Konfiguration

```
feature GPS
set gps_provider = UBLOX
set gps_sbas_mode = AUTO
set gps_auto_baud = ON
set gps_ublox_use_galileo = ON
```

1. Tilldela seriell port till GPS på fliken **Portar** (standard 115200 baud för UBlox)
2. Aktivera GPS-funktionen
3. Ställ in leverantör
4. Spara och starta om

## OSD Element

GPS data som visas i OSD inkluderar:
- Satelliträkning och fixtyp
- GPS koordinater (lat/längd)
- Markhastighet
- Höjd (GPS)
- Avstånd hemifrån
- Pil för hemriktning

## Ornithopter överväganden

- GPS antenn måste ha klar himmel — monteringsplatsen är avgörande med flaxande vingar
– Viktstraffet är betydande på små ornithoptrar
- GPS-assisterad RTH (Return to Home) kräver noggrann inställning av navigeringsvärden för PID för flaxande flygdynamik