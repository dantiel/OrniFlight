# Mezclador

El mezclador traduce las salidas del controlador de vuelo (alabeo, cabeceo, guiñada, aceleración) en señales de servo para su ornitóptero.

## Mezclador de ornitópteros

OrniFlight amplía el sistema mezclador de Betaflight con configuraciones específicas para ornitópteros. La batidora maneja:

- **Servos de ala**: convierte la salida PID en modulación de trazo de ala
- **Servos de cola** (opcional): controla las superficies del timón/elevador

## Tipos de mezcladores

| Mezclador | Caso de uso |
|-------|----------|
| **ORNITHOPTER** | Ornitóptero estándar de doble ala con 2 servos de ala |
| **ORNITHOPTER_4S** | Ornitóptero de 4 servos (control independiente del ala izquierda/derecha) |
| **ORNITHOPTER_TAIL** | Doble ala + elevador de cola + timón |

## Configuración del servo

Configurado en la pestaña **Servos** o vía CLI:

```
smix reverse 0 2 r       # Reverse servo 2
smix 0 0 0 100 0 0 100   # Servo 0: roll mixing
smix 1 1 1 100 0 0 100   # Servo 1: pitch mixing
```z

## Integración ONDAS

El mezclador funciona en conjunto con ONDAS (Sistema aerodinámico dinámico no lineal de Ornithopter):

- **Acelerador** → establece la amplitud del aleteo base
- **ONDA Cadence** → cambia la ventana de modulación dentro de cada trazo
- **ONDA Ferocity** → modifica la forma de onda del trazo (sinusoidal ↔ trapezoidal)
- **ONDA Balance** → corrección de simetría del ala izquierda/derecha

Para conocer la teoría detallada de ONDAS, consulte la [ONDAS Wiki](../wiki/ondas.html).

## configuración CLI

```
mixer = ORNITHOPTER
set servo_pwm_rate = 330     # Servo update frequency
set servo_center_pulse = 1500
set flap_spread = 20         # Wing angle amplitude in degrees
```z