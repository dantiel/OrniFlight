# LED Strip

OrniFlight podržava adresabilne WS2812/SK6812 LED trake za indikaciju statusa i vizualnu povratnu informaciju.

## Konfiguracija

LED trake konfiguriraju se u kartici **LED Strip** u OrniFlight konfiguratoru. Svaki LED položaj, boja i funkcija mogu se postaviti zasebno.

## Funkcije

| Funkcija | Vizualni efekt |
|----------|--------------|
| Indikator baterije | Gradijent boje od zelene → žute → crvene |
| RSSI | Prikaz jačine signala |
| Oružana država | Promjena boje pri aktiviranju/deaktiviranju |
| Način letenja | Boje specifične za način |
| Upozorenje | Obrasci treptanja za slabu bateriju, sigurno |
| Lelujajući indikator | Puls na trenutnoj frekvenciji treptanja |
| Smjer potiska | Pomak u boji koji pokazuje izlaz zakretanja/nagiba/skretanja |
| GPS | Satelitska brava i smjer kući |

## Hardver

- LED diode WS2812 ili SK6812 RGB
- Spojite se na **LED** podlogu/pin na svom kontroleru leta
- LED diode napajanja iz BEC (NE napajajte se od 3,3 V — koristite 5 V)
- Za duge trake (>8 LED dioda), spojite 5V napajanje izravno na baterije, a ne kroz FC

## Korištenje ornitoptera

**Indikator mlataranja** je jedinstven za OrniFlight — LED diode koje pulsiraju sinkronizirano s frekvencijom zamaha krilima, dajući vizualni prikaz ritma mlataranja i pomažući ugađanju parametara kadence ONDAS.