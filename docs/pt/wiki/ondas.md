# ONDAS — Estabilização adaptativa dinâmica normalizada oscilante

## O Princípio Fundamental

Uma aeronave de asa fixa ou convencional gera forças de controle **continuamente** —, uma deflexão da superfície de controle ou mudança RPM produz um momento de estado estacionário. Um ornitóptero não. Cada grama de empuxo, cada Newton de torque, está **ligado à fase** dentro do ciclo de batida de asa. O mesmo impulso de força aplicado em diferentes pontos do curso produz resultados fundamentalmente diferentes.

ONDAS reconhece esta realidade e modula o esforço de estabilização de forma síncrona com o ciclo de oscilação.

---

## Cadence — O Cérebro Timing

Cadence é o filtro ONDAS mais crítico porque determina **quando** a correção ocorre dentro de cada batida de asa.

| Fase do AVC | Efeito da aplicação de força |
|---|---|
| Centro de descida | Elevação máxima, autoridade de rolagem |
| Fim do curso descendente (frenagem) | Arrasto induzido → momento de guinada |
| Centro ascendente | Impulso para trás, inclinação para cima |
| Final ascendente | Inversão de asa, efeito mínimo |

**Cadence muda a janela de modulação** para alinhar com a fase onde o braço da alavanca aerodinâmica é mais longo. Cadência errada = luta contra a física das asas. Cadência correta = cada miliwatt se torna autoridade de controle.

### Parâmetros

| Parâmetro | Valor | Função |
|----------|-------|----------|
| `ONDAS_K0` | 1,0 | Deslocamento da fase base |
| `ONDAS_K2` | 10,0 | Propagação/nitidez de fase |
| `ONDAS_PHASE_SCALE` | 0,00005 | Fator pequeno, grande alavancagem |

---

## Ferocity P — Impulso Assimétrico Imediato

Ferocity P aumenta a **quadratura da forma de onda** (formato trapezoidal: permanência em ±1, rampa de cosseno entre) proporcionalmente ao erro PID atual.

- Mais impulso de um lado → momento imediato
- A asa freada no final do curso experimenta **arrasto induzido** — este é o contra-momento
- Efeito: direto, proporcional, imediato

---

## Ferocity D — Exploração de arrasto antecipado

Ferocity D completa o quadro. Onde P fornece assimetria de empuxo, D aproveita o **arrasto da asa contralateral** como freio.

- Lê a taxa de erro da mudança e **antecipa**
- Pode explorar deliberadamente o arrasto de uma asa desacelerada para momentos de guinada/inclinação
- P+D juntos criam um **par de momentos diferenciais** — impulso no lado A, arrasto no lado B — mais eficiente do que apenas impulso

---

## Três maneiras de Cadence/Ferocity D aumentar Ferocity

### 1. Zzz18zzz D direto aumenta P durante mudança rápida de erro

Em rajadas ou manobras agressivas, `error_rate` é grande. D multiplica isso e aumenta a ferocidade básica. A asa torna-se *mais nítida* (mais trapezoidal) porque P+D juntos exigem mais quadratura do que P sozinho. Resultado: autoridade máxima precisamente quando é crítico.

### 2. Zzz19zzz Cadence indireto muda o ponto de alavancagem

Cadence modula *quando* no ciclo a ferocidade atua. Mover a janela para uma fase mais aerodinamicamente sensível (por exemplo, centro de movimento descendente vs. final de movimento ascendente) significa que o **mesmo valor de ferocidade** produz mais efeito de amplificação — efetivamente sem alteração numérica.

### 3. Combinatória — D × Cadence durante a recuperação de estol

Em um estol: alta taxa de afundamento → D detecta a taxa de → que aumenta a ferocidade. Simultaneamente, a cadência muda a modulação para a fase de descida, onde a asa tem mordida máxima. A interação: D fornece a força, cadência o momento certo. Sem cadência, a força D chega na fase errada e se dissipa inutilmente.

---

## Parâmetros ONDAS adicionais

| Parâmetro | Função |
|-----------|----------|
| **Balance** | Simetria de empuxo para cima/para baixo — Viés de termo I entre movimento ascendente e descendente. Compensa a assimetria das asas, tolerâncias de fabricação e desgaste |
| **Warp** | Roll/Yaw P → Diferencial de ferocidade L/R — asas direita e esquerda batem independentemente no eixo de rotação para manobras de inclinação e curva |
| **Anchor** | A ancoragem de fase — bloqueia a modulação em uma referência de fase específica, resistindo ao desvio |
| **Resonance** | A compensação de ressonância da fuselagem — evita modos estruturais emocionantes da fuselagem |

---

## Analogia

**Cadence é o maestro. Ferocity P e D são os instrumentos.**

Sem maestro, eles tocam —, mas não juntos. Com um, o ruído se torna música.

---

## Veja também

- [Guia de ajuste ONDAS](../../tutorials/ondas_tuning.html) — procedimento prático de ajuste
- [Protocolo MSP](msp.html) formato de ligação — para parâmetros ONDAS
- [Perfis de voo](profiles.html) configuração ONDAS com reconhecimento de perfil —