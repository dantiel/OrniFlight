# LED Faixa

OrniFlight suporta tiras endereçáveis WS2812/SK6812 LED para indicação de status e feedback visual.

## Configuração

As faixas LED são configuradas na guia **LED Strip** do configurador OrniFlight. Cada posição, cor e função do LED podem ser definidas individualmente.

## Funções

| Função | Efeito Visual |
|----------|-------------|
| Indicador de bateria | Gradiente de cor verde → amarelo → vermelho |
| RSSI | Exibição da intensidade do sinal |
| Estado do braço | Mudança de cor ao armar/desarmar |
| Modo de voo | Cores específicas do modo |
| Aviso | Padrões de intermitência para bateria fraca, à prova de falhas |
| Indicador de oscilação | Pulso na frequência de oscilação atual |
| Direção de Impulso | Mudança de cor indicando saída de rotação/inclinação/guinada |
| GPS | Bloqueio de satélite e direção inicial |

## Hardware

- LEDs WS2812 ou SK6812 RGB
- Conecte-se ao pad/pin **LED** em seu controlador de vôo
- LEDs de alimentação de um BEC (NÃO alimente de 3,3 V, — use 5 V)
- Para tiras longas (> 8 LEDs), conecte a alimentação de 5 V diretamente às baterias, não através do FC

## Uso de ornitóptero

O **Indicador de oscilação** é exclusivo dos LEDs OrniFlight — que pulsam em sincronia com a frequência do movimento da asa, fornecendo uma representação visual do ritmo de oscilação e ajudando a ajustar os parâmetros de cadência do ONDAS.