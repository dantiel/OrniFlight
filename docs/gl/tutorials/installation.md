# Instalación

Como instalar o firmware OrniFlight no seu controlador de voo.

## Requisitos previos

- **OrniFlight Configurator** (última versión)
- cable de datos USB (non só de carga)
- Placa controladora de voo compatible

## Tableros admitidos

| Xunta | Obxectivo | Flash | Notas |
|-------|---------|-------|--------|
| OMNIBUSF4 | `OMNIBUSF4` | 16 MB | STM32F405, MPU6000, OSD |
| TINYFISH | `TINYFISH` | 256 kB | STM32F411, MPU6000 |

## Pasos intermitentes

### 1. Acceda ao modo DFU/Bootloader

**OMNIBUSF4**: Mantén premido o botón BOOT mentres conectas USB. O vermello LED permanece firme — estás no modo DFU.

**TINYFISH**: Mantén premido o botón BOOT mentres conectas USB.

### 2. Flash a través do Configurador

1. Abre OrniFlight Configurator
2. Vaia á pestana **Firmware Flasher**
3. Seleccione o seu destino no menú despregable
4. Escolla a versión do firmware (recoméndase a última versión estable)
5. Fai clic en **Cargar firmware (en liña)** ou selecciona un ficheiro hexadecimal local
6. Fai clic en **Flash Firmware**
7. Agarde a "Programación: EXITOSA"

### 3. Primeira conexión

Despois de parpadear:
1. Desconecta e volve conectar USB (sen o botón BOOT)
2. O configurador debería conectarse automaticamente
3. Acepte o indicador "Aplicar valores predeterminados personalizados".
4. Verifique a información do taboleiro na pestana Configuración

## Solución de problemas

### Sen porto DFU

**macOS/Linux**: DFU debería aparecer automaticamente. Se non:
zz0zzz

**Windows**: Instale [Zadig](https://zadig.akeo.ie/) para substituír o controlador STM32 DFU:
1. Executar Zadig
2. Opcións → Listar todos os dispositivos
3. Seleccione "STM32 BOOTLOADER"
4. Substitúe o controlador por "WinUSB"

### Fallo de flash

- Proba cun cable USB diferente (con capacidade de datos, non só de carga)
- Proba cun porto USB diferente (directo, non concentrador)
- Mantén premido o botón BOOT durante todo o proceso de flash
- **OMNIBUSF4**: pode ser necesario borrar o chip completo — comprobar a opción "Borrar completo do chip"

### O configurador non se conectará

- Verifique que o cable USB sexa capaz de datos
- O taboleiro de verificación non está no modo DFU (LED parpadeando = modo normal)
- Reiniciar o configurador
- Proba un porto USB diferente

## CLI Flash (avanzado)

Para usuarios avanzados, flash a través de STM32CubeProgrammer ou st-flash:

zz1zzz

Despois de parpadear, verifique con:

zz2zzz