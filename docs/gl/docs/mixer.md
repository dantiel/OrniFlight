# Mesturador

O mesturador traduce as saídas do controlador de voo (rodamento, cabeceo, guiñada, aceleración) en sinais servo para o seu ornitóptero.

## Mesturador de ornitópteros

OrniFlight amplía o sistema de mestura de Betaflight con configuracións específicas de ornitópteros. O mesturador manexa:

- **Servos de ás**: converte a saída PID en modulación de golpe de á
- **Servos de cola** (opcional): Controla as superficies do elevador/temón

## Tipos de mesturadores

| Mesturador | Caso de uso |
|-------|----------|
| **ORNITHOPTER** | Ornitóptero estándar de dúas alas con servos de 2 ás |
| **ORNITHOPTER_4S** | Ornitóptero de 4 servos (control independente á esquerda/dereita) |
| **ORNITHOPTER_TAIL** | Dobre á + elevador de cola + temón |

## Configuración do servo

Configurado na pestana **Servos** ou mediante CLI:

zz0zzz

## ONDAS Integración

O mesturador funciona en concerto con ONDAS (Ornithopter Nonlinear Dynamic Aerodynamic System):

- **Acelerador** → establece a amplitude do aleteo da base
- **ONDA Cadence** → cambia a xanela de modulación dentro de cada trazo
- **ONDA Ferocity** → modifica a forma de onda do trazo (sinusoidal ↔ trapezoidal)
- **ONDA Balance** → corrección de simetría de á esquerda/dereita

Para obter unha teoría detallada sobre ONDAS, consulte a [ONDAS Wiki](../wiki/ondas.html).

## Configuración de CLI

zz1zzz