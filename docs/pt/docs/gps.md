#GPS

GPS permite manter posição, retornar para casa e navegação baseada em telemetria para seu ornitóptero. Os recursos do GPS no OrniFlight são funcionais, mas considerados experimentais, o — sempre voa dentro da linha de visão visual.

## Protocolos Suportados

- **UBLOX** (recomendado) — Protocolo binário UBlox, eficiente e confiável
- **NMEA** — Protocolo padrão baseado em texto

## Hardware

- BN-880, BN-220 ou módulos UBlox M8N GPS + Compass semelhantes
- Conecte: TX/RX a um UART grátis, mais 5V/GND
- Monte o GPS longe de fios de alimentação e cabos servo para minimizar a interferência
- A bússola/magnetômetro deve estar longe de fontes magnéticas (fios de alimentação, servos)

## Configuração

```
feature GPS
set gps_provider = UBLOX
set gps_sbas_mode = AUTO
set gps_auto_baud = ON
set gps_ublox_use_galileo = ON
```

1. Atribua a porta serial a GPS na guia **Portas** (padrão 115200 baud para UBlox)
2. Habilite o recurso GPS
3. Definir provedor
4. Salve e reinicie

## Elementos OSD

Os dados GPS exibidos em OSD incluem:
- Contagem de satélites e tipo de correção
- coordenadas GPS (lat/lon)
- Velocidade de solo
- Altitude (GPS)
- Distância de casa
- Seta de direção inicial

## Considerações sobre ornitópteros

- A antena GPS deve ter visão clara do céu. O local de montagem do — é crítico com asas batendo
- A penalidade de peso é significativa em pequenos ornitópteros
- RTH assistido por GPS (Return to Home) requer ajuste cuidadoso dos valores de navegação PID para dinâmica de voo oscilante