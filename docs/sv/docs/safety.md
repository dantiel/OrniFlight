# Säkerhet

## Checklista före flygning

1. **Vingar**: Se till att vingarna är säkert monterade och länkaget är intakt
2. **Batteri**: Fulladdat, ordentligt säkrat, korrekt cellantal
3. **Kontroller**: Verifiera sticksvaren på fliken Configurator-mottagare
4. **Failsafe**: Testa på bänken före flygning (se [Failsafe](failsafe.html))
5. **Arm-omkopplare**: Konfigurera och testa — lita aldrig på enbart spakarmering
6. **Launch Area**: Fri från människor, hinder och överliggande hinder

## Armsäkerhet

OrniFlight använder flera säkerhetsanordningar innan tillkoppling:

- **Låg gas**: Gasnivån måste vara minst
- **Nivå**: Hantverket måste vara någorlunda jämnt
- **RX Signal**: Giltig mottagarsignal krävs
- **CPU Load**: Systemet får inte överbelastas
- **Kalibrering**: Accelerometer och gyro måste kalibreras

## Säkerhet under flygning

- **Flyg inom visuell synlinje**
- Håll avstånd till människor och djur
- Övervaka batterispänningen — land innan varningströskeln
- I FPV: flyg alltid med en spotter
- Vind: ornithoptrar kan vara vindkänsliga — vet dina gränser

## Akutrutiner

| Situation | Åtgärd |
|----------------|--------|
| Förlust av orientering | Växla till INDEPENDENT-läge, mittspakar |
| Signalförlust | Failsafe kommer att landa automatiskt (om proceduren LAND konfigurerad) |
| Vingskador | Avväpna omedelbart — vingar stoppa |
| Fågelangrepp | Avväpna, bedöm skador innan återuppkoppling |
| Lågt batteri | Landa omedelbart — ornithoptrar har ingen autorotation |

## Ornithopter-specifika risker

- **Klämrisk**: Flaxande vingar kan orsaka skada — håll händerna fria när de är beväpnade
- **Länkkopplingsfel**: Kontrollera alla stötstänger och kulleder före flygning
- **Resonance**: Vissa flaxande frekvenser kan excitera flygkroppsresonanser — ställa in ONDAS svep för att undvika
- **Glidspärr**: Om vingservon misslyckas i icke-neutralt läge är kontrollerad landning omöjlig — testservons felsäkra positioner