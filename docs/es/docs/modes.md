# Modos de vuelo

Los modos se alternan mediante interruptores AUX en su transmisor. Cada modo se puede asignar a un rango de canales AUX específico en la pestaña **Modos** del Configurador OrniFlight.

## Modos estándar

| Modo | Función |
|------|----------|
| **ARM** | Habilitar control de vuelo (motores/servos activos) |
| **ANGLE** | La nave — de nivel automático vuelve al nivel cuando los palos están centrados |
| **HORIZON** | Modo de ángulo híbrido — cerca del centro, acro al máximo |
| **ACRO** | Predeterminado — sin nivel automático, control de velocidad puro |
| **AIRMODE** | Mantiene activo el bucle PID a velocidad cero para obtener plena autoridad |

## OrniFlight-Modos específicos

| ID | Modo | Función |
|----|------|----------|
| 50 | **INDEPENDENT** | Control de ala independiente — cada ala responde a su propio canal de servo |
| 51 | **GLIDE** | Modo planeo — alas bloqueadas en posición horizontal para volar |
| 52 | **PROFILE** | Selección de perfil de vuelo — cambiar entre 3 perfiles PID/ONDAS |

## Modos de utilidad

| Modo | Función |
|------|----------|
| **BEEPER** | Activar timbre para localizar aeronaves perdidas |
| **BLACKBOX** | Iniciar/detener el registro de Blackbox |
| **FAILSAFE** | Activar manualmente la etapa de seguridad 2 (interruptor de pánico) |
| **OSD** | Alternar visualización OSD |
| **TELEMETRY** | Activar/desactivar salida de telemetría |

## Notas del ornitóptero

- El modo **INDEPENDENT** es exclusivo de OrniFlight — y permite el mapeo de servo por ala para empuje asimétrico y control diferencial del ala.
- El modo **GLIDE** mantiene las alas en posición neutral, útil para el vuelo térmico y el descenso energéticamente eficiente.
- El cambio **PROFILE** permite cambios de parámetros ONDAS en vuelo para diferentes condiciones de vuelo (por ejemplo, crucero versus maniobras agresivas)