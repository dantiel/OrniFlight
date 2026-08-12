#RSSI

RSSI (Indicador de intensidade do sinal recibido) mostra a calidade da súa ligazón de radio. OrniFlight pode obter RSSI desde a entrada analóxica, os datos do receptor en serie ou o protocolo RSSI.

## RSSI Fontes

| Fonte | Conexión | Configuración |
|--------|-----------|----------------|
| **Protocolo de serie** | Ningún (sobre cable serie RX) | CRSF, GHST — automático |
| **Canle AUX** | Ningún (TX envía RSSI como canle) | `set rssi_channel = 8` |
| **Zzz25zzz analóxico** | RSSI almofada activada FC → Receptor RSSI fóra | `set rssi_adc_channel = 1` |

## Configuración

### Serie RSSI (CRSF/GHST/SBUS)

zz0zzz

RSSI transmítese automaticamente mediante protocolos en serie — sen necesidade de cableado adicional.

### Zzz32zzz analóxico

Connect receiver RSSI output → RSSI pad on flight controller:

zz1zzz

### AUX Canle RSSI

Configura o teu transmisor para enviar RSSI nunha canle específica e despois:

zz2zzz

## Pantalla

RSSI móstrase no OSD e pódese transmitir mediante telemetría á túa radio. Configurar limiares de aviso:

zz3zzz

## Rango de ornitópteros

Para os ornitópteros, RSSI é fundamental — que as alas aleatorias crean patróns de interferencia RF dinámicos. Monitoriza RSSI durante os voos de proba iniciais para verificar o rendemento fiable da ligazón en todas as posicións das ás.