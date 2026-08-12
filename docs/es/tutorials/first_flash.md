# Primer destello

> *Obtener OrniFlight en su controlador de vuelo — paso a paso.*

## Lo que necesitas

- Controlador de vuelo basado en STM32F4 (OMNIBUSF4, TINYFISH, MATEKF405, etc.)
- cable USB
- [dfu-util](http://dfu-util.sourceforge.net/) o STM32CubeProgrammer
- Archivo OrniFlight `.hex` de la [página de lanzamientos](https://github.com/dantiel/OrniFlight/releases)

## Paso 1: Ingrese al modo DFU

1. **Mantén presionado el botón BOOT** en tu controlador de vuelo
2. **Conecte USB** mientras mantiene presionado el botón
3. **Suelta** después de 2 segundos

Verificar en macOS/Linux:

```
dfu-util -l
```z

Debería mostrar `Found DFU: [0483:df11]`

## Paso 2: Flashear

```
dfu-util -a 0 -D obj/orniflight_0.4.6_OMNIBUSF4.hex
```z

## Paso 3: primer arranque

1. Desenchufe USB
2. Vuelva a enchufar USB (no mantenga presionado BOOT)
3. Conéctese a través del configurador OrniFlight

## Paso 4: Configuración básica

En el Configurador:

1. **Pestaña Puertos**: Configure UART para su receptor (Serial RX)
2. **Pestaña Configuración**: Seleccione el protocolo del receptor (se recomienda CRSF)
3. **Pestaña Modos**: configure los interruptores ARM, GLIDE/INDEPENDENT y PROFILE.
4. **Pestaña avanzada → ONDAS**: revise los valores predeterminados, ajuste Cadence primero

## Solución de problemas

| Problema | Arreglar |
|---------|-----|
| dispositivo DFU no encontrado | Pruebe un cable USB diferente, verifique el botón BOOT |
| El flash falla | Verifique la instalación de dfu-util, permisos USB |
| Sin arranque después del flash | Vuelva a flashear, verifique que el hexadecimal coincida con su objetivo |
| El configurador no se conecta | Verifique el puerto COM y la velocidad en baudios |

---

*Siguiente: [Configuración básica](basic_setup.html) →*