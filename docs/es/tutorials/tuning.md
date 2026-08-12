# PID Sintonización

OrniFlight utiliza un controlador PID (Proporcional-Integral-Derivado) adaptado para vuelo con aleteo. La sintonización difiere significativamente de la de los aviones convencionales debido a la naturaleza periódica del empuje de aleteo.

## Conceptos básicos del ornitóptero PID

A diferencia de los aviones convencionales, donde el empuje es casi continuo, el empuje de los ornitópteros oscila con cada golpe de ala. Esto crea:

- **Ondulación de empuje** a frecuencia de aleteo (normalmente 5–15 Hz)
- **Autoridad de control dependiente de la fase** — la misma salida PID tiene un efecto diferente según en qué parte del ciclo de carrera se aplica
- **Dinámica de giro-guiñada acoplada** — el empuje asimétrico del ala afecta a ambos ejes simultáneamente

## PID Términos

| Término | Efecto | Nota del ornitóptero |
|------|--------|-----------------|
| **P** | Corrección inmediata proporcional — | Utilice valores conservadores; oscilación es sincronizada con el aleteo |
| **Yo** | Corrección integral de errores persistentes — | Imprescindible para mantener la actitud durante los deslizamientos |
| **D** | La derivada — amortigua las oscilaciones | Ajustado a la frecuencia de brazada del ala, no a las oscilaciones del cuadro |
| **Maldita sea** | Feed-forward — directo a la salida | Útil para una respuesta nítida en el eje de balanceo |

## Valores iniciales

Para un ornitóptero de tamaño mediano (1–1,5 m de envergadura):

| Eje | P | Yo | D | F |
|------|---|---|---|---|
| Rollo | 25 | 30 | 15 | 30 |
| Lanzamiento | 30 | 35 | 20 | 35 |
| Guiñada | 40 | 35 | 10 | 20 |

## Procedimiento de ajuste

### 1. Ajuste de tarifas primero

Antes de realizar la sintonización PID, establezca velocidades que le resulten cómodas:
- Comience con RC Tarifa 0,90, Super Tarifa 0,65, Expo 0,30
- Ajuste según su estilo de vuelo y tamaño de ornitóptero.

### 2. Ganancia P

Aumente P hasta que vea una oscilación en la frecuencia de aleteo, luego retroceda un 20%:
- Oscilación de balanceo: el ala se bambolea al ritmo de brazada.
- Oscilación de cabeceo: balanceo longitudinal
- Oscilación de guiñada: movimiento de cola sincronizado con las brazadas

### 3.D Ganancia

Aumente D para amortiguar el rebote después de golpes bruscos con el stick:
- Demasiado: fluctuación del servo, sobrecalentamiento
- Demasiado poco: suena después de que se detiene el balanceo/el cabeceo

### 4. Yo gano

Gano contadores de deriva persistente:
- Aumentar hasta eliminar la deriva.
- Demasiado: oscilación lenta a 1–2 Hz (por debajo de la frecuencia de aleteo)

## Integración ONDAS

ONDAS (Sistema aerodinámico dinámico no lineal de Ornithopter) modula la salida de PID dentro de cada golpe de ala. Después del ajuste básico de PID:

1. Establezca **Cadence Gain** — cambia la ventana de modulación a una fase aerodinámicamente óptima
2. Establezca **Ferocity P** — impulso de empuje asimétrico inmediato
3. Establecer **Ferocity D** — explotación de arrastre anticipada
4. Afinar **Balance** — simetría del ala izquierda/derecha

Consulte la [Guía de sintonización ONDAS](ondas_tuning.html) para conocer el procedimiento detallado.

## Análisis de caja negra

Habilite el registro de Blackbox para visualizar el rendimiento de PID. Busque:
- **Oscilación del término P** en frecuencia de aleteo → reduce P
- **Limpieza del término I** durante giros sostenidos → reduce el I o aumenta la relajación del término I
- **Ruido D-term** por vibración → verifique primero el equilibrio mecánico y luego reduzca D

## Perfiles de vuelo

OrniFlight admite 3 perfiles de vuelo conmutables en pleno vuelo:

| Perfil | Caso de uso |
|---------|----------|
| 1 | Crucero estándar |
| 2 | Alta agilidad/agresividad |
| 3 | Eficiencia / elevación térmica |