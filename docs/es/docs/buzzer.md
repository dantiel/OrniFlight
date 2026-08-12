# Zumbador

OrniFlight admite zumbadores activos para indicación audible de estado y ubicación de modelo perdido.

## Funciones

- **Armar/Desarmar** — tonos distintos
- **Batería baja** — pitidos de advertencia repetidos
- **A prueba de fallos** patrón — SOS
- **Modelo perdido** — pitido continuo mediante interruptor
- **GPS Fix** — tono de confirmación en bloqueo de satélite
- **Calibración** patrones de pitidos — durante la calibración de giro/aceleración
- **RX Señal perdida** — advertencia cuando se cae la conexión del receptor

## Hardware

- Conecte un zumbador activo de 5 V (NO un piezo pasivo) a los pads **BUZZ-** y **BUZZ+**
- El zumbador es controlado por un transistor en el FC —. No se necesita controlador externo para los zumbadores estándar.

## configuración CLI

```
beeper -GYRO_CALIBRATED     # Disable gyro calibration beeps
beeper -RX_LOST             # Enable receiver lost warning
beeper -ON_USB              # Disable beeper when USB connected
```z

## Seguridad de los ornitópteros

El localizador es especialmente útil para ornitópteros grandes que pueden aterrizar en pasto alto o follaje. Configure el modo BEEPER en un interruptor momentáneo para una activación rápida cuando sea necesario.