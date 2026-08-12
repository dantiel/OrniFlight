# Misturador

O mixer traduz as saídas do controlador de vôo (rolagem, inclinação, guinada, aceleração) em sinais servo para o seu ornitóptero.

## Misturador Ornitóptero

OrniFlight estende o sistema de mixagem do Betaflight com configurações específicas para ornitópteros. O misturador controla:

- **Servos de asa**: Converta a saída PID em modulação de curso de asa
- **Servos de cauda** (opcional): controla as superfícies do elevador/leme

## Tipos de mixagem

| Misturador | Caso de uso |
|-------|----------|
| **ORNITHOPTER** | Ornitóptero padrão de asa dupla com 2 servos de asa |
| **ORNITHOPTER_4S** | Ornitóptero de 4 servos (controle independente das asas esquerda/direita) |
| **ORNITHOPTER_TAIL** | Asa dupla + elevador de cauda + leme |

## Configuração Servo

Configurado na aba **Servos** ou via CLI:

```
smix reverse 0 2 r       # Reverse servo 2
smix 0 0 0 100 0 0 100   # Servo 0: roll mixing
smix 1 1 1 100 0 0 100   # Servo 1: pitch mixing
```

## Integração ONDAS

O mixer funciona em conjunto com ONDAS (Ornithopter Nonlinear Dynamic Aerodynamic System):

- **Throttle** → define a amplitude de oscilação da base
- **ONDA Cadence** → muda a janela de modulação dentro de cada golpe
- **ONDA Ferocity** → modifica a forma da forma de onda do curso (senoidal ↔ trapezoidal)
- **ONDA Balance** → correção de simetria da asa esquerda/direita

Para uma teoria ONDAS detalhada, consulte o [ONDAS Wiki](../wiki/ondas.html).

## CLI Configurações

```
mixer = ORNITHOPTER
set servo_pwm_rate = 330     # Servo update frequency
set servo_center_pulse = 1500
set flap_spread = 20         # Wing angle amplitude in degrees
```