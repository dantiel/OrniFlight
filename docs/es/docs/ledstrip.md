# LED tira

OrniFlight admite tiras direccionables WS2812/SK6812 LED para indicación de estado y retroalimentación visual.

## Configuración

Las tiras LED se configuran en la pestaña **LED Strip** del Configurador OrniFlight. Cada posición, color y función de LED se puede configurar individualmente.

## Funciones

| Función | Efecto visual |
|----------|--------------|
| Indicador de batería | Degradado de color verde → amarillo → rojo |
| RSSI | Visualización de la intensidad de la señal |
| Estado del brazo | Cambio de color al armar/desarmar |
| Modo vuelo | Colores específicos del modo |
| Advertencia | Patrones de parpadeo para batería baja, a prueba de fallos |
| Indicador de aleteo | Pulso a la frecuencia de aleteo actual |
| Dirección de empuje | Cambio de color que indica la salida de balanceo/inclinación/guiñada |
| GPS | Bloqueo de satélites y dirección de inicio |

## Hardware

- LED WS2812 o SK6812 RGB
- Conéctese al pad/pin **LED** de su controlador de vuelo
- LED de alimentación desde un BEC (NO alimente desde 3.3V — use 5V)
- Para tiras largas (>8 LED), conecte la alimentación de 5 V directamente a las almohadillas de la batería, no a través de FC

## Uso del ornitóptero

El **Indicador de aleteo** es exclusivo de los LED OrniFlight — que pulsan en sincronía con la frecuencia de golpe del ala, brindando una representación visual del ritmo de aleteo y ayudando a ajustar los parámetros de cadencia de ONDAS.