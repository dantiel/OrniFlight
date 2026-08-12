# Primeiro flash

> *Conseguir OrniFlight no teu controlador de voo — paso a paso.*

## O que necesitas

- Controlador de voo baseado en STM32F4 (OMNIBUSF4, TINYFISH, MATEKF405, etc.)
- Cable USB
- [dfu-util](http://dfu-util.sourceforge.net/) ou STM32CubeProgrammer
- OrniFlight `.hex` ficheiro da [páxina de lanzamentos](https://github.com/dantiel/OrniFlight/releases)

## Paso 1: ingresa ao modo DFU

1. **Mantén premido o botón BOOT** no teu controlador de voo
2. **Conecta USB** mentres mantés presionado o botón
3. **Liberar** despois de 2 segundos

Verifique en macOS/Linux:

zz0zzz

Debe mostrar `Found DFU: [0483:df11]`

## Paso 2: Flash

zz1zzz

## Paso 3: primeiro arranque

1. Desenchufe USB
2. Volve conectar USB (non manteñas BOOT)
3. Conéctese mediante OrniFlight Configurator

## Paso 4: Configuración básica

No Configurador:

1. **Pestaña Portos**: configura UART para o teu receptor (serie RX)
2. **Pestaña Configuración**: seleccione o protocolo do receptor (recoméndase CRSF)
3. **Pestaña Modos**: configura os interruptores ARM, GLIDE/INDEPENDENT e PROFILE
4. **Pestana → ONDAS avanzada**: revisa os valores predeterminados, primeiro sintona Cadence

## Solución de problemas

| Problema | Fixar |
|----------|-----|
| Non se atopou o dispositivo DFU | Proba un cable USB diferente, verifica o botón BOOT |
| Flash falla | Comprobe a instalación de dfu-util, permisos USB |
| Sen arranque despois do flash | Volve a flashear, verifica que o hexadecimal coincida co teu obxectivo |
| O configurador non se conectará | Comproba o porto COM e a taxa de transmisión |

---

*Seguinte: [Configuración básica](basic_setup.html) →*