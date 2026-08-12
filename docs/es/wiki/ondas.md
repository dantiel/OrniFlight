# ONDAS — Estabilización adaptativa dinámica normalizada oscilante

## El principio básico

Una aeronave de ala fija o convencional genera fuerzas de control **continuamente** — una deflexión de la superficie de control o un cambio RPM produce un momento de estado estacionario. Un ornitóptero no. Cada gramo de empuje, cada Newton de torsión, está **en fase** dentro del ciclo de aleteo. El mismo impulso de fuerza aplicado en diferentes puntos del golpe produce resultados fundamentalmente diferentes.

ONDAS reconoce esta realidad y modula el esfuerzo de estabilización sincrónicamente con el ciclo de aleteo.

---

## Cadence — El cerebro del tiempo

Cadence es el filtro ONDAS más crítico porque determina **cuándo** ocurre la corrección dentro de cada aleteo.

| Fase de accidente cerebrovascular | Efecto de la aplicación de fuerza |
|---|---|
| Centro de descenso | Máxima autoridad de elevación y balanceo |
| Fin de carrera descendente (frenado) | Arrastre inducido → momento de guiñada |
| Centro de carrera ascendente | Empuje hacia atrás, cabeceo |
| Fin de carrera ascendente | Inversión del ala, efecto mínimo |

**Cadence cambia la ventana de modulación** para alinearla con la fase donde el brazo de palanca aerodinámico es más largo. Cadencia incorrecta = física del ala de combate. Cadencia correcta = cada milivatio se convierte en autoridad de control.

### Parámetros

| Parámetro | Valor | Función |
|-----------|-------|----------|
| `ONDAS_K0` | 1.0 | Desplazamiento de fase base |
| `ONDAS_K2` | 10.0 | Distribución de fase/nitidez |
| `ONDAS_PHASE_SCALE` | 0,00005 | Pequeño factor, gran apalancamiento |

---

## Ferocity P — Empuje asimétrico inmediato

Ferocity P aumenta la **cuadratura de la forma de onda** (forma trapezoidal: permanencia en ±1, rampa de coseno entre) proporcionalmente al error actual de PID.

- Más empuje en un lado → momento inmediato
- El ala frenada al final de la carrera experimenta **resistencia inducida** —, este es el contramomento.
- Efecto: directo, proporcional, inmediato

---

## Ferocity D — Explotación de arrastre anticipada

Ferocity D completa el cuadro. Donde P proporciona asimetría de empuje, D aprovecha el **arrastre del ala contralateral** como freno.

- Lee la tasa de error de cambio y **anticipa**
- Puede explotar deliberadamente la resistencia de un ala desacelerada para momentos de guiñada/cabeceo.
- P+D juntos crean un **par de momento diferencial** — empuje en el lado A, arrastre en el lado B — más eficiente que solo empuje

---

## Tres formas de Cadence/Ferocity D aumentan Ferocity

### 1. Direct — D aumenta P durante el cambio rápido de error

En rachas o maniobras agresivas, `error_rate` es grande. D multiplica esto y aumenta la ferocidad básica. El ala se vuelve *más afilada* (más trapezoidal) porque P+D juntos exigen más cuadratura que P solo. Resultado: máxima autoridad precisamente en los momentos críticos.

### 2. Indirecto — Cadence cambia el punto de apalancamiento

Cadence modula *cuando* en el ciclo actúa la ferocidad. Mover la ventana a una fase más aerodinámicamente sensible (por ejemplo, centro de carrera descendente versus final de carrera ascendente) significa que el **mismo valor de ferocidad** produce más efecto — amplificación efectiva sin cambios numéricos.

### 3. Combinatoria — D × Cadence durante la recuperación de pérdida

En pérdida: alta tasa de caída → D detecta la tasa → aumenta la ferocidad. Al mismo tiempo, la cadencia cambia la modulación a la fase de descenso, donde el ala tiene la máxima mordida. La interacción: D proporciona la fuerza, la cadencia el momento adecuado. Sin cadencia, D-force llega a la fase equivocada y se disipa inútilmente.

---

## Parámetros adicionales de ONDAS

| Parámetro | Función |
|-----------|----------|
| **Balance** | Simetría de empuje hacia arriba/abajo — Sesgo del término I entre carrera ascendente y descendente. Compensa la asimetría del ala, las tolerancias de fabricación y el desgaste |
| **Warp** | Roll/Yaw P → Diferencial de ferocidad L/R — Las alas derecha e izquierda aletean independientemente en el eje de balanceo para maniobras de inclinación y giro |
| **Anchor** | El anclaje de fase — bloquea la modulación en una referencia de fase específica, resistiendo la deriva |
| **Resonance** | La compensación de resonancia del fuselaje — evita modos estructurales interesantes del fuselaje |

---

## Analogía

**Cadence es el director. Ferocity P y D son los instrumentos.**

Sin director, tocan — pero no juntos. Con uno, el ruido se convierte en música.

---

## Ver también

- [Guía de sintonización ONDAS](../../tutorials/ondas_tuning.html) procedimiento de sintonización práctico —
- [Protocolo MSP](msp.html) formato de cable — para parámetros ONDAS
- [Perfiles de vuelo](profiles.html) — configuración ONDAS compatible con el perfil