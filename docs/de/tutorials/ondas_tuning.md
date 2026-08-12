# ONDAS Tuning-Anleitung

> *Der praktische Begleiter zur ONDAS-Theorie —, wie man jeden Parameter nach Gefühl abstimmt.*

## Tuning-Reihenfolge

ONDAS-Parameter sind voneinander abhängig. Stimmen Sie sie in dieser Reihenfolge ab:

```
1. Cadence    →  timing
2. Ferocity D →  primary stabilization
3. Ferocity P →  response crispness
4. Balance    →  upstroke/downstroke bias
5. Warp       →  modulation width
6. Anchor     →  dry/wet mix
7. Resonance  →  cycle-to-cycle memory
8. Phase 2    →  advanced (prescience, espelho, saudade, SSFF)
```

## Schritt für Schritt

### 1. Cadence — Finden Sie Ihr Phasenfenster

**Ziel**: Platzieren Sie die Modulation dort, wo Ihr Flügel den meisten Biss hat.

**Methode**: 
- Beginnen Sie mit 50
- Erhöhung auf 70 — Wird die Rollreaktion schwächer?
- Auf 30 verringern — Wird die Rollreaktion stärker?
- Der „stärkste“ Punkt ist der Punkt, an dem die Schlagkraft Ihres Flügels ihren Höhepunkt erreicht

**Anzeichen für zu hohe Werte**: Breiige Reaktion, das Handwerk fühlt sich „verzögert“ an
**Anzeichen für zu niedrigen Wert**: Ruckartige Reaktion, Überschwingen beim Rollen

### 2. Ferocity D — Stabilisieren Sie das Handwerk

**Ziel**: Primärstabilisierung ohne Schwingungen.

**Methode**:
- Beginnen Sie mit 20
- Schwebeflug oder gleichmäßiger Vorwärtsflug
- Erhöhen Sie die Geschwindigkeit, bis das Fahrzeug „steifer“ wird.
- Ziehen Sie 5 Punkte von der Stelle zurück, an der Sie die Schwingung zum ersten Mal bemerken

**Anzeichen für zu hohe Werte**: Feine Vibration, motorisches Summen in den Servos
**Anzeichen für zu niedrigen Wert**: Fahrzeug driftet, fühlt sich locker an

### 3. Ferocity P — Knusprigkeit

**Ziel**: Reaktionsfreudig, aber nicht nervös.

**Methode**:
- Beginnen Sie um 15
- Stoßen Sie den Rollstock — an, beißt das Fahrzeug sofort?
- Erhöhen Sie den Wert, bis der Knüppel deutlich reagiert
- Ziehen Sie zurück, wenn Sie eine Überschreitung feststellen

**Anzeichen für zu hohe Lautstärke**: Klingeln nach Knüppeleingabe, Rückprall
**Anzeichen für zu niedrig**: Breiige, verzögerte Reaktion

### 4. Balance — Asymmetrie-Tuning

**Ziel**: Gleiche Autorität in beide Richtungen.

**Methode**:
- Fliegen Sie gerade und gerade
- Nach links rollen, Reaktionsgeschwindigkeit beachten
- Nach rechts rollen, Reaktionsgeschwindigkeit beachten
- Passen Sie die Balance an, um sie auszugleichen

### 5–7. Warp, Anchor, Resonance

Feinabstimmung der Parameter. Erst anpassen, wenn 1–4 fest sind.

| Param | Start | Anpassen, wann |
|-------|-------|-------------|
| Warp | 50 | Die Modulation fühlt sich zu weitläufig oder zu spitz an |
| Anchor | 70 | Möchten Sie mehr/weniger rohes PID gemischt |
| Resonance | 30 | Der Schwebeflug ist instabil oder der Vorwärtsflug fühlt sich klingelnd an |

### 8. Phase 2 — Erweitert

| Param | Wirkung |
|-------|--------|
| Prescience | Timing-Vorlauf — höher = Modulation eilt der Phase mehr voraus |
| Espelho | Differenzialkupplung — engere Rolle, kann Effizienz verringern |
| Saudade | Strichspeicher — flüssiger, aber weniger reaktionsschnell |
| SSFF | Direkte Gyro→wave-Einspritzung — ab 10 |

---

*Das Ziel ist ein Fahrzeug, das so fliegt, als ob es in der Luft sein möchte. Wenn Sie dagegen ankämpfen, gehen Sie zurück und stimmen Sie von Cadence aufwärts ab.*