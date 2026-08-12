# LED Strip

OrniFlight atbalsta adresējamās WS2812/SK6812 LED joslas statusa indikācijai un vizuālai atgriezeniskajai saitei.

## Konfigurācija

LED sloksnes ir konfigurētas OrniFlight Configurator cilnē **LED Strip**. Katru LED pozīciju, krāsu un funkciju var iestatīt atsevišķi.

## Funkcijas

| Funkcija | Vizuālais efekts |
|----------|--------------|
| Akumulatora indikators | Krāsu gradients no zaļa → dzeltena → sarkana |
| RSSI | Signāla stipruma displejs |
| Arm State | Krāsas maiņa iedarbinot/izslēdzot |
| Lidojuma režīms | Režīmam raksturīgas krāsas |
| Brīdinājums | Mirkšķināšanas raksti zema akumulatora uzlādes līmeņa gadījumā, droši |
| Plīvošanas indikators | Impulss pie strāvas svārstību frekvences |
| Vilces virziens | Krāsu nobīde, kas norāda uz gājienu/soli/slīpuma izvadi |
| GPS | Satelīta bloķēšana un mājas virziens |

## Aparatūra

- WS2812 vai SK6812 RGB gaismas diodes
- Savienojiet ar lidojuma kontroliera **LED** spilventiņu/kontaktu
- Barošanas gaismas diodes no BEC (NEIZMANTOJIET no 3,3 V —, izmantojiet 5 V)
- Garām sloksnēm (>8 gaismas diodes) pievienojiet 5 V strāvu tieši akumulatora spilventiņiem, nevis caur FC

## Ornitoptera lietošana

**Pārdošanas indikators** ir unikāls OrniFlight — gaismas diodēm, kas pulsē sinhroni ar spārnu gājiena frekvenci, sniedzot vizuālu plakstīšanas ritma attēlojumu un palīdzot noregulēt ONDAS ritma parametrus.