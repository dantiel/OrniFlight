# Empezando

¡Bienvenido a OrniFlight! Esta guía lo guiará a través de la configuración inicial de su controlador de vuelo ornitóptero.

## Lo que necesitas

- **Configurador OrniFlight** descarga — desde [orniflight.org](https://orniflight.org)
- **cable USB** — para conectar el controlador de vuelo a la computadora
- **Ornitóptero** con:
  - Controlador de vuelo compatible (OMNIBUSF4, TINYFISH)
  - Servos para accionamiento de alas.
  - Receptor vinculado a su transmisor
  - Batería (2S–4S LiPo)

## Inicio rápido

### 1. Firmware flash

1. Abra **Configurador OrniFlight**
2. Vaya a la pestaña **Actualización de firmware**
3. Seleccione el objetivo de su tablero (OMNIBUSF4 o TINYFISH)
4. Elija la última versión estable
5. Haga clic en **Cargar firmware** y luego en **Actualizar firmware**

### 2. Configuración inicial

Después de parpadear, el Configurador le pedirá que aplique valores predeterminados personalizados. **Aceptar siempre.**

### 3. Configuración del receptor

1. Vaya a la pestaña **Puertos** → y configure el UART correcto en `Serial RX`.
2. Vaya a la pestaña **Configuración** → y seleccione el protocolo de su receptor (CRSF, SBUS, etc.)
3. Vaya a la pestaña **Receptor** → y verifique que los movimientos del joystick coincidan con los canales esperados.
4. Establecer puntos finales del canal: 1000–2000 con 1500 centro

### 4. Configuración del servo

1. Vaya a la pestaña **Servos**
2. Verifique que el mapeo de servos coincida con la configuración del ala de su ornitóptero
3. Pruebe la dirección del servo — en reversa si es necesario
4. Establecer la posición central (alas horizontales = 1500)

### 5. Configuración de modos

1. Vaya a la pestaña **Modos**
2. Asigne ARM a un conmutador AUX
3. Asigne modos de vuelo (ANGLE / ACRO / HORIZON) como desee
4. Asigne INDEPENDENT y GLIDE a interruptores de repuesto.
5. Configure BEEPER para localizar modelos perdidos

### 6. Primer vuelo

1. **Desconecte el varillaje del ala para realizar pruebas en banco**
2. Armar y verificar la dirección del movimiento del servo.
3. Verifique la respuesta del acelerador
4. Para el primer vuelo real: use el modo ANGLE, tarifas bajas
5. Coloca el cursor al nivel de los ojos y recorta según sea necesario.

## Próximos pasos

- [Configuración básica](basic_setup.html) tutorial de configuración detallado de —
- [afinación ONDAS](../../tutorials/ondas_tuning.html) dinámica de aleteo de melodía —
- [PID Tuning](../../tutorials/tuning.html) — ajusta las características de vuelo