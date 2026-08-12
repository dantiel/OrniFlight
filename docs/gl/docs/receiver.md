# Receptor (RX)

OrniFlight admite múltiples protocolos de receptor para o control por radio do teu ornitóptero.

## Protocolos admitidos

| Protocolo | Tipo | Notas |
|----------|------|-------|
| **CRSF** (Fuego cruzado) | Serie | Baixa latencia, telemetría, recomendada |
| **SBUS** | Serie | Invertido, necesita un inversor en F4 |
| **IBUS** (FlySky) | Serie | Non invertido, directo UART |
| **PPM** | Analóxico dun só fío | 8ch, legado, non recomendado |
| **SPEKTRUM** | Serie | 1024/2048, vincular mediante CLI |
| **FPORT** | Serie | FrSky, combina RX+Telemetría |
| **GHST** (Fantasma) | Serie | ImmersionRC, baixa latencia |

## Configuración de serie RX

1. Conecte o receptor a un pin UART RX libre
2. No Configurator → **Ports**: configure UART en `Serial RX`
3. No Configurador → **Configuración**: seleccione o protocolo
4. Para SBUS en F4: activa `set sbus_inversion = ON`

## CLI Configuración rápida

zz0zzz

## A prueba de fallos

Configure o receptor a proba de fallos para que o receptor emita **sen pulsos** na perda de sinal. O controlador de voo detectará isto e activará o seu propio procedemento de seguridade. Consulte [Failsafe](failsafe.html) para a configuración a nivel de FC.