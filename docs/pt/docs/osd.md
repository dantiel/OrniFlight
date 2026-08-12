# Exibição na tela (OSD)

OrniFlight inclui um OSD (exibição na tela) integrado usando o chip MAX7456 ou AT7456E. O OSD sobrepõe dados de voo ao feed de vídeo FPV.

## Elementos Suportados

Configure elementos na guia **OSD** do OrniFlight Configurator. Arraste e solte elementos para posicioná-los na tela.

### Dados de voo

| Elemento | Exibições |
|--------|----------|
| Tensão da bateria | Tensão da bateria principal (por exemplo, 14,8 V) |
| Tensão média da célula | Tensão por célula (por exemplo, 3,7 V) |
| Sorteio Atual | Amplificadores instantâneos |
| mAh Desenhado | Capacidade acumulada consumida |
| RSSI | Intensidade do sinal do receptor |
| Modo de voo | Modo atual (INDEPENDENT, GLIDE, etc.) |
| Posição do acelerador | Porcentagem atual de aceleração |
| Temporizador | Tempo de voo/tempo armado |
| Nome do ofício | nome da embarcação OrniFlight |

### Específico para ornitópteros

| Elemento | Exibições |
|----------|----------|
| Frequência de oscilação | Taxa atual de curso da asa em Hz |
| Perfil ONDAS | Número do perfil de voo ativo (1-3) |
| Fase Cadence | Deslocamento de fase de modulação atual |
| Servo Ângulo | Posição servo da asa |

## Gerenciamento de fontes

O OSD usa um sistema de exibição baseado em caracteres. A guia **OSD** do Configurador OrniFlight inclui um **Gerenciador de Fontes** para fazer upload de fontes e glifos personalizados.

## CLI Configurações

```
set osd_units = METRIC
set osd_warn_bitmask = 270335  # Warning flag bitmask
set osd_tim1 = 2560            # Timer 1 source
set osd_tim2 = 2561            # Timer 2 source
```

## Hardware

Chip OSD atualmente suportado: **AT7456E** (encontrado em OMNIBUSF4 e placas compatíveis). MAX7456 é compatível e detectado automaticamente.