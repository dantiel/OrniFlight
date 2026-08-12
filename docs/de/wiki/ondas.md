# ONDAS — Oszillierende normalisierte dynamische adaptive Stabilisierung

## Das Grundprinzip

Ein Starrflügler oder ein konventionelles Flugzeug erzeugt Steuerkräfte **kontinuierlich** —, eine Steuerflächenauslenkung oder RPM-Änderung erzeugt ein stationäres Moment. Ein Ornithopter tut das nicht. Jedes Gramm Schub, jedes Newton Drehmoment ist innerhalb des Flügelschlagzyklus **phasengebunden**. Der gleiche Kraftimpuls, der an verschiedenen Punkten des Hubs angewendet wird, führt zu grundlegend unterschiedlichen Ergebnissen.

ONDAS erkennt diese Realität an und moduliert die Stabilisierungsbemühungen synchron mit dem Schlagzyklus.

---

## Cadence — Das Timing-Gehirn

Cadence ist der kritischste ONDAS-Filter, da er bestimmt, **wann** die Korrektur innerhalb jedes Flügelschlags erfolgt.

| Schlaganfallphase | Wirkung der Kraftanwendung |
|---|---|
| Abschlagmitte | Maximale Hub- und Rollautorität |
| Abwärtshubende (Bremsen) | Induzierter Widerstand → Giermoment |
| Aufwärtshubzentrum | Nach hinten stoßen, aufrichten |
| Aufwärtshub Ende | Flügelumkehr, minimaler Effekt |

**Cadence verschiebt das Modulationsfenster**, um es an die Phase anzupassen, in der der aerodynamische Hebelarm am längsten ist. Falsche Trittfrequenz = Kampfflügelphysik. Richtige Trittfrequenz = jedes Milliwatt wird zur Kontrollinstanz.

### Parameter

| Parameter | Wert | Funktion |
|-----------|-------|----------|
| `ONDAS_K0` | 1,0 | Basisphasenversatz |
| `ONDAS_K2` | 10,0 | Phasenspreizung / Schärfe |
| `ONDAS_PHASE_SCALE` | 0,00005 | Kleiner Faktor, große Hebelwirkung |

---

## Ferocity P — Sofortiger asymmetrischer Schub

Ferocity P erhöht die **Rechteckigkeit der Wellenform** (Trapezform: Verweildauer bei ±1, Kosinusrampe dazwischen) proportional zum aktuellen PID-Fehler.

- Mehr Schub auf einer Seite → sofort
- Der gebremste Flügel erfährt am Ende des Hubs einen **induzierten Widerstand** —, das ist das Gegenmoment
- Wirkung: direkt, proportional, unmittelbar

---

## Ferocity D — Vorwegnehmende Drag-Ausbeutung

Ferocity D rundet das Bild ab. Wo P für Schubasymmetrie sorgt, nutzt D den **Widerstand des kontralateralen Flügels** als Bremse.

- Liest die Fehleränderungsrate und **antizipiert**
- Kann den Widerstand eines verlangsamten Flügels gezielt für Gier-/Nickmomente ausnutzen
- P+D erzeugen zusammen ein **Differenzmomentpaar** — Schub auf Seite A, Widerstand auf Seite B — effizienter als reiner Schub

---

## Drei Möglichkeiten Cadence/Ferocity D erhöht Ferocity

### 1. Direct — D erhöht P bei schneller Fehleränderung

Bei Böen oder aggressiven Manövern ist `error_rate` groß. D multipliziert dies und erhöht die Basiswildheit. Der Flügel wird *schärfer* (trapezförmiger), weil P+D zusammen mehr Rechtwinkligkeit erfordern als P allein. Ergebnis: maximale Autorität genau dann, wenn es kritisch ist.

### 2. Indirekt — Cadence verschiebt den Hebelpunkt

Cadence moduliert, *wenn* im Zyklus Wildheit wirkt. Das Verschieben des Fensters in eine aerodynamisch empfindlichere Phase (z. B. Abwärtshub-Mitte vs. Aufwärtshub-Ende) bedeutet, dass der **gleiche Wildheitswert** mehr Effekt — effektive Verstärkung ohne numerische Änderung erzeugt.

### 3. Kombinatorisches — D × Cadence während der Stall-Erholung

Im Stall: hohe Sinkrate → D erkennt die Geschwindigkeit → erhöht die Wildheit. Gleichzeitig verschiebt die Trittfrequenz die Modulation in die Abschlagphase, in der der Flügel den maximalen Biss hat. Das Zusammenspiel: D sorgt für die Kraft, Kadenz für den richtigen Moment. Ohne Trittfrequenz erreicht die D-Kraft die falsche Phase und verflüchtigt sich nutzlos.

---

## Zusätzliche ONDAS-Parameter

| Parameter | Funktion |
|-----------|----------|
| **Balance** | Auf-/Ab-Schubsymmetrie — I-Term-Vorspannung zwischen Auf- und Abschlag. Kompensiert Flügelasymmetrie, Fertigungstoleranzen und Verschleiß |
| **Warp** | Roll-/Gier-P → L/R-Wildheitsdifferenzial — rechter und linker Flügel schlagen unabhängig voneinander auf der Rollachse für Quer- und Wendemanöver |
| **Anchor** | Die Phasenverankerung — sperrt die Modulation an eine bestimmte Phasenreferenz und verhindert Drift |
| **Resonance** | Die Resonanzkompensation der Flugzeugzelle — vermeidet aufregende Strukturmoden der Flugzeugzelle |

---

## Analogie

**Cadence ist der Dirigent. Ferocity P und D sind die Instrumente.**

Ohne Dirigenten spielen sie —, aber nicht zusammen. Mit einem wird Lärm zur Musik.

---

## Siehe auch

- [ONDAS Tuning Guide](../../tutorials/ondas_tuning.html) — praktisches Tuning-Verfahren
- [MSP-Protokoll](msp.html) —-Drahtformat für ONDAS-Parameter
- [Flugprofile](profiles.html) — profilbewusste ONDAS-Konfiguration