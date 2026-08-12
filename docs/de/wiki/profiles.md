# Flugprofile

> *4 unabhängige Tuning-Slots, während des Fluges umschaltbar.*

## Konzept

OrniFlight speichert 4 vollständige `ornithopterProfile_t`-Strukturen —, von denen jede alle 19 ONDAS- und Wing-Dynamics-Parameter enthält. Ein BOX-Modus (`BOXORNITHOPTERPROFILE`, permanentId 52) wählt das aktive Profil über einen 2-Positionen-RC-Schalter aus, der 4 Steckplätzen (0–3) zugeordnet ist.

## Warum Profile?

Unterschiedliche Flugregime erfordern unterschiedliche Abstimmungen:

| Profil | Anwendungsfall | Cadence | Ferocity | Notizen |
|---------|----------|---------|----------|-------|
| 0 | **Kreuzfahrt** | Mitte (50) | Niedrig (30) | Effizienter Vorwärtsflug |
| 1 | **Kunstflug** | Niedrig (20) | Hoch (80) | Maximale Autorität |
| 2 | **Schweben/Herumlungern** | Hoch (70) | Mitte (50) | Stabilität vor Geschwindigkeit |
| 3 | **Gleiten** | Mitte (50) | Niedrig (10) | Minimaler Eingriff |

## Was ist in einem Profil?

Alle 19 Felder von `ornithopterProfile_t`:

- **Gleitgeometrie**: glide_angle
- **ONDAS v2 (10)**: Trittfrequenz, Ferocity_d/p/roll/yaw, Balance, Warp, Warp_yaw, Anker, Resonanz
- **Phase 2 (4)**: Prescience, Espelho, Saudade, SSFF
- **Wellenform (2)**: ferocity_downStroke, Ferocity_UpStroke
- **Aeroelastic (2)**: aeroelastic_glide_coefficient, aeroelastic_flap_coefficient

## Was ist global (nicht pro Profil)

- Frequenzkanal (ein RC-Kanal, funktioniert sowohl in INDEPENDENT als auch in GLIDE)
- Servo-Montagewinkel
- Flatternde Phasenverschiebungen
- GralhaAzul-Geometrie (servo_speed, max_amplitude, Flap_magnitude, Wing_origin)

Dies sind physikalische Konstanten der Flugzeugzelle —, sie ändern sich nicht mit dem Flugregime.

## Wechsel im Flug

1. Weisen Sie einem Ersatzkanal einen Schalter mit 2 oder 3 Positionen zu
2. Ordnen Sie auf der Registerkarte „Konfiguratormodi“ diesen Bereich `ORNITHOPTER PROFILE` zu
3. Jede Schalterposition wählt einen der 4 Steckplätze aus
4. Das Profil-Dropdown-Menü des Konfigurators bearbeitet den *aktuell ausgewählten* Slot über MSP

---

*Siehe `src/main/flight/ornithopter_profile.h` für die Strukturdefinition.*