# Perfils de vol

> *4 ranures de sintonització independents, commutables durant el vol.*

## Concepte

OrniFlight emmagatzema 4 estructures `ornithopterProfile_t` completes — cadascuna amb els 19 paràmetres de ONDAS i dinàmica de les ales. Un mode BOX (`BOXORNITHOPTERPROFILE`, permanentId 52) selecciona el perfil actiu mitjançant un interruptor RC de 2 posicions assignat a 4 ranures (0–3).

## Per què perfils?

Els diferents règims de vol exigeixen diferents ajustaments:

| Perfil | Cas d'ús | Cadence | Ferocity | Notes |
|---------|----------|----------|-----------|-------|
| 0 | ** Creuer** | Mitjana (50) | Baix (30) | Vol endavant eficient |
| 1 | **Acrobacia** | Baixa (20) | Alt (80) | Màxima autoritat |
| 2 | **Hover/Loiter** | Alt (70) | Mitjana (50) | Estabilitat sobre velocitat |
| 3 | **Llisca** | Mitjana (50) | Baix (10) | Mínima intervenció |

## Què hi ha en un perfil

Els 19 camps de `ornithopterProfile_t`:

- **Geometria de lliscament**: angle_planament
- **ONDAS v2 (10)**: cadència, ferocitat_d/p/roll/yaw, equilibri, warp, warp_yaw, àncora, ressonància
- **Phase 2 (4)**: presciència, espell, saudade, ssff
- **Forma d'ona (2)**: ferocitat_avall, ferocitat_amunt
- **Aeroelàstic (2)**: coeficient_aeroelàstic_de_lliscament, coeficient_aeroelàstic_flap

## Què és global (no per perfil)

- Canal de freqüència (un canal RC, funciona tant en INDEPENDENT com en GLIDE)
- Angles de muntatge del servo
- Canvis de fase amb aleteig
- Geometria GralhaAzul (servo_speed, max_amplitude, flap_magnitude, wing_origin)

Aquestes són constants físiques de la cèl·lula — que no canvien amb el règim de vol.

## Canvi en vol

1. Assigna un interruptor de 2 o 3 posicions a un canal de recanvi
2. A la pestanya Modes del configurador, assigneu aquest interval a `ORNITHOPTER PROFILE`
3. Cada posició de l'interruptor selecciona una de les 4 ranures
4. El menú desplegable del perfil del configurador edita l'espai *actualment seleccionat* mitjançant MSP

---

*Vegeu `src/main/flight/ornithopter_profile.h` per a la definició de l'estructura.*