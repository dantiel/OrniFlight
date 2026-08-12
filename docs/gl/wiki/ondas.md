# ONDAS — Estabilización adaptativa dinámica normalizada oscilante

## O principio básico

Unha aeronave de ala fixa ou convencional xera forzas de control **continuamente** — unha deflexión da superficie de control ou un cambio RPM produce un momento de estado estacionario. Un ornitóptero non. Cada gramo de empuxe, cada Newton de torque, está **limitado por fase** dentro do ciclo de batida das ás. O mesmo impulso de forza aplicado en diferentes puntos da carreira produce resultados fundamentalmente diferentes.

ONDAS recoñece esta realidade e modula o esforzo de estabilización de forma sincronizada co ciclo de aleteo.

---

## Cadence — O cerebro do tempo

Cadence é o filtro ONDAS máis crítico porque determina **cando** a corrección dentro de cada batido de ás.

| Fase de trazo | Efecto da aplicación da forza |
|---|---|
| Centro descendente | Elevación máxima, autoridade de rodadura |
| Extremo descendente (freado) | Momento de guiñada de arrastre inducido → |
| Centro de subida | Empuxado cara atrás, lanzamento |
| Extremo ascendente | Inversión de ás, efecto mínimo |

**Cadence cambia a xanela de modulación** para aliñarse coa fase onde o brazo de panca aerodinámico é máis longo. Cadencia incorrecta = física de ala de loita. Cadencia correcta = cada miliwatt convértese en autoridade de control.

### Parámetros

| Parámetro | Valor | Función |
|-----------|-------|-----------|
| `ONDAS_K0` | 1.0 | Desfase de fase base |
| `ONDAS_K2` | 10,0 | Distribución de fases / nitidez |
| `ONDAS_PHASE_SCALE` | 0,00005 | Pequeno factor, gran alavancagem |

---

## Ferocity P — Empuje asimétrico inmediato

Ferocity P aumenta a **escuadratura da forma de onda** (forma trapezoidal: permanencia en ±1, rampa coseno entre) proporcionalmente ao erro PID actual.

- Máis empuxe nun lado → momento inmediato
- A á freada no final de carreira experimenta **arrastre inducido** — este é o momento contrario
- Efecto: directo, proporcional, inmediato

---

## Ferocity D — Explotación de arrastre anticipatorio

Ferocity D completa a imaxe. Onde P proporciona asimetría de empuxe, D aproveita o **arrastre da á contralateral** como freo.

- Le a taxa de erro de cambio e **anticipa**
- Pode explotar deliberadamente o arrastre dunha á ralentizada para os momentos de guiñada ou cabeceo
- P+D xuntos crean un **par de momento diferencial** — empuxe no lado A, arrastre no lado B — máis eficiente que só o empuxe

---

## Tres xeitos Cadence/Ferocity D Aumenta Ferocity

### 1. O — D directo aumenta P durante o cambio rápido de erro

En refachos ou manobras agresivas, `error_rate` é grande. D multiplica isto e engádese á ferocidade base. A á vólvese *máis nítida* (máis trapezoidal) porque P+D xuntos esixen máis cadrados que P só. Resultado: máxima autoridade precisamente cando é crítico.

### 2. Indirecto — Cadence cambia o punto de influencia

Cadence modula *cando* no ciclo a ferocidade actúa. Mover a xanela a unha fase máis aerodinámicamente sensible (por exemplo, o centro da carreira descendente versus o final da carreira ascendente) significa que o **mesmo valor de ferocidade** produce unha amplificación — máis efectiva sen cambios numéricos.

### 3. Combinatoria — D × Cadence durante a recuperación do parado

Nunha parada: alta taxa de afundimento → D detecta a taxa → aumenta a ferocidade. Simultaneamente, a cadencia cambia a modulación na fase de baixada onde a ala ten a máxima mordida. A interacción: D proporciona a forza, a cadencia o momento axeitado. Sen cadencia, a forza D chega á fase equivocada e se disipa inútilmente.

---

## Parámetros adicionais de ONDAS

| Parámetro | Función |
|-----------|----------|
| **Balance** | Simetría de empuxe arriba/abaixo — Sesgo de termo I entre ascendente e descendente. Compensa a asimetría das ás, as tolerancias de fabricación e o desgaste |
| **Warp** | Rodamento/Guiñada P → Diferencial de ferocidade L/R — As ás dereita e esquerda baten de forma independente no eixe de balance para manobras de inclinación e xiro |
| **Anchor** | Anclaxe de fase — bloquea a modulación a unha referencia de fase específica, resistindo a deriva |
| **Resonance** | A compensación de resonancia da célula — evita emocionantes modos estruturais da célula |

---

## Analoxía

**Cadence é o director. Ferocity P e D son os instrumentos.**

Sen director, tocan — pero non xuntos. Cunha, o ruído convértese en música.

---

## Ver tamén

- [ONDAS Tuning Guide](../../tutorials/ondas_tuning.html) — procedemento práctico de afinación
- [Protocolo MSP](msp.html) formato de cable — para os parámetros ONDAS
- [Perfís de voo](profiles.html) — configuración do perfil ONDAS