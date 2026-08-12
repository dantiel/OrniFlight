# Monitoramento de bateria

OrniFlight monitora a tensão da bateria principal através do ADC (conversor analógico para digital). Isso permite avisos de bateria fraca por meio de padrões de campainha, status LED e faixa LED.

## Recursos

- Detecção automática da contagem de células na conexão (com base nas tensões mínimas/máximas das células)
- Aviso de bateria fraca com limites configuráveis
- Detecção de corrente para consumo de mAh (se compatível com FC)
- Tensão exibida em OSD e transmitida via telemetria

## Alvos Suportados

Todos os controladores de vôo suportados (OMNIBUSF4, TINYFISH) incluem monitoramento VBAT via divisor de tensão.

## Conexões

**SEMPRE VERIFIQUE A POLARIDADE.** Meça as tensões esperadas antes de conectar. Tensão incorreta ou polaridade invertida destruirão seu controlador de vôo.

### OMNIBUSF4

Conecte a bateria principal ao bloco VBAT. O divisor de tensão integrado suporta até 6S diretamente.

### TINYFISH

VBAT é roteado através da entrada de energia da placa —, não sendo necessária nenhuma conexão separada.

## CLI Configurações

```
set vbat_min_cell_voltage = 330       # Minimum per-cell voltage (3.3V)
set vbat_max_cell_voltage = 430       # Maximum per-cell voltage (4.3V)
set vbat_warning_cell_voltage = 350   # Warning threshold (3.5V)
set battery_meter_type = ADC
set current_meter_type = ADC          # If current sensor available
```

## Segurança

As baterias LiPo nunca devem ser descarregadas abaixo de 3,5 V por célula sob carga. Os limites configuráveis ​​do OrniFlight ajudam a garantir a operação segura e a longevidade da bateria.