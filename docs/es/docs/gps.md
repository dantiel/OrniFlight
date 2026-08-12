# GPS

GPS permite mantener la posición, regresar a casa y navegar mediante telemetría para su ornitóptero. Las características de GPS en OrniFlight son funcionales, pero se consideran experimentales. — siempre vuela dentro de la línea de visión.

## Protocolos admitidos

- **UBLOX** (recomendado) — Protocolo binario UBlox, eficiente y confiable
- **NMEA** — Protocolo estándar basado en texto

## Hardware

- BN-880, BN-220 o módulos similares UBlox M8N GPS+Compass
- Conecte: TX/RX a un UART gratuito, más 5V/GND
- Monte el GPS lejos de cables de alimentación y servocables para minimizar las interferencias.
- La brújula/magnetómetro debe estar alejado de fuentes magnéticas (cables de alimentación, servos)

## Configuración

```
feature GPS
set gps_provider = UBLOX
set gps_sbas_mode = AUTO
set gps_auto_baud = ON
set gps_ublox_use_galileo = ON
```z

1. Asigne el puerto serie a GPS en la pestaña **Puertos** (115200 baudios predeterminados para UBlox)
2. Habilite la función GPS
3. Establecer proveedor
4. Guardar y reiniciar

## OSD Elementos

Los datos de GPS mostrados en OSD incluyen:
- Recuento de satélites y tipo de corrección.
- Coordenadas GPS (lat/lon)
- Velocidad de avance
- Altitud (GPS)
- Distancia desde casa
- Flecha de dirección de inicio

## Consideraciones sobre ornitópteros

- La antena GPS debe tener una vista despejada del cielo. La ubicación de montaje — es crítica con alas batientes.
- La penalización de peso es significativa en ornitópteros pequeños.
- RTH (regreso a casa) asistido por GPS requiere un ajuste cuidadoso de los valores de navegación PID para la dinámica de vuelo de aleteo