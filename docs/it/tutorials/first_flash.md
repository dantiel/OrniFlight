# Primo flash

> *Inserisci OrniFlight nel tuo controller di volo — passo dopo passo.*

## Cosa ti serve

- Controllore di volo basato su STM32F4 (OMNIBUSF4, TINYFISH, MATEKF405, ecc.)
-cavo USB
- [dfu-util](http://dfu-util.sourceforge.net/) o STM32CubeProgrammer
- file OrniFlight `.hex` dalla [pagina delle versioni](https://github.com/dantiel/OrniFlight/releases)

## Passaggio 1: entra nella modalità DFU

1. **Tieni premuto il pulsante BOOT** sul controller di volo
2. **Collega USB** tenendo premuto il pulsante
3. **Rilascia** dopo 2 secondi

Verifica su macOS/Linux:

```
dfu-util -l
```

Dovrebbe mostrare `Found DFU: [0483:df11]`

## Passaggio 2: flash

```
dfu-util -a 0 -D obj/orniflight_0.4.6_OMNIBUSF4.hex
```

## Passaggio 3: primo avvio

1. Scollega USB
2. Ricollega USB (non tenere BOOT)
3. Connettiti tramite il configuratore OrniFlight

## Passaggio 4: configurazione di base

Nel Configuratore:

1. **Scheda Porte**: Configura UART per il tuo ricevitore (Seriale RX)
2. **Scheda Configurazione**: selezionare il protocollo del ricevitore (si consiglia CRSF)
3. **Scheda Modalità**: imposta gli interruttori ARM, GLIDE/INDEPENDENT e PROFILE
4. **Scheda → ONDAS avanzata**: controlla le impostazioni predefinite, regola prima Cadence

## Risoluzione dei problemi

| Problema | Correzione |
|---------|-----|
| Dispositivo DFU non trovato | Prova un cavo USB diverso, controlla il pulsante BOOT |
| Flash non funziona | Controlla l'installazione di dfu-util, le autorizzazioni USB |
| Nessun avvio dopo il flash | Ripeti il ​​flash, verifica che l'esadecimale corrisponda al tuo target |
| Il configuratore non si connette | Controlla la porta COM e la velocità di trasmissione |

---

*Successivo: [Configurazione di base](basic_setup.html) →*