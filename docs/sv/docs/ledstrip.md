# LED Strip

OrniFlight stöder adresserbara WS2812/SK6812 LED-remsor för statusindikering och visuell feedback.

## Konfiguration

LED-remsor konfigureras på fliken **LED Strip** i OrniFlight Configurator. Varje LED position, färg och funktion kan ställas in individuellt.

## Funktioner

| Funktion | Visuell effekt |
|--------|-------------|
| Batteriindikator | Färggradient från grön → gul → röd |
| RSSI | Visning av signalstyrka |
| Arm State | Färgbyte vid armering/avaktivering |
| Flygläge | Lägesspecifika färger |
| Varning | Blinkmönster för lågt batteri, felsäkert |
| Flappande indikator | Puls vid aktuell flaxande frekvens |
| Dragriktning | Färgskiftning som indikerar rullning/stigning/giring |
| GPS | Satellitlås och hemriktning |

## Hårdvara

- WS2812 eller SK6812 RGB lysdioder
- Anslut till **LED** pad/stift på din flygkontroll
- Strömlysdioder från en BEC (strömförsörj INTE från 3,3V — använder 5V)
- För långa remsor (>8 lysdioder), anslut 5V ström direkt till batterikuddar, inte genom FC

## Ornithopter användning

**Flappande indikator** är unik för OrniFlight — LEDs pulserar i synk med vingslagsfrekvensen, vilket ger en visuell representation av flaxande rytm och hjälper till att ställa in ONDAS kadensparametrar.