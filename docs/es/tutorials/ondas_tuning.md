# ONDAS Guía de sintonización

> *El compañero práctico de ONDAS Theory — cómo ajustar cada parámetro según la sensación.*

## Orden de sintonización

Los parámetros ONDAS son interdependientes. Sintonízalos en esta secuencia:

```
1. Cadence    →  timing
2. Ferocity D →  primary stabilization
3. Ferocity P →  response crispness
4. Balance    →  upstroke/downstroke bias
5. Warp       →  modulation width
6. Anchor     →  dry/wet mix
7. Resonance  →  cycle-to-cycle memory
8. Phase 2    →  advanced (prescience, espelho, saudade, SSFF)
```z

## Paso a paso

### 1. Cadence — Encuentra tu ventana de fase

**Objetivo**: Colocar la modulación donde tu ala tenga más mordida.

**Método**: 
- Empezar a los 50
- Aumente a 70 — ¿la respuesta al balanceo se vuelve más débil?
- Disminución a 30 — ¿la respuesta al balanceo se vuelve más fuerte?
- El punto "más fuerte" es donde la potencia de tu vela alcanza su punto máximo.

**Señales de demasiado alto**: respuesta blanda, la artesanía se siente "retrasada"
**Señales de demasiado bajo**: respuesta entrecortada, sobrepaso en rollo

### 2. Ferocity D — Estabiliza el oficio

**Objetivo**: Estabilización primaria sin oscilación.

**Método**:
- Empieza a las 20
- Flotación o vuelo constante hacia adelante
- Aumente hasta que sienta que la embarcación se "endurece"
- Retroceda 5 puntos desde donde notó la oscilación por primera vez.

**Signos de demasiado alto**: vibración fina, zumbido similar al de un motor en los servos
**Señales de nivel demasiado bajo**: la embarcación se desvía, se siente floja

### 3. Ferocity P — Crujiente

**Objetivo**: receptivo pero no nervioso.

**Método**:
- Empieza a las 15
- Golpea el palo giratorio —, ¿la nave muerde inmediatamente?
- Aumente hasta que la respuesta de la palanca sea nítida
- Retroceda si ve un exceso

**Señales de demasiado alto**: timbre después de tocar la palanca, rebote
**Signos de nivel demasiado bajo**: respuesta blanda y tardía

### 4. Balance — Ajuste de asimetría

**Objetivo**: Igual autoridad en ambas direcciones.

**Método**:
- Vuela recto y nivelado.
- Girar hacia la izquierda, observar la velocidad de respuesta.
- Gira hacia la derecha, observa la velocidad de respuesta.
- Ajustar el equilibrio para igualarlos.

### 5–7. Warp, Anchor, Resonance

Parámetros de ajuste fino. Sólo ajuste después de que 1-4 estén sólidos.

| Parámetro | Inicio | Ajustar cuando |
|-------|-------|-------------|
| Warp | 50 | La modulación se siente demasiado dispersa o demasiado picosa.
| Anchor | 70 | Quiere más/menos PID crudo mezclado |
| Resonance | 30 | El vuelo estacionario es inestable o el vuelo hacia adelante se siente sonoro |

### 8. Phase 2 — Avanzado

| Parámetro | Efecto |
|-------|--------|
| Prescience | Avance de sincronización — más alto = la modulación lleva la fase más |
| Espelho | Acoplamiento diferencial — rollo más apretado, puede reducir la eficiencia |
| Saudade | Memoria de trazos — más fluida pero con menos capacidad de respuesta |
| SSFF | Inyección directa gyro→wave — comienza a las 10 |

---

*El objetivo es una nave que vuele como si quisiera estar en el aire. Si estás luchando contra ello, retrocede y vuelve a sintonizar desde Cadence hacia arriba.*