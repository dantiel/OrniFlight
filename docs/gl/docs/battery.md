# Monitorización da batería

OrniFlight monitoriza a tensión da batería principal a través do ADC (conversor de analóxico a dixital). Isto permite avisos de batería baixa mediante zumbadores, estados LED e LED.

## Características

- Detección automática do reconto de células ao conectar (en función das tensións mínimas/máximas das células)
- Aviso de batería baixa con limiares configurables
- Detección de corrente para o consumo de mAh (se é compatible con FC)
- Tensión mostrada en OSD e transmitida por telemetría

## Obxectivos admitidos

Todos os controladores de voo compatibles (OMNIBUSF4, TINYFISH) inclúen monitorización VBAT mediante divisor de voltaxe.

## Conexións

**COMPROBAR SEMPRE A POLARIDADE.** Mida as tensións esperadas antes de conectar. A tensión incorrecta ou a polaridade invertida destruirá o seu controlador de voo.

### OMNIBUSF4

Conecte a batería principal ao VBAT pad. O divisor de voltaxe integrado manexa ata 6S directamente.

### TINYFISH

VBAT envíase a través da entrada de alimentación do taboleiro — non é necesaria unha conexión separada.

## CLI Configuración

zz0zzz

## Seguridade

As baterías LiPo nunca deben descargarse por debaixo de 3,5 V por cela baixo carga. Os limiares configurables de OrniFlight axudan a garantir un funcionamento seguro e a lonxevidade da batería.