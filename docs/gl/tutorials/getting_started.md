# Comezando

Benvido a OrniFlight! Esta guía guíache pola configuración inicial do teu controlador de voo ornitóptero.

## O que necesitas

- **OrniFlight Configurator** — descarga de [orniflight.org](https://orniflight.org)
- **cable USB** — para conectar o controlador de voo ao ordenador
- **Ornitóptero** con:
  - Controlador de voo compatible (OMNIBUSF4, TINYFISH)
  - Servos para accionamento das ás
  - Receptor conectado ao teu transmisor
  - Batería (2S–4S LiPo)

## Inicio rápido

### 1. Firmware Flash

1. Abre **OrniFlight Configurator**
2. Vaia á pestana **Firmware Flasher**
3. Seleccione o destino do taboleiro (OMNIBUSF4 ou TINYFISH)
4. Escolla a última versión estable
5. Fai clic en **Cargar firmware** e logo en **Firmware Flash**

### 2. Configuración inicial

Despois de parpadear, o configurador pediralle que aplique os valores predeterminados personalizados. **Acepta sempre.**

### 3. Configuración do receptor

1. Vaia á pestana **Portos** → establece o UART correcto en `Serial RX`
2. Vai á pestana **Configuración** → e selecciona o teu protocolo de receptor (CRSF, SBUS, etc.)
3. Vai á pestana **Receptor** → verifica que os movementos do stick coincidan coas canles esperadas
4. Establecer puntos finais da canle: 1000–2000 con 1500 centro

### 4. Configuración do servo

1. Vaia á pestana **Servos**
2. Verifique que o mapeo do servo coincida coa configuración das ás do seu ornitóptero
3. Proba a dirección do servo — inversa se é necesario
4. Establece a posición central (alas horizontais = 1500)

### 5. Configuración de modos

1. Vaia á pestana **Modos**
2. Asigne ARM a un interruptor AUX
3. Asigna modos de voo (ANGLE / ACRO / HORIZON) segundo o desexe
4. Asigne INDEPENDENT e GLIDE aos interruptores de reserva
5. Configure BEEPER para a localización de modelos perdidos

### 6. Primeiro Voo

1. **Desconecte a conexión de á para probas en banco**
2. Arme e verifique a dirección do movemento do servo
3. Comprobe a resposta do acelerador
4. Para o primeiro voo real: utiliza o modo ANGLE, tarifas baixas
5. Pasa o rato á altura dos ollos, recorta segundo sexa necesario

## Seguintes pasos

- [Configuración básica](basic_setup.html) — guía de configuración detallada
- [ONDAS Tuning](../../tutorials/ondas_tuning.html) — tune dinámica de aleteo
- [PID Tuning](../../tutorials/tuning.html) — axustar as características de voo