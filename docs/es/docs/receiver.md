# Receptor (RX)

OrniFlight admite múltiples protocolos de receptor para el control por radio de su ornitóptero.

## Protocolos admitidos

| Protocolo | Tipo | Notas |
|----------|------|-------|
| **CRSF** (Fuego cruzado) | Serie | Baja latencia, telemetría, recomendada |
| **SBUS** | Serie | Invertido, necesita inversor en F4 |
| **IBUS** (FlySky) | Serie | Directo, no invertido UART |
| **PPM** | Analógico de un solo cable | 8 canales, heredado, no recomendado |
| **SPEKTRUM** | Serie | 1024/2048, enlazar vía CLI |
| **FPORT** | Serie | FrSky, combina RX+Telemetría |
| **GHST** (Fantasma) | Serie | ImmersionRC, baja latencia |

## Configuración serie RX

1. Conecte el receptor a un pin UART RX libre
2. En el Configurador → **Puertos**: establezca UART en `Serial RX`
3. En Configurador → **Configuración**: seleccione protocolo
4. Para SBUS en F4: habilite `set sbus_inversion = ON`

## CLI Configuración rápida

```
feature RX_SERIAL
set serialrx_provider = CRSF
set serialrx_inverted = OFF
set serialrx_halfduplex = OFF
save
```z

## A prueba de fallos

Configure el receptor a prueba de fallas para que el receptor emita **sin pulsos** en caso de pérdida de señal. El controlador de vuelo detectará esto y activará su propio procedimiento de seguridad. Consulte [Failsafe](failsafe.html) para la configuración de nivel FC.