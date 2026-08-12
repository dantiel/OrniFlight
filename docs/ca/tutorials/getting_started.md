# Primers passos

Benvingut a OrniFlight! Aquesta guia us guiarà per la configuració inicial del vostre controlador de vol ornitòpter.

## El que necessites

- **OrniFlight Configurator** baixada de — des de [orniflight.org](https://orniflight.org)
- **cable USB** — per connectar el controlador de vol a l'ordinador
- **Ornitòpter** amb:
  - Controlador de vol compatible (OMNIBUSF4, TINYFISH)
  - Servos per a l'accionament de les ales
  - Receptor vinculat al vostre transmissor
  - Bateria (2S–4S LiPo)

## Inici ràpid

### 1. Firmware Flash

1. Obriu **OrniFlight Configurator**
2. Aneu a la pestanya **Firmware Flasher**
3. Seleccioneu l'objectiu del vostre tauler (OMNIBUSF4 o TINYFISH)
4. Trieu la darrera versió estable
5. Feu clic a **Carga firmware** i després a **Firmware Flash**

### 2. Configuració inicial

Després de parpellejar, el configurador us demanarà que apliqueu els valors predeterminats personalitzats. **Accepteu sempre.**

### 3. Configuració del receptor

1. Aneu a la pestanya **Ports** → establiu el UART correcte a `Serial RX`
2. Aneu a la pestanya **Configuració** → seleccioneu el vostre protocol de receptor (CRSF, SBUS, etc.)
3. Aneu a la pestanya **Receptor** → comprova que els moviments de la palanca coincideixen amb els canals esperats
4. Establiu els punts finals del canal: 1000–2000 amb 1500 centre

### 4. Configuració del servo

1. Aneu a la pestanya **Servos**
2. Verifiqueu que el mapa del servo coincideixi amb la configuració de l'ala del vostre ornitòpter
3. Proveu la direcció del servo — inversa si cal
4. Estableix la posició central (ales horitzontals = 1500)

### 5. Configuració de modes

1. Aneu a la pestanya **Modes**
2. Assigna ARM a un interruptor AUX
3. Assigna els modes de vol (ANGLE / ACRO / HORIZON) com vulguis
4. Assigna INDEPENDENT i GLIDE als interruptors de recanvi
5. Configura BEEPER per localitzar el model perdut

### 6. Primer vol

1. **Desconnecteu l'enllaç de l'ala per a proves de banc**
2. Armeu i verifiqueu la direcció del moviment del servo
3. Comproveu la resposta de l'accelerador
4. Per al primer vol real: utilitzeu el mode ANGLE, tarifes baixes
5. Passeu el cursor a l'alçada dels ulls, retalleu-lo segons sigui necessari

## Següents passos

- [Configuració bàsica](basic_setup.html) — explicació detallada de la configuració
- [ONDAS Tuning](../../tutorials/ondas_tuning.html) — dinàmica de bateig de la melodia
- [PID Tuning](../../tutorials/tuning.html) — ajustar les característiques de vol