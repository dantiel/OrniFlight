# Visualización en pantalla (OSD)

OrniFlight inclúe un OSD (visualización en pantalla) integrado mediante o chip MAX7456 ou AT7456E. O OSD superpón os datos de voo na túa fonte de vídeo FPV.

## Elementos compatibles

Configure os elementos na pestana **OSD** de OrniFlight Configurator. Arrastre e solte elementos para situalos na pantalla.

### Datos de voo

| Elemento | Pantallas |
|---------|----------|
| Tensión da batería | Tensión da batería principal (por exemplo, 14,8 V) |
| Tensión media das células | Tensión por célula (por exemplo, 3,7 V) |
| Sorteo actual | Amperios instantáneos |
| mAh debuxado | Capacidade acumulada consumida |
| RSSI | Intensidade do sinal do receptor |
| Modo voo | Modo actual (INDEPENDENT, GLIDE, etc.) |
| Posición do acelerador | Porcentaxe actual do acelerador |
| Temporizador | Tempo de voo / tempo armado |
| Nome da artesanía | OrniFlight nome da artesanía |

### Específico de ornitópteros

| Elemento | Pantallas |
|-----------|----------|
| Frecuencia de bateo | Frecuencia actual de golpe de ala en Hz |
| ONDAS Perfil | Número de perfil de voo activo (1-3) |
| Cadence Fase | Desfase de fase de modulación actual |
| Ángulo servo | Posición do servo de ala |

## Xestión de fontes

O OSD usa un sistema de visualización baseado en caracteres. A pestana **OSD** do Configurador OrniFlight inclúe un **Xestor de fontes** para cargar fontes e glifos personalizados.

## CLI Configuración

zz0zzz

## Hardware

Chip OSD actualmente compatible: **AT7456E** (atópase en placas OMNIBUSF4 e compatibles). MAX7456 é compatible e detectouse automaticamente.