# Perfis de voo

> *4 slots de ajuste independentes, comutáveis durante o vôo.*

## Conceito

OrniFlight armazena 4 estruturas `ornithopterProfile_t` completas —, cada uma contendo todos os 19 ONDAS e parâmetros de dinâmica de asa. Um modo BOX (`BOXORNITHOPTERPROFILE`, permanenteId 52) seleciona o perfil ativo por meio de um switch RC de 2 posições mapeado para 4 slots (0–3).

## Por que perfis?

Diferentes regimes de voo exigem ajustes diferentes:

| Perfil | Caso de uso | Cadence | Ferocity | Notas |
|--------|----------|---------|----------|-------|
| 0 | **Cruzeiro** | Meados (50) | Baixo (30) | Voo direto eficiente |
| 1 | **Acrobático** | Baixo (20) | Alto (80) | Autoridade máxima |
| 2 | **Passar o mouse/vadiar** | Alto (70) | Meados (50) | Estabilidade em relação à velocidade |
| 3 | **Deslizar** | Meados (50) | Baixo (10) | Intervenção mínima |

## O que há em um perfil

Todos os 19 campos do `ornithopterProfile_t`:

- **Geometria de deslizamento**: glide_angle
- **ONDAS v2 (10)**: cadência, ferocity_d/p/roll/yaw, equilíbrio, warp, warp_yaw, âncora, ressonância
- **Phase 2 (4)**: presciência, espelho, saudade, ssff
- **Forma de onda (2)**: ferocity_downstroke, ferocity_upstroke
- **Aeroelástico (2)**: aeroelastic_glide_coefficient, aeroelastic_flap_coefficient

## O que é global (não por perfil)

- Canal de frequência (um canal RC, funciona tanto em INDEPENDENT quanto em GLIDE)
- Ângulos de montagem servo
- Mudanças de fase oscilantes
- geometria GralhaAzul (servo_speed, max_amplitude, flap_magnitude, wing_origin)

Estas são constantes físicas da fuselagem — e não mudam com o regime de voo.

## Mudança em vôo

1. Atribua uma chave de 2 ou 3 posições a um canal sobressalente
2. Na guia Modos do configurador, mapeie esse intervalo para `ORNITHOPTER PROFILE`
3. Cada posição da chave seleciona um dos 4 slots
4. O menu suspenso do perfil do Configurador edita o slot *atualmente selecionado* via MSP

---

*Veja `src/main/flight/ornithopter_profile.h` para a definição da estrutura.*