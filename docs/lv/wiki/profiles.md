# Lidojuma profili

> *4 neatkarīgi noregulēšanas sloti, pārslēdzami lidojuma laikā.*

## Koncepcija

OrniFlight uzglabā 4 pilnīgas `ornithopterProfile_t` struktūras —, katra satur visus 19 ONDAS un spārnu dinamikas parametrus. Režīms BOX (`BOXORNITHOPTERPROFILE`, permanentId 52) atlasa aktīvo profilu, izmantojot 2 pozīciju RC slēdzi, kas piesaistīts 4 slotiem (0–3).

## Kāpēc profili?

Dažādiem lidojumu režīmiem ir nepieciešama atšķirīga regulēšana:

| Profils | Lietošanas gadījums | Cadence | Ferocity | Piezīmes |
|---------|----------|---------|-----------|--------|
| 0 | **Kruīzs** | Vidēja (50) | Zems (30) | Efektīvs lidojums uz priekšu |
| 1 | **Aerobatic** | Zems (20) | Augsts (80) | Maksimālā pilnvara |
| 2 | **Hover/Loiter** | Augsts (70) | Vidēja (50) | Stabilitāte pār ātrumu |
| 3 | **Glide** | Vidēja (50) | Zems (10) | Minimāla iejaukšanās |

## Kas atrodas profilā

Visi 19 `ornithopterProfile_t` lauki:

- **Slīdēšanas ģeometrija**: slīdēšanas_leņķis
- **ONDAS v2 (10)**: ritms, niknums_d/p/roll/yaw, līdzsvars, deformācija, deformācijas_virze, enkurs, rezonanse
- **Phase 2 (4)**: zināšanās, espelho, saudade, ssff
- **Viļņa forma (2)**: mežonība_uz leju, mežonība_augšup
- **Aeroelastība (2)**: aeroelastības_slīdēšanas_koeficients, aeroelastības_atloka_koeficients

## Kas ir globāls (nevis profilam)

- Frekvences kanāls (viens RC kanāls, darbojas gan INDEPENDENT, gan GLIDE)
- Servo stiprinājuma leņķi
- Fāžu nobīdes
- GralhaAzul ģeometrija (servo_speed, max_amplitude, flap_magnitude, wing_origin)

Tās ir lidmašīnas korpusa fiziskās konstantes —, tās nemainās atkarībā no lidojuma režīma.

## Pārslēgšanās lidojuma laikā

1. Rezerves kanālam piešķiriet 2 vai 3 pozīciju slēdzi
2. Cilnē Konfiguratora režīmi kartējiet šo diapazonu uz `ORNITHOPTER PROFILE`
3. Katra slēdža pozīcija izvēlas vienu no 4 slotiem
4. Konfiguratora profila nolaižamā izvēlne rediģē *pašlaik atlasīto* slotu, izmantojot MSP

---

*Struktūras definīciju skatiet sadaļā `src/main/flight/ornithopter_profile.h`.*