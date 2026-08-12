# Telemetria

A telemetria envia dados de voo de OrniFlight para o transmissor de rádio —, tensão da bateria, corrente, coordenadas RSSI, GPS, altitude e muito mais.

## Protocolos Suportados

| Protocolo | Sistema de Rádio | Contagem de Fios |
|----------|------------|-----------|
| **CRSF** | Fogo cruzado / Tracer / ELRS | Integrado com RX (bidirecional) |
| **SmartPort** | FrSky | 1 fio (pino TX) |
| **HoTT** | Graupner | 1 fio (TX+TZ) |
| **IBUS** | FlySky | 1 fio (sensor TX) |
| **LTM** | Telemetria de Luz (MWP) | 1 fio (TX) |

## Configuração

1. No Configurador → **Portas**: defina o pino UART TX para o protocolo de telemetria apropriado
2. Habilite o recurso de telemetria: `feature TELEMETRY`
3. Configure a inversão de telemetria, se necessário

Para **CRSF**, a telemetria é tratada automaticamente —, não sendo necessária nenhuma porta separada.

## SmartPort (FrSky)

SmartPort requer inversão de sinal em processadores F4. Ou:
- Use um controlador de vôo com inversor embutido
- Use SoftSerial com `set tlm_inversion = ON`

```
feature TELEMETRY
set tlm_inverted = ON
set tlm_halfduplex = ON
```

## Dados de telemetria

OrniFlight transmite:
- tensão VBAT (bateria principal)
- Consumo atual / mAh consumido
- RSSI (intensidade do sinal)
- Modo de vôo / status do braço
- coordenadas GPS (se equipado)
- Altitude / vario (se barômetro)
- perfil de voo ONDAS ativo