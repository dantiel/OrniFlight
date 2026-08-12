# Profili leta

> *4 neovisna utora za ugađanje, promjenjiva tijekom leta.*

## Koncept

OrniFlight pohranjuje 4 kompletne `ornithopterProfile_t` strukture — od kojih svaka sadrži svih 19 ONDAS i parametara dinamike krila. Način rada BOX (`BOXORNITHOPTERPROFILE`, permanentId 52) odabire aktivni profil preko prekidača RC s 2 položaja mapiranog na 4 utora (0–3).

## Zašto Profili?

Različiti režimi leta zahtijevaju različito podešavanje:

| Profil | Slučaj upotrebe | Cadence | Ferocity | Bilješke |
|---------|----------|---------|----------|-------|
| 0 | **Krstarenje** | Sredina (50) | Nisko (30) | Učinkovit let naprijed |
| 1 | **Akrobatski** | Nisko (20) | Visoko (80) | Najveća ovlast |
| 2 | **Lebdjenje/lebljenje** | Visoko (70) | Sredina (50) | Stabilnost u odnosu na brzinu |
| 3 | **Klizi** | Sredina (50) | Nisko (10) | Minimalna intervencija |

## Što je u profilu

Svih 19 polja `ornithopterProfile_t`:

- **Glide geometrija**: glide_angle
- **ONDAS v2 (10)**: kadenca, žestina_d/p/roll/yaw, ravnoteža, warp, warp_yaw, sidro, rezonancija
- **Phase 2 (4)**: predviđanje, espelho, saudade, ssff
- **Valni oblik (2)**: ferocity_downstroke, ferocity_upstroke
- **Aeroelastic (2)**: aeroelastic_glide_coefficient, aeroelastic_flap_coefficient

## Što je globalno (ne po profilu)

- Frekvencijski kanal (jedan RC kanal, radi i u INDEPENDENT i u GLIDE)
- Servo kutovi za montažu
- Laptajući fazni pomaci
- GralhaAzul geometrija (servo_brzina, max_amplituda, flap_magnitude, wing_origin)

Ovo su fizičke konstante konstrukcije zrakoplova — koje se ne mijenjaju s režimom leta.

## Prebacivanje tijekom leta

1. Dodijelite prekidač s 2 ili 3 položaja rezervnom kanalu
2. U kartici Modovi konfiguratora, preslikajte taj raspon na `ORNITHOPTER PROFILE`
3. Svaki položaj prekidača odabire jedan od 4 utora
4. Padajući izbornik profila konfiguratora uređuje *trenutno odabrani* utor putem MSP

---

*Pogledajte `src/main/flight/ornithopter_profile.h` za definiciju strukture.*