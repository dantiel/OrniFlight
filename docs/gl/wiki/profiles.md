# Perfís de voo

> *4 ranuras de sintonización independentes, conmutables durante o voo.*

## Concepto

OrniFlight almacena 4 estruturas `ornithopterProfile_t` completas —, cada unha contén os 19 parámetros de ONDAS e de dinámica das ás. Un modo BOX (`BOXORNITHOPTERPROFILE`, permanentId 52) selecciona o perfil activo mediante un interruptor RC de 2 posicións asignado a 4 slots (0–3).

## Por que Perfís?

Os diferentes réximes de voo requiren diferentes axustes:

| Perfil | Caso de uso | Cadence | Ferocity | Notas |
|---------|----------|----------|----------|-------|
| 0 | **Cruceiro** | Medio (50) | Baixo (30) | Voo cara adiante eficiente |
| 1 | **Acrobático** | Baixo (20) | Alto (80) | Máxima autoridade |
| 2 | **Hover/Loiter** | Alto (70) | Medio (50) | Estabilidade sobre a velocidade |
| 3 | **Deslizar** | Medio (50) | Baixo (10) | Mínima intervención |

## Que hai nun perfil

Os 19 campos de `ornithopterProfile_t`:

- **Xometría de deslizamento**: ángulo_deslizamento
- **ONDAS v2 (10)**: cadencia, ferocidade_d/p/roll/yaw, balance, warp, warp_yaw, áncora, resonancia
- **Phase 2 (4)**: prescience, espelho, saudade, ssff
- **Forma de onda (2)**: ferocity_downstroke, ferocity_downstroke
- **Aeroelástico (2)**: coeficiente_de_deslizamento_aeroelástico, coeficiente_de_flap_aeroelástico

## Que é global (non por perfil)

- Canle de frecuencia (unha canle RC, funciona tanto en INDEPENDENT como en GLIDE)
- Ángulos de montaxe dos servos
- Cambios de fase de aleteo
- xeometría GralhaAzul (servo_speed, max_amplitude, flap_magnitude, wing_origin)

Estas son constantes físicas do fuselaje — que non cambian co réxime de voo.

## Cambio en voo

1. Asigne un interruptor de 2 ou 3 posicións a unha canle de reserva
2. Na pestana Modos do configurador, asigne ese intervalo a `ORNITHOPTER PROFILE`
3. Cada posición do interruptor selecciona unha das 4 ranuras
4. O menú despregable do perfil do configurador edita o slot *seleccionado actualmente* mediante MSP

---

*Consulte `src/main/flight/ornithopter_profile.h` para a definición da estrutura.*