# a prueba de fallos

OrniFlight tiene un sistema de seguridad de dos etapas para proteger su ornitóptero en caso de pérdida de señal del receptor.

## Sistema de dos etapas

### Etapa 1 — Pérdida de señal detectada

Se activa cuando:
- Cualquier canal de vuelo tiene una longitud de pulso no válida
- El receptor informa del modo a prueba de fallos
- No hay señal del receptor durante un tiempo configurado

**Acción**: Todos los canales cambian a valores de reserva (configurados a través de `rxfail`). Comienza una breve ventana de recuperación —. Si la señal regresa, se reanuda el vuelo normal.

### Etapa 2 — Tiempo de guardia expiró

Se ingresa cuando la Etapa 1 persiste por más de `failsafe_delay` (predeterminado: 400 ms) Y la nave está armada.

**Procedimientos** (configurable vía `failsafe_procedure`):

| Procedimiento | Comportamiento |
|-----------|----------|
| **DROP** | Desarmar inmediatamente — alas se detienen, avión desciende |
| **LAND** | Modo planeo — alas bloqueadas horizontalmente, descenso controlado |

**LAND** es el procedimiento recomendado para ornitópteros —. Mantiene las alas en una posición neutral para un descenso en planeo, dando tiempo para la recuperación de la señal.

## configuración CLI

```
set failsafe_delay = 4         # Guard time in 0.1s (4 = 400ms)
set failsafe_procedure = LAND  # DROP or LAND
set failsafe_throttle = 1000   # Fallback throttle (low)
set failsafe_switch_mode = STAGE1  # Transmitter switch behavior
```z

## Receptor a prueba de fallos

También configure el sistema de seguridad de su receptor para que emita **sin pulsos** en caso de pérdida de señal. Esto permite que el controlador de vuelo detecte la pérdida y active la Etapa 1.

## Pruebas

Pruebe el mecanismo de seguridad **con el varillaje del ala desconectado** en el banco:
1. Asigne el modo FAILSAFE a un interruptor
2. Arma la nave
3. Mueva el interruptor → y observe el procedimiento a prueba de fallos.
4. Verificar que el comportamiento del servo coincida con las expectativas