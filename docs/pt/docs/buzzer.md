# Campainha

OrniFlight suporta campainhas ativas para indicação sonora de status e localização de modelo perdido.

## Funções

- **Armar/Desarmar** tons distintos —
- **Bateria Fraca** — repetindo bipes de aviso
- **Failsafe** padrão — SOS
- **Modelo Perdido** — bipe contínuo via switch
- **GPS Fix** tom de confirmação — no bloqueio do satélite
- **Calibração** padrões de bipe — durante a calibração do giroscópio/aceleração
- **RX Sinal perdido** aviso — quando a conexão do receptor cai

## Hardware

- Conecte uma campainha ativa de 5 V (NÃO um piezo passivo) aos pads **BUZZ-** e **BUZZ+**
- A campainha é acionada por um transistor no FC —, nenhum driver externo é necessário para campainhas padrão

## CLI Configurações

```
beeper -GYRO_CALIBRATED     # Disable gyro calibration beeps
beeper -RX_LOST             # Enable receiver lost warning
beeper -ON_USB              # Disable beeper when USB connected
```

## Segurança de ornitópteros

O sinal sonoro é especialmente útil para ornitópteros grandes que podem pousar em grama alta ou folhagem. Configure o modo BEEPER em um switch momentâneo para ativação rápida quando necessário.