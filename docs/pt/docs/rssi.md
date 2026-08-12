#RSSI

RSSI (Indicador de intensidade do sinal recebido) mostra a qualidade do seu link de rádio. OrniFlight pode obter RSSI a partir de entrada analógica, dados do receptor serial ou protocolo RSSI.

## RSSI Fontes

| Fonte | Conexão | Configuração |
|--------|-----------|---------------|
| **Protocolo serial** | Nenhum (pelo fio serial RX) | CRSF, GHST — automático |
| **Canal AUX** | Nenhum (TX envia RSSI como canal) | `set rssi_channel = 8` |
| **Analógico ADC** | RSSI pad em FC → Receptor RSSI saída | `set rssi_adc_channel = 1` |

## Configuração

### Série RSSI (CRSF/GHST/SBUS)

```
set rssi_src_frame_errors = OFF
set rssi_scale = 100
set rssi_offset = 0
```

RSSI é transmitido automaticamente pelos protocolos seriais —, sem necessidade de fiação extra.

### Analógico RSSI

Conecte a saída do receptor RSSI → RSSI pad no controlador de vôo:

```
set rssi_adc_channel = 1      # Use ADC channel 1
set rssi_scale = 100          # Scale to 0-100%
set rssi_offset = 0
```

### AUX Canal RSSI

Configure seu transmissor para enviar RSSI em um canal específico e então:

```
set rssi_channel = 12         # Aux channel number
set rssi_scale = 100
set rssi_offset = 0
```

## Exibição

RSSI é mostrado no OSD e pode ser transmitido via telemetria para o seu rádio. Configure limites de aviso:

```
set osd_rssi_alarm = 20        # Warning at 20% RSSI
```

## Gama de ornitópteros

Para ornitópteros, RSSI é crítico. O bater de asas — cria padrões de interferência RF dinâmicos. Monitore o RSSI durante os voos de teste iniciais para verificar o desempenho confiável do link em todas as posições das asas.