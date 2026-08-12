# Perfiles de vuelo

> *4 ranuras de sintonización independientes, conmutables durante el vuelo.*

## Concepto

OrniFlight almacena 4 estructuras `ornithopterProfile_t` completas —, cada una de las cuales contiene los 19 ONDAS y parámetros de dinámica de alas. Un modo BOX (`BOXORNITHOPTERPROFILE`, permanenteId 52) selecciona el perfil activo mediante un interruptor RC de 2 posiciones asignado a 4 ranuras (0–3).

## ¿Por qué perfiles?

Diferentes regímenes de vuelo exigen diferentes ajustes:

| Perfil | Caso de uso | Cadence | Ferocity | Notas |
|---------|----------|---------|----------|-------|
| 0 | **Crucero** | Mediados (50) | Bajo (30) | Vuelo hacia adelante eficiente |
| 1 | **Acrobático** | Bajo (20) | Alto (80) | Autoridad máxima |
| 2 | **Flotar/Merodear** | Alto (70) | Mediados (50) | Estabilidad sobre velocidad |
| 3 | **Deslizamiento** | Mediados (50) | Bajo (10) | Intervención mínima |

## ¿Qué hay en un perfil?

Los 19 campos de `ornithopterProfile_t`:

- **Geometría de deslizamiento**: glide_angle
- **ONDAS v2 (10)**: cadencia, ferocidad_d/p/roll/yaw, equilibrio, deformación, warp_yaw, ancla, resonancia
- **Phase 2 (4)**: presciencia, espelho, saudade, ssff
- **Forma de onda (2)**: ferocity_downstroke, ferocity_upstroke
- **Aeroelástico (2)**: aeroelastic_glide_coficient, aeroelastic_flap_coficient

## Qué es global (no por perfil)

- Canal de frecuencia (un canal RC, funciona tanto en INDEPENDENT como en GLIDE)
- Ángulos de montaje servo
- Cambios de fase de aleteo
- geometría GralhaAzul (servo_speed, max_amplitude, flap_magnitude, wing_origin)

Estas son constantes físicas del fuselaje — y no cambian con el régimen de vuelo.

## Cambio en vuelo

1. Asigne un interruptor de 2 o 3 posiciones a un canal libre
2. En la pestaña Modos del configurador, asigne ese rango a `ORNITHOPTER PROFILE`.
3. Cada posición del interruptor selecciona una de las 4 ranuras
4. El menú desplegable del perfil del Configurador edita la ranura *actualmente seleccionada* a través de MSP

---

*Ver `src/main/flight/ornithopter_profile.h` para la definición de estructura.*