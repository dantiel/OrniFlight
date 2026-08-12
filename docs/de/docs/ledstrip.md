# LED Strip

OrniFlight unterstützt adressierbare Streifen WS2812/SK6812 LED für Statusanzeige und visuelles Feedback.

## Konfiguration

LED-Streifen werden auf der Registerkarte **LED Strip** des OrniFlight-Konfigurators konfiguriert. Jede LED-Position, Farbe und Funktion kann individuell eingestellt werden.

## Funktionen

| Funktion | Visueller Effekt |
|----------|--------------|
| Batterieanzeige | Farbverlauf von Grün → Gelb → Rot |
| RSSI | Signalstärkeanzeige |
| Waffenstaat | Farbwechsel beim Aktivieren/Deaktivieren |
| Flugmodus | Modusspezifische Farben |
| Warnung | Blinkmuster bei schwacher Batterie, ausfallsicher |
| Schlaganzeige | Puls bei aktueller Schlagfrequenz |
| Schubrichtung | Farbverschiebung, die die Roll-/Nick-/Gier-Ausgabe anzeigt |
| GPS | Satellitensperre und Heimrichtung |

## Hardware

- LEDs WS2812 oder SK6812 RGB
- Verbinden Sie sich mit dem **LED** Pad/Pin Ihres Flugcontrollers
- Power-LEDs von einem BEC (KEINE Stromversorgung über 3,3 V, — verwenden Sie 5 V)
- Schließen Sie bei langen Streifen (>8 LEDs) die 5-V-Stromversorgung direkt an die Batteriekontakte an, nicht über FC

## Ornithopter-Einsatz

Die **Flatteranzeige** gibt es nur bei OrniFlight, —. Die LEDs pulsieren synchron mit der Schlagfrequenz des Flügels, geben eine visuelle Darstellung des Schlagrhythmus und helfen bei der Abstimmung der Trittfrequenzparameter von ONDAS.