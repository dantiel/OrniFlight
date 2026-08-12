# Installazione

Come installare il firmware OrniFlight sul tuo controller di volo.

## Prerequisiti

- **OrniFlight Configuratore** (ultima versione)
- Cavo dati USB (non solo per ricarica)
- Scheda controller di volo supportata

## Schede supportate

| Consiglio | Obiettivo | Flash | Note |
|-------|--------|-------|-------|
| OMNIBUSF4 | `OMNIBUSF4` | 16MB | STM32F405, MPU6000, OSD |
| TINYFISH | `TINYFISH` | 256KB | STM32F411, MPU6000 |

## Passaggi lampeggianti

### 1. Accedere alla modalità DFU/Bootloader

**OMNIBUSF4**: tieni premuto il pulsante BOOT mentre colleghi USB. Il rosso LED rimane fisso — sei in modalità DFU.

**TINYFISH**: tieni premuto il pulsante BOOT mentre colleghi USB.

### 2. Flash tramite configuratore

1. Apri il configuratore OrniFlight
2. Vai alla scheda **Firmware Flasher**
3. Seleziona il tuo target dal menu a discesa
4. Scegli la versione del firmware (si consiglia l'ultima versione stabile)
5. Fare clic su **Carica firmware (online)** o selezionare un file esadecimale locale
6. Fare clic su **Firmware Flash**
7. Attendere "Programmazione: SUCCESSFUL"

### 3. Prima connessione

Dopo aver lampeggiato:
1. Scollegare e ricollegare USB (senza pulsante BOOT)
2. Il configuratore dovrebbe connettersi automaticamente
3. Accettare il messaggio "Applica impostazioni predefinite personalizzate".
4. Verificare le informazioni sulla scheda nella scheda Configurazione

## Risoluzione dei problemi

### Nessuna porta DFU

**macOS/Linux**: DFU dovrebbe apparire automaticamente. In caso contrario:
```bash
# Check for DFU device
system_profiler SPUSBDataType | grep -A 10 STM
```

**Windows**: Installa [Zadig](https://zadig.akeo.ie/) per sostituire il driver STM32 DFU:
1. Esegui Zadig
2. Opzioni → Elenca tutti i dispositivi
3. Seleziona "STM32 BOOTLOADER"
4. Sostituisci il driver con "WinUSB"

### Flash non funziona

- Prova un cavo USB diverso (con funzionalità dati, non di sola ricarica)
- Prova una porta USB diversa (diretta, non hub)
- Tieni premuto il pulsante BOOT durante il processo di flash
- **OMNIBUSF4**: Potrebbe essere necessaria la cancellazione completa del chip. — seleziona l'opzione "Cancellazione completa del chip"

### Il configuratore non si connette

- Verificare che il cavo USB sia compatibile con i dati
- La scheda di controllo non è in modalità DFU (LED lampeggiante = modalità normale)
- Riavviare il configuratore
- Prova una porta USB diversa

## CLI Flash (Avanzato)

Per gli utenti avanzati, esegui il flash tramite STM32CubeProgrammer o st-flash:

```bash
st-flash write orniflight_0.4.6_OMNIBUSF4.hex 0x08000000
```

Dopo il flashing verificare con:

```bash
st-flash verify orniflight_0.4.6_OMNIBUSF4.hex 0x08000000
```