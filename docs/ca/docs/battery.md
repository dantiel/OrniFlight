# Monitorització de la bateria

OrniFlight controla la tensió de la bateria principal mitjançant el ADC (convertidor d'analògic a digital). Això permet avisos de bateria baixa mitjançant els patrons de timbres, d'estat LED i LED.

## Característiques

- Detecció automàtica del recompte de cèl·lules a la connexió (basada en les tensions mínimes/màx. de les cel·les)
- Avís de bateria baixa amb llindars configurables
- Detecció de corrent per al consum de mAh (si és compatible amb FC)
- Tensió mostrada en OSD i transmesa mitjançant telemetria

## Objectius compatibles

Tots els controladors de vol admesos (OMNIBUSF4, TINYFISH) inclouen el control VBAT mitjançant divisor de voltatge.

## Connexions

**COMPROVEU SEMPRE LA POLARITAT.** Mesureu les tensions esperades abans de connectar-vos. El voltatge incorrecte o la polaritat invertida destruirà el controlador de vol.

### OMNIBUSF4

Connecteu la bateria principal al coixinet VBAT. El divisor de tensió a bord gestiona fins a 6S directament.

### TINYFISH

VBAT s'encamina a través de l'entrada d'alimentació de la placa —, no cal una connexió separada.

## CLI Configuració

```
set vbat_min_cell_voltage = 330       # Minimum per-cell voltage (3.3V)
set vbat_max_cell_voltage = 430       # Maximum per-cell voltage (4.3V)
set vbat_warning_cell_voltage = 350   # Warning threshold (3.5V)
set battery_meter_type = ADC
set current_meter_type = ADC          # If current sensor available
```

## Seguretat

Les bateries LiPo mai s'han de descarregar per sota de 3,5 V per cel·la sota càrrega. Els llindars configurables de OrniFlight ajuden a garantir un funcionament segur i la longevitat de la bateria.