# Receptor (RX)

OrniFlight suporta vários protocolos de receptor para controle de rádio do seu ornitóptero.

## Protocolos Suportados

| Protocolo | Tipo | Notas |
|----------|------|-------|
| **CRSF** (Fogo Cruzado) | Série | Baixa latência, telemetria, recomendada |
| **SBUS** | Série | Invertido, precisa de inversor no F4 |
| **IBUS** (FlySky) | Série | UART direto não invertido |
| **PPM** | Analógico de fio único | 8ch, legado, não recomendado |
| **SPEKTRUM** | Série | 1024/2048, vincular via CLI |
| **FPORT** | Série | FrSky, combina RX+Telemetria |
| **GHST** (Fantasma) | Série | ImmersionRC, baixa latência |

## Configuração serial RX

1. Conecte o receptor a um pino UART RX livre
2. No Configurador → **Portas**: defina UART como `Serial RX`
3. No Configurador → **Configuração**: selecione o protocolo
4. Para SBUS em F4: habilite `set sbus_inversion = ON`

## CLI Configuração rápida

```
feature RX_SERIAL
set serialrx_provider = CRSF
set serialrx_inverted = OFF
set serialrx_halfduplex = OFF
save
```

## À prova de falhas

Configure o receptor à prova de falhas para que o receptor **não emita pulsos** em caso de perda de sinal. O controlador de vôo detectará isso e ativará seu próprio procedimento à prova de falhas. Consulte [Failsafe](failsafe.html) para configuração no nível FC.