# Configuración básica

> *Configura tu ornitóptero para el primer vuelo.*

## Lista de verificación previa al vuelo

Antes que nada:

- [] Controlador de vuelo flasheado con OrniFlight
- [ ] Receptor vinculado al transmisor
- [ ] Servos conectados a las salidas correctas de PWM
- [ ] Batería conectada (¡alas aseguradas!)

## Configuración del receptor

### CRSF (Recomendado)

1. **Pestaña Puertos**: configure UART (por ejemplo, UART1) en "Serial RX"
2. **Pestaña Configuración**: Modo receptor = "Receptor basado en serie", Proveedor = "CRSF"
3. Apague y encienda, verifique que las entradas del canal se muevan en la pestaña Receptor

### SBUS / Otro

El mismo proceso — selecciona el protocolo apropiado en la pestaña Configuración.

## Mapeo de servos

En la **pestaña Servos**:

| Servo | Función | Tasa predeterminada |
|-------|----------|-------------|
| Servo 0 | Ala izquierda | 250 Hz |
| Servo 1 | Ala Derecha | 250Hz |
| Servo2 | Cresta/timón | 50Hz |

Ajuste mínimo/máximo/medio para que coincida con el rango de su servo. Pruebe con "Anular" para verificar la dirección.

## Selección del modo de vuelo

En la **pestaña Modos**:

1. **ARM**: Asignar a un interruptor (¡seguridad!)
2. **ORNITHOPTER INDEPENDENT** o **ORNITHOPTER GLIDE**: elige tu modo de vuelo principal
3. **ORNITHOPTER PROFILE**: asignación — opcional para cambio de perfil en vuelo

## ONDAS Primera afinación

Vaya a **Subpestaña Avanzado → ONDAS**:

1. **ganancia Cadence**: comience en 50 (medio). Este es el parámetro más importante.
2. **Ferocity D Ganancia**: comienza en 30. Esta es tu estabilización principal.
3. **Ferocity P Ganancia**: Comience en 20 para balanceo/cabeceo, 0 para guiñada.
4. **Balance Ganancia**: 0 (centrado).

Conecte una batería, **asegure firmemente el ornitóptero** y ARM. Observe el movimiento del servo —; debe ser un aleteo suave y sinusoidal.

## Primer vuelo

1. Comience con un suave lanzamiento hacia el viento.
2. Utilice el modo GLIDE para una sensación de vuelo natural
3. Utilice el modo INDEPENDENT cuando desee control de frecuencia directo
4. Aterriza, ajusta ONDAS, repite

---

*Siguiente: [Guía de afinación ONDAS](ondas_tuning.html) →*