# Controls

OrniFlight verwendet die standardmäßige RC-Stick-Zuordnung mit Ornithopter-spezifischen Erweiterungen.

## Stick Mapping

| Stick | Axis | Primäreffekt |
|-------|------|---------------|
| Gashebel (links, vertikal) | Gas | Schlagamplitude / Schub |
| Yaw (Left, horizontal) | Yaw | Differentialflügelschub zum Drehen |
| Pitch (rechts, vertikal) | Pitch | Vorwärts-/Rückwärtsneigung |
| Rollen (rechts, horizontal) | Roll | Left/right banking |

## Flugmodi

| Modus | Stick Behavior |
|------|---------------|
| **ACRO** | Steuerknüppel steuern die Winkelgeschwindigkeit — kein automatisches Niveau |
| **ANGLE** | Steuerknüppel steuern den Winkel — automatisch, wenn sie losgelassen werden |
| **HORIZON** | ANGLE nahe der Mitte, ACRO bei voller Auslenkung |

ACRO wird erfahrenen Piloten empfohlen. ANGLE eignet sich gut für Erstflüge und Thermiksegelflüge.

## Ornithopter-spezifische Kontrollen

### INDEPENDENT Mode

Wenn der INDEPENDENT-Modus aktiv ist, reagiert jedes Flügelservo unabhängig:
- **Linker Stick** → linke Flügelservos
- **Rechter Stick** → rechte Flügelservos
- Ermöglicht asymmetrisches Schlagen für aggressive Manöver

### GLIDE Mode

Der Modus GLIDE verriegelt beide Flügel in horizontaler Position. Der Ornithopter wird zum Segelflugzeug:
- **Gashebel** hat keinen Einfluss auf die Flügelposition
- **Pitch/Roll/Yaw** beeinflusst weiterhin die Hecksteuerflächen (falls vorhanden)

### Profilwechsel

Die Profilumschaltung während des Fluges über den AUX-Kanal ermöglicht die Änderung der PID/ONDAS-Parameter während des Fluges:
- **Profil 1**: Standard-Kreuzfahrteinstellungen
- **Profil 2**: Einstellungen für hohe Agilität
- **Profil 3**: Effizienz-/Gleiteinstellungen

## Preise

Konfigurieren Sie die Tarife auf der Registerkarte **PID Tuning**. Beginnen Sie für Ornithopter mit konservativen Raten. Die Schlagdynamik verstärkt die Steuereingaben:
- RC Rate: 0,80–1,00
- Superrate: 0,60–0,70
- Expo: 0,20–0,40