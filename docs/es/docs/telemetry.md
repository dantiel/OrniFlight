# Telemetría

La telemetría envía datos de vuelo desde OrniFlight a su transmisor de radio —, voltaje de la batería, corriente, coordenadas RSSI, GPS, altitud y más.

## Protocolos admitidos

| Protocolo | Sistema de radio | Recuento de cables |
|----------|-------------|------------|
| **CRSF** | Fuego cruzado / Trazador / ELRS | Integrado con RX (bidireccional) |
| **SmartPort** | FrSky | 1 cable (pin TX) |
| **HoTT** | Graupner | 1 hilo (TX+TZ) |
| **IBUS** | FlySky | 1 cable (sensor TX) |
| **LTM** | Telemetría de luz (MWP) | 1 hilo (TX) |

## Configuración

1. En el Configurador → **Puertos**: establezca el pin UART TX en el protocolo de telemetría apropiado.
2. Habilite la función de telemetría: `feature TELEMETRY`
3. Configure la inversión de telemetría si es necesario

Para **CRSF**, la telemetría se maneja automáticamente —, no se necesita un puerto separado.

## SmartPort (FrSky)

SmartPort requiere inversión de señal en procesadores F4. O:
- Utilice un controlador de vuelo con inversor incorporado
- Utilice SoftSerial con `set tlm_inversion = ON`

```
feature TELEMETRY
set tlm_inverted = ON
set tlm_halfduplex = ON
```z

## Datos de telemetría

OrniFlight transmite:
- voltaje VBAT (batería principal)
- Consumo de corriente / mAh consumido
- RSSI (intensidad de la señal)
- Modo de vuelo/estado de armado
- coordenadas GPS (si está equipado)
- Altitud/vario (si barómetro)
- perfil de vuelo ONDAS activo