# Modos de voo

Os modos cámbianse a través dos interruptores AUX do teu transmisor. Cada modo pódese asignar a un intervalo de canles AUX específico na pestana **Modos** do Configurador OrniFlight.

## Modos estándar

| Modo | Función |
|------|----------|
| **ARM** | Activar o control de voo (motores/servos activos) |
| **ANGLE** | O nivel automático — craft volve ao nivel cando os paus están centrados |
| **HORIZON** | Modo de ángulo híbrido — preto do centro, acro a plena palanca |
| **ACRO** | — predeterminado sen nivel automático, control de taxa puro |
| **AIRMODE** | Mantén o bucle PID activo con aceleración cero para unha autoridade total |

## OrniFlight-Modos específicos

| ID | Modo | Función |
|----|-------|----------|
| 50 | **INDEPENDENT** | Control de á independente — cada á responde á súa propia canle de servo |
| 51 | **GLIDE** | Modo de deslizamento — ás bloqueadas en posición horizontal para volar |
| 52 | **PROFILE** | Selección de perfil de voo — cambiar entre 3 perfís PID/ONDAS |

## Modos de utilidade

| Modo | Función |
|------|----------|
| **BEEPER** | Activar o timbre para localizar avións perdidos |
| **BLACKBOX** | Iniciar/deter o rexistro de Blackbox |
| **FAILSAFE** | Activar manualmente la etapa 2 a prueba de fallos (interruptor de pánico) |
| **OSD** | Alternar visualización OSD |
| **TELEMETRY** | Activar/desactivar a saída de telemetría |

## Notas de ornitópteros

- O modo **INDEPENDENT** é exclusivo de OrniFlight —, permite o mapeo de servos por ala para o control de empuxe asimétrico e diferencial de ás.
- O modo **GLIDE** mantén as ás en posición neutra, útil para a elevación térmica e o descenso eficiente enerxéticamente
- O cambio **PROFILE** permite cambios no parámetro ONDAS durante o voo para diferentes condicións de voo (por exemplo, cruceiro ou manobras agresivas)