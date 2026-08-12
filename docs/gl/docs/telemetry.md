#Telemetría

A telemetría envía datos de voo desde OrniFlight ao teu transmisor de radio — tensión da batería, corrente, coordenadas RSSI, GPS, altitude e moito máis.

## Protocolos admitidos

| Protocolo | Sistema de radio | Conta de fíos |
|----------|-------------|------------|
| **CRSF** | Crossfire / Tracer / ELRS | Integrado con RX (bidireccional) |
| **SmartPort** | FrSky | 1 fío (pin TX) |
| **HoTT** | Graupner | 1 fío (TX+TZ) |
| **IBUS** | FlySky | 1 cable (sensor TX) |
| **LTM** | Telemetría de luz (MWP) | 1 fío (TX) |

## Configuración

1. No Configurator → **Ports**: configure o pin UART TX no protocolo de telemetría adecuado
2. Activa a función de telemetría: `feature TELEMETRY`
3. Configure a inversión de telemetría se é necesario

Para **CRSF**, a telemetría xestionase automaticamente — non é necesario un porto separado.

## SmartPort (FrSky)

SmartPort require a inversión de sinal nos procesadores F4. Calquera cousa:
- Use un controlador de voo con inversor incorporado
- Use SoftSerial con `set tlm_inversion = ON`

zz0zzz

## Datos de telemetría

OrniFlight transmite:
- voltaxe VBAT (batería principal)
- Consumo de corrente / mAh consumido
- RSSI (intensidade do sinal)
- Modo voo / estado do brazo
- Coordenadas GPS (se está equipado)
- Altitude / vario (se barómetro)
- Perfil de voo ONDAS activo