# Flyglägen

Lägen växlas via AUX-omkopplare på din sändare. Varje läge kan tilldelas ett specifikt AUX-kanalområde på fliken **Modes** i OrniFlight Configurator.

## Standardlägen

| Läge | Funktion |
|------|--------|
| **ARM** | Aktivera flygkontroll (motorer/servon aktiva) |
| **ANGLE** | Auto-level — farkoster återgår till nivå när pinnar centreras |
| **HORIZON** | Hybrid — vinkelläge nära mitten, acro på full stick |
| **ACRO** | Standard — ingen autonivå, ren hastighetskontroll |
| **AIRMODE** | Håller PID loop aktiv vid noll gas för full auktoritet |

## OrniFlight-specifika lägen

| ID | Läge | Funktion |
|----|------|---------|
| 50 | **INDEPENDENT** | Oberoende vingkontroll — varje vinge svarar på sin egen servokanal |
| 51 | **GLIDE** | Glidläge — vingar låsta i horisontellt läge för svävande |
| 52 | **PROFILE** | Val av flygprofil — växla mellan 3 PID/ONDAS-profiler |

## Verktygslägen

| Läge | Funktion |
|------|----------------|
| **BEEPER** | Aktivera summer för att lokalisera förlorat flygplan |
| **BLACKBOX** | Starta/stoppa Blackbox-loggning |
| **FAILSAFE** | Trigga felsäkert steg 2 manuellt (panikbrytare) |
| **OSD** | Växla OSD-skärm |
| **TELEMETRY** | Aktivera/inaktivera telemetriutgång |

## Ornithopter Notes

- **INDEPENDENT**-läget är unikt för OrniFlight — det möjliggör servomappning per ving för asymmetrisk dragkraft och differentiell vingkontroll
- **GLIDE**-läget håller vingarna i neutralt läge, användbart för termisk svävning och energieffektiv nedstigning
- **PROFILE**-växling tillåter ONDAS-parameterändringar under flygning för varierande flygförhållanden (t.ex. kryssning kontra aggressiv manövrering)