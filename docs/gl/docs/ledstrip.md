# LED Strip

OrniFlight admite tiras WS2812/SK6812 LED direccionables para indicación de estado e retroalimentación visual.

## Configuración

As tiras LED están configuradas na pestana **LED Strip** do Configurador OrniFlight. Cada posición, cor e función LED pódense configurar individualmente.

## Funcións

| Función | Efecto Visual |
|----------|--------------|
| Indicador de batería | Degradado de cor do verde → amarelo → vermello |
| RSSI | Visualización da intensidade do sinal |
| Estado do brazo | Cambio de cor ao armar/desarmar |
| Modo voo | Cores específicas do modo |
| Aviso | Patróns de parpadeo para batería baixa, a prueba de fallos |
| Indicador de aleteo | Pulso á frecuencia de bateo actual |
| Dirección de empuxe | Cambio de cor que indica a saída de balanceo/ cabeceo/ guiñada |
| GPS | Bloqueo de satélite e dirección de inicio |

## Hardware

- LEDs WS2812 ou SK6812 RGB
- Conéctate ao pad/pin **LED** do teu controlador de voo
- LED de alimentación dun BEC (NON alimentar a partir de 3,3 V — use 5 V)
- Para tiras longas (>8 LED), conecte a alimentación de 5 V directamente ás almofadas da batería, non a través de FC

## Uso de ornitópteros

O **Indicador de aleteo** é exclusivo dos LED OrniFlight — pulso sincronizado coa frecuencia de batida das ás, dándolle unha representación visual do ritmo de aleteo e axudando a afinar os parámetros de cadencia ONDAS.