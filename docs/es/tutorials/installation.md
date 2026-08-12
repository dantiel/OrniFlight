# Instalación

Cómo instalar el firmware OrniFlight en su controlador de vuelo.

## Requisitos previos

- **Configurador OrniFlight** (última versión)
- cable de datos USB (no solo de carga)
- Placa controladora de vuelo compatible

## Tableros compatibles

| tablero | Objetivo | Destello | Notas |
|-------|--------|-------|-------|
| OMNIBUSF4 | `OMNIBUSF4` | 16MB | STM32F405, MPU6000, OSD |
| TINYFISH | `TINYFISH` | 256 KB | STM32F411, MPU6000 |

## Pasos intermitentes

### 1. Ingrese al modo DFU/cargador de arranque

**OMNIBUSF4**: Mantenga presionado el botón BOOT mientras conecta USB. El rojo LED permanece fijo — estás en modo DFU.

**TINYFISH**: Mantenga presionado el botón BOOT mientras conecta USB.

### 2. Flash a través del Configurador

1. Abra el configurador OrniFlight
2. Vaya a la pestaña **Actualización de firmware**
3. Seleccione su objetivo en el menú desplegable.
4. Elija la versión del firmware (se recomienda la última versión estable)
5. Haga clic en **Cargar firmware (en línea)** o seleccione un archivo hexadecimal local.
6. Haga clic en **Firmware flash**
7. Espere a "Programación: EXITOSA"

### 3. Primera conexión

Después de flashear:
1. Desconecte y vuelva a conectar USB (sin botón BOOT)
2. El configurador debe conectarse automáticamente
3. Acepte el mensaje "Aplicar valores predeterminados personalizados"
4. Verifique la información del tablero en la pestaña Configuración

## Solución de problemas

### Sin puerto DFU

**macOS/Linux**: DFU debería aparecer automáticamente. Si no:
```bash
# Check for DFU device
system_profiler SPUSBDataType | grep -A 10 STM
```z

**Windows**: Instale [Zadig](https://zadig.akeo.ie/) para reemplazar el controlador STM32 DFU:
1. Corre Zadig
2. Opciones → Listar todos los dispositivos
3. Seleccione "STM32 BOOTLOADER"
4. Reemplace el controlador con "WinUSB"

### El flash falla

- Pruebe con un cable USB diferente (con capacidad para datos, no solo para carga)
- Pruebe con un puerto USB diferente (directo, no concentrador)
- Mantenga presionado el botón BOOT durante todo el proceso de flasheo.
- **OMNIBUSF4**: Es posible que sea necesario borrar todo el chip — marque la opción "Borrado completo del chip"

### El configurador no se conecta

- Verifique que el cable USB tenga capacidad para datos
- Verifique que la placa no esté en modo DFU (LED parpadeando = modo normal)
- Reiniciar configurador
- Pruebe un puerto USB diferente

## CLI Flash (avanzado)

Para usuarios avanzados, flashee mediante STM32CubeProgrammer o st-flash:

```bash
st-flash write orniflight_0.4.6_OMNIBUSF4.hex 0x08000000
```z

Después del flasheo, verificar con:

```bash
st-flash verify orniflight_0.4.6_OMNIBUSF4.hex 0x08000000
```