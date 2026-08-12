# PID Afinación

OrniFlight usa un controlador PID (Proporcional-Integral-Derivada) adaptado para voo de ás. A afinación difire significativamente das aeronaves convencionais debido á natureza periódica do empuxe de aleteo.

## Ornithopter PID Conceptos básicos

A diferenza dos avións convencionais onde o empuxe é case continuo, o empuxe dos ornitópteros oscila con cada golpe de á. Isto crea:

- **Ondulado de empuxe** na frecuencia de aleteo (normalmente 5–15 Hz)
- **Autoridade de control dependente da fase** — a mesma saída PID ten un efecto diferente dependendo de onde se aplique no ciclo de trazo
- **Dinámica de balanceo acoplado** — o empuxe asimétrico da ala afecta a ambos eixes simultáneamente

## PID Condicións

| Prazo | Efecto | Nota de ornitópteros |
|------|---------|-----------------|
| **P** | Corrección inmediata — proporcional | Utilizar valores conservadores; a oscilación é aleteo-sincrónico |
| **Eu** | Corrección de erros persistentes — integral | Imprescindible para manter a actitude durante os deslizamentos |
| **D** | A derivada — amortece as oscilacións | Axustado á taxa de golpe das ás, non ás oscilacións do cadro |
| **F** | Feed-forward — adherencia directa á saída | Útil para unha resposta nítida no eixe de rolo |

## Valores iniciais

Para un ornitóptero de tamaño mediano (1–1,5 m de envergadura):

| Eixo | P | eu | D | F |
|------|---|---|---|---|
| Rolo | 25 | 30 | 15 | 30 |
| Pitch | 30 | 35 | 20 | 35 |
| Guiña | 40 | 35 | 10 | 20 |

## Procedemento de sintonía

### 1. Primeiro axuste da taxa

Antes de sintonizar PID, establece tarifas que resulten cómodas:
- Comeza con RC Rate 0,90, Super Rate 0,65, Expo 0,30
- Axuste ao seu estilo de voo e tamaño do ornitóptero

### 2. P Gain

Aumenta P ata que vexa a oscilación na frecuencia de aleteo e, a continuación, retroceda un 20 %:
- Oscilación de balance: bamboleo das alas ao ritmo de golpe
- Oscilación do tono: balance de proa-popa
- Oscilación de guiñada: meneo de cola sincronizado cos golpes

### 3. D Ganancia

Aumenta D para amortiguar o rebote despois de introducir un pau afiado:
- Demasiado: fluctuación dos servos, sobrequecemento
- Demasiado pouco: timbre despois das paradas de balance/ cabeceo

### 4. Gaño

Gaño contadores de deriva persistente:
- Aumentar ata eliminar a deriva
- Demasiado: oscilación lenta a 1–2 Hz (por debaixo da taxa de bateo)

## ONDAS Integración

ONDAS (Ornithopter Nonlinear Dynamic Aerodynamic System) modula a saída PID dentro de cada golpe de ala. Despois da afinación básica de PID:

1. Establece **Cadence Gain** — cambia a xanela de modulación á fase aerodinámicamente óptima
2. Establece **Ferocity P** — impulso de empuxe asimétrico inmediato
3. Establece **Ferocity D** — explotación de arrastre anticipada
4. Afina **Balance** — a simetría da á esquerda/dereita

Consulte [ONDAS Tuning Guide](ondas_tuning.html) para obter un procedemento detallado.

## Análise da caixa negra

Activa o rexistro de Blackbox para visualizar o rendemento de PID. Busca:
- **Oscilación do termo P** na frecuencia de aleteo → reduce P
- **I-term windup** durante xiros sostidos → reduce I ou aumenta I-term relax
- **Ruído de termo D** da vibración → primeiro comproba o equilibrio mecánico e despois reduce D

## Perfís de voo

OrniFlight admite 3 perfís de voo conmutables durante o voo:

| Perfil | Caso de uso |
|---------|----------|
| 1 | Cruceiro estándar |
| 2 | Alta axilidade / agresivo |
| 3 | Eficiencia / elevación térmica |