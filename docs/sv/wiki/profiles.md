# Flygprofiler

> *4 oberoende inställningsplatser, omkopplingsbar under flygning.*

## Koncept

OrniFlight lagrar 4 kompletta `ornithopterProfile_t`-strukturer — som var och en innehåller alla 19 ONDAS och vingdynamikparametrar. Ett BOX-läge (`BOXORNITHOPTERPROFILE`, permanentId 52) väljer den aktiva profilen via en 2-positions RC-omkopplare mappad till 4 platser (0–3).

## Varför profiler?

Olika flygregimer kräver olika inställning:

| Profil | Användningsfall | Cadence | Ferocity | Anteckningar |
|--------|--------|--------|--------|-------|
| 0 | **Cruising** | Mitt (50) | Låg (30) | Effektiv flygning framåt |
| 1 | **Aerobatic** | Låg (20) | Hög (80) | Maximal behörighet |
| 2 | **Hover/Loiter** | Hög (70) | Mitt (50) | Stabilitet över hastighet |
| 3 | **Glid** | Mitt (50) | Låg (10) | Minimalt ingripande |

## Vad finns i en profil

Alla 19 fält av `ornithopterProfile_t`:

- **Glidgeometri**: glidvinkel
- **ONDAS v2 (10)**: kadens, vildhet_d/p/roll/yaw, balans, warp, warp_yaw, ankare, resonans
- **Phase 2 (4)**: förutseende, espelho, saudade, ssff
- **Vågform (2)**: vildhet_nedåt, vildhet_uppåt
- **Aeroelastic (2)**: aeroelastic_glide_coefficient, aeroelastic_flap_coefficient

## Vad är globalt (inte per profil)

- Frekvenskanal (en RC-kanal, fungerar i både INDEPENDENT och GLIDE)
- Servomonteringsvinklar
- Klaffande fasförskjutningar
- GralhaAzul geometri (servo_speed, max_amplitude, flap_magnitude, wing_origin)

Dessa är fysiska konstanter för flygplanet — de ändras inte med flygregimen.

## Byter under flygning

1. Tilldela en 2-läges- eller 3-lägesbrytare till en reservkanal
2. På fliken Konfiguratorlägen mappar du det intervallet till `ORNITHOPTER PROFILE`
3. Varje omkopplarläge väljer en av de 4 kortplatserna
4. Konfiguratorns profilrullgardinsmeny redigerar den *för närvarande valda* luckan via MSP

---

*Se `src/main/flight/ornithopter_profile.h` för strukturdefinitionen.*