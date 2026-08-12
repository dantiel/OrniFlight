# Načini leta

Načini se mijenjaju preko AUX prekidača na vašem odašiljaču. Svaki način rada može se dodijeliti određenom rasponu kanala AUX u kartici **Načini** u OrniFlight konfiguratoru.

## Standardni načini rada

| Način | Funkcija |
|------|----------|
| **ARM** | Omogući kontrolu leta (motori/servos aktivni) |
| **ANGLE** | Automatsko niveliranje — letjelica se vraća na nivo kada se štapovi centriraju |
| **HORIZON** | Hibridni način kuta — blizu središta, akro na punoj palici |
| **ACRO** | Zadano — nema automatske razine, čista kontrola brzine |
| **AIRMODE** | Održava PID petlju aktivnom pri nultom gasu za puni autoritet |

## OrniFlight-specifični načini rada

| ID | Način | Funkcija |
|----|------|----------|
| 50 | **INDEPENDENT** | Neovisna kontrola krila — svako krilo odgovara na vlastiti servo kanal |
| 51 | **GLIDE** | Način klizanja — krila zaključana u vodoravnom položaju za uzdizanje |
| 52 | **PROFILE** | Odabir profila leta — prebacivanje između 3 profila PID/ONDAS |

## Uslužni načini rada

| Način | Funkcija |
|------|----------|
| **BEEPER** | Aktivirajte zvučni signal za lociranje izgubljenog zrakoplova |
| **BLACKBOX** | Pokretanje/zaustavljanje Blackbox zapisivanja |
| **FAILSAFE** | Ručno aktiviranje sigurnog stupnja 2 (prekidač za paniku) |
| **OSD** | Uključi prikaz OSD |
| **TELEMETRY** | Omogući/onemogući telemetrijski izlaz |

## Bilješke o ornitopteru

- **INDEPENDENT** način je jedinstven za OrniFlight — i omogućuje servo mapiranje po krilu za asimetrični potisak i diferencijalnu kontrolu krila
- **GLIDE** način rada drži krila u neutralnom položaju, što je korisno za toplinsko uzdizanje i energetski učinkovito spuštanje
- **PROFILE** prebacivanje omogućuje promjene parametara ONDAS tijekom leta za različite uvjete leta (npr. krstarenje nasuprot agresivnom manevriranju)