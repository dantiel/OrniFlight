#GPS

GPS permite o mantemento da posición, o retorno á casa e a navegación baseada en telemetría para o teu ornitóptero. As funcións de GPS en OrniFlight son funcionais pero consideradas — experimentais sempre voan dentro da liña de visión visual.

## Protocolos admitidos

- **UBLOX** (recomendado) — Protocolo binario UBlox, eficiente e fiable
- **NMEA** — Protocolo estándar baseado en texto

## Hardware

- Módulos BN-880, BN-220 ou similar UBlox M8N GPS+Compass
- Conectar: TX/RX a un UART gratuíto, ademais de 5V/GND
- Monte GPS lonxe dos cables de alimentación e dos cables de servo para minimizar as interferencias
- O compás/magnetómetro debe estar lonxe de fontes magnéticas (fíos de alimentación, servos)

## Configuración

zz0zzz

1. Asigne o porto serie a GPS na pestana **Portos** (predeterminado 115200 baudios para UBlox)
2. Activa a función GPS
3. Establecer provedor
4. Garda e reinicia

## Elementos OSD

Os datos GPS mostrados en OSD inclúen:
- Conta de satélites e tipo de arranxo
- coordenadas GPS (lat/lon)
- Velocidade marcha
- Altitude (GPS)
- Distancia da casa
- Frecha de dirección de inicio

## Consideracións sobre os ornitópteros

- A antena GPS debe ter vista do ceo despexado — A localización de montaxe é fundamental con ás que batan
- A penalización de peso é significativa en pequenos ornitópteros
- GPS asistido por RTH (Volver á páxina de inicio) require un axuste coidadoso dos valores PID de navegación para a dinámica do voo aleteo