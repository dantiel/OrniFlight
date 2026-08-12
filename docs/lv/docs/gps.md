# GPS

GPS nodrošina jūsu ornitoptera pozīcijas saglabāšanu, atgriešanos mājās un uz telemetriju balstītu navigāciju. GPS funkcijas programmā OrniFlight ir funkcionālas, taču uzskatāmas par eksperimentālām — vienmēr lido vizuālā redzamības zonā.

## Atbalstītie protokoli

- **UBLOX** (ieteicams) — UBlox binārais protokols, efektīvs un uzticams
- **NMEA** — Teksta standarta protokols

## Aparatūra

- BN-880, BN-220 vai līdzīgi UBlox M8N GPS+kompasa moduļi
- Savienojiet: TX/RX ar bezmaksas UART, plus 5V/GND
- Uzstādiet GPS tālāk no strāvas vadiem un servo kabeļiem, lai samazinātu traucējumus
- Kompasam/magnetometram jāatrodas prom no magnētiskiem avotiem (barošanas vadiem, servo)

## Konfigurācija

```
feature GPS
set gps_provider = UBLOX
set gps_sbas_mode = AUTO
set gps_auto_baud = ON
set gps_ublox_use_galileo = ON
```

1. Cilnē **Porti** piešķiriet seriālo portu GPS (Ublox noklusējuma vērtība ir 115 200 bodi).
2. Iespējojiet funkciju GPS
3. Iestatiet nodrošinātāju
4. Saglabājiet un restartējiet

## OSD Elements

GPS datos, kas tiek parādīti OSD, ir iekļauts:
- Satelītu skaits un fiksācijas veids
- GPS koordinātas (lat/gar)
- Zemes ātrums
- Augstums (GPS)
- Attālums no mājām
- Mājas virziena bultiņa

## Ornitoptera apsvērumi

- GPS antenai ir jābūt skaidrām debesīm; — stiprinājuma vieta ir ļoti svarīga ar plīvojošiem spārniem
- Mazajiem ornitopteriem svara sods ir ievērojams
- GPS asistētai RTH (Atgriezties uz sākumlapu) ir nepieciešama rūpīga navigācijas PID vērtību noregulēšana, lai nodrošinātu lidojuma dinamiku.