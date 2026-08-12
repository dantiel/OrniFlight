# Visualización en pantalla (OSD)

OrniFlight incluye un OSD (visualización en pantalla) integrado que utiliza el chip MAX7456 o AT7456E. El OSD superpone datos de vuelo en su transmisión de video FPV.

## Elementos compatibles

Configure elementos en la pestaña **OSD** del Configurador OrniFlight. Arrastra y suelta elementos para posicionarlos en la pantalla.

### Datos de vuelo

| Elemento | Pantallas |
|---------|----------|
| Voltaje de la batería | Tensión de la batería principal (por ejemplo, 14,8 V) |
| Voltaje promedio de la celda | Voltaje por celda (por ejemplo, 3,7 V) |
| Sorteo actual | Amplificadores instantáneos |
| mAh dibujado | Capacidad acumulada consumida |
| RSSI | Intensidad de la señal del receptor |
| Modo vuelo | Modo actual (INDEPENDENT, GLIDE, etc.) |
| Posición del acelerador | Porcentaje de aceleración actual |
| Temporizador | Tiempo de vuelo/tiempo de armado |
| Nombre de la artesanía | OrniFlight nombre de la artesanía |

### Específico de ornitópteros

| Elemento | Pantallas |
|----------|----------|
| Frecuencia de aleteo | Frecuencia de brazada actual del ala en Hz |
| Perfil ONDAS | Número de perfil de vuelo activo (1-3) |
| Fase Cadence | Desplazamiento de fase de modulación actual |
| Ángulo servo | Posición del servo del ala |

## Gestión de fuentes

El OSD utiliza un sistema de visualización basado en caracteres. La pestaña **OSD** del Configurador OrniFlight incluye un **Administrador de fuentes** para cargar fuentes y glifos personalizados.

## configuración CLI

```
set osd_units = METRIC
set osd_warn_bitmask = 270335  # Warning flag bitmask
set osd_tim1 = 2560            # Timer 1 source
set osd_tim2 = 2561            # Timer 2 source
```z

## Hardware

Chip OSD actualmente compatible: **AT7456E** (se encuentra en OMNIBUSF4 y placas compatibles). MAX7456 es compatible y se detecta automáticamente.