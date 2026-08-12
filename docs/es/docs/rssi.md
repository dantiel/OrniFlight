# RSSI

RSSI (Indicador de intensidad de la señal recibida) muestra la calidad de su enlace de radio. OrniFlight puede generar RSSI a partir de una entrada analógica, datos del receptor en serie o el protocolo RSSI.

## RSSI Fuentes

| Fuente | Conexión | Configuración |
|--------|-----------|---------------|
| **Protocolo serie** | Ninguno (a través del cable serie RX) | CRSF, GHST — automático |
| **Canal AUX** | Ninguno (TX envía RSSI como canal) | `set rssi_channel = 8` |
| **Analógico ADC** | RSSI pad en FC → Receptor RSSI fuera | `set rssi_adc_channel = 1` |

## Configuración

### Serie RSSI (CRSF/GHST/SBUS)

```
set rssi_src_frame_errors = OFF
set rssi_scale = 100
set rssi_offset = 0
```z

RSSI se transmite automáticamente mediante protocolos seriales —, no se necesita cableado adicional.

### Analógico RSSI

Conecte la salida RSSI del receptor → RSSI pad en el controlador de vuelo:

```
set rssi_adc_channel = 1      # Use ADC channel 1
set rssi_scale = 100          # Scale to 0-100%
set rssi_offset = 0
```z

### AUX Canal RSSI

Configure su transmisor para enviar RSSI en un canal específico, luego:

```
set rssi_channel = 12         # Aux channel number
set rssi_scale = 100
set rssi_offset = 0
```

## Mostrar

RSSI se muestra en OSD y se puede transmitir mediante telemetría a su radio. Configurar umbrales de advertencia:

```
set osd_rssi_alarm = 20        # Warning at 20% RSSI
```

## Rango de ornitópteros

Para los ornitópteros, RSSI es fundamental. — Las alas batientes crean patrones dinámicos de interferencia RF. Supervise RSSI durante los vuelos de prueba iniciales para verificar el rendimiento confiable del enlace en todas las posiciones del ala.