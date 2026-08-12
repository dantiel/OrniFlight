# Flugmodi

Die Modi werden über die Schalter AUX an Ihrem Sender umgeschaltet. Jeder Modus kann auf der Registerkarte **Modi** des OrniFlight-Konfigurators einem bestimmten AUX-Kanalbereich zugewiesen werden.

## Standardmodi

| Modus | Funktion |
|------|----------|
| **ARM** | Flugsteuerung aktivieren (Motoren/Servos aktiv) |
| **ANGLE** | Automatische Nivellierung — Das Fahrzeug kehrt zur Nivellierung zurück, wenn die Stöcke zentriert sind |
| **HORIZON** | Hybrid — Winkelmodus nahe der Mitte, Acro bei vollem Steuerknüppel |
| **ACRO** | Standardmäßig — kein Auto-Level, reine Geschwindigkeitskontrolle |
| **AIRMODE** | Hält die PID-Schleife bei null Drosselung für volle Autorität aktiv |

## OrniFlight-spezifische Modi

| ID | Modus | Funktion |
|----|------|----------|
| 50 | **INDEPENDENT** | Unabhängige Flügelsteuerung — Jeder Flügel reagiert auf seinen eigenen Servokanal |
| 51 | **GLIDE** | Gleitmodus — Flügel zum Segelfliegen in horizontaler Position verriegelt |
| 52 | **PROFILE** | Flugprofilauswahl — Wechsel zwischen 3 PID/ONDAS-Profilen |

## Utility-Modi

| Modus | Funktion |
|------|----------|
| **BEEPER** | Aktivieren Sie den Summer, um verlorene Flugzeuge zu lokalisieren |
| **BLACKBOX** | Blackbox-Protokollierung starten/stoppen |
| **FAILSAFE** | Failsafe Stufe 2 (Panikschalter) manuell auslösen |
| **OSD** | OSD-Anzeige umschalten |
| **TELEMETRY** | Telemetrieausgabe aktivieren/deaktivieren |

## Ornithopter-Notizen

- Der **INDEPENDENT**-Modus ist einzigartig für OrniFlight —. Er ermöglicht die Servozuordnung pro Flügel für asymmetrischen Schub und differenzielle Flügelsteuerung
- Der **GLIDE**-Modus hält die Flügel in neutraler Position, nützlich für thermisches Segelfliegen und energieeffizienten Sinkflug
- **PROFILE**-Umschaltung ermöglicht ONDAS-Parameteränderungen während des Fluges für unterschiedliche Flugbedingungen (z. B. Reiseflug oder aggressives Manövrieren).