# Monitoreo de batería

OrniFlight monitorea el voltaje de la batería principal a través del ADC (convertidor analógico a digital). Esto habilita advertencias de batería baja a través de patrones de zumbador, estado LED y LED.

## Características

- Detección automática del recuento de celdas al conectar (basado en voltajes de celda mínimo/máximo)
- Advertencia de batería baja con umbrales configurables
- Detección de corriente para el consumo de mAh (si es compatible con FC)
- Voltaje mostrado en OSD y transmitido vía telemetría

## Objetivos admitidos

Todos los controladores de vuelo compatibles (OMNIBUSF4, TINYFISH) incluyen monitoreo VBAT mediante divisor de voltaje.

## Conexiones

**SIEMPRE COMPRUEBE LA POLARIDAD.** Mida los voltajes esperados antes de realizar la conexión. Un voltaje incorrecto o una polaridad invertida destruirán su controlador de vuelo.

### OMNIBUSF4

Conecte la batería principal al pad VBAT. El divisor de voltaje integrado maneja hasta 6S directamente.

### TINYFISHz

VBAT se enruta a través de la entrada de alimentación de la placa —, no se necesita una conexión separada.

## configuración CLI

```
set vbat_min_cell_voltage = 330       # Minimum per-cell voltage (3.3V)
set vbat_max_cell_voltage = 430       # Maximum per-cell voltage (4.3V)
set vbat_warning_cell_voltage = 350   # Warning threshold (3.5V)
set battery_meter_type = ADC
set current_meter_type = ADC          # If current sensor available
```z

## Seguridad

Las baterías LiPo nunca deben descargarse por debajo de 3,5 V por celda bajo carga. Los umbrales configurables de OrniFlight ayudan a garantizar un funcionamiento seguro y la longevidad de la batería.