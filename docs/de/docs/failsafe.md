# Ausfallsicher

OrniFlight verfügt über ein zweistufiges Ausfallsicherungssystem, um Ihren Ornithopter im Falle eines Empfängersignalverlusts zu schützen.

## Zweistufiges System

### Stufe 1 — Signalverlust erkannt

Wird ausgelöst, wenn:
- Jeder Flugkanal hat eine ungültige Impulslänge
- Empfänger meldet Failsafe-Modus
- Für eine konfigurierte Dauer kein Signal vom Empfänger

**Aktion**: Alle Kanäle wechseln auf Fallback-Werte (konfiguriert über `rxfail`). Ein kurzes Erholungsfenster beginnt —, wenn das Signal zurückkehrt, wird der normale Flug fortgesetzt.

### Stufe 2 — Schutzzeit abgelaufen

Wird eingegeben, wenn Stufe 1 länger als `failsafe_delay` (Standard: 400 ms) andauert UND das Fahrzeug scharfgeschaltet ist.

**Prozeduren** (konfigurierbar über `failsafe_procedure`):

| Vorgehensweise | Verhalten |
|-----------|----------|
| **DROP** | Sofort entwaffnen — Flügel stoppen, Flugzeug sinkt |
| **LAND** | Gleitmodus — Flügel horizontal verriegelt, kontrollierter Sinkflug |

**LAND** ist das empfohlene Verfahren für Ornithopter. — Es hält die Flügel für einen gleitenden Abstieg in einer neutralen Position und gibt so Zeit für die Signalwiederherstellung.

## CLI Einstellungen

```
set failsafe_delay = 4         # Guard time in 0.1s (4 = 400ms)
set failsafe_procedure = LAND  # DROP or LAND
set failsafe_throttle = 1000   # Fallback throttle (low)
set failsafe_switch_mode = STAGE1  # Transmitter switch behavior
```

## Empfänger ausfallsicher

Konfigurieren Sie außerdem die Ausfallsicherung Ihres Empfängers so, dass bei Signalverlust **keine Impulse** ausgegeben werden. Dadurch kann der Fluglotse den Verlust erkennen und Stufe 1 aktivieren.

## Testen

Failsafe-Test **bei getrennter Flügelanlenkung** auf dem Prüfstand:
1. Weisen Sie einem Schalter den FAILSAFE-Modus zu
2. Bewaffnen Sie das Fahrzeug
3. Stellen Sie den Schalter → um und beachten Sie die Failsafe-Prozedur
4. Überprüfen Sie, ob das Servoverhalten den Erwartungen entspricht