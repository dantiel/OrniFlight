# Trasmettitore video (VTX)

OrniFlight supporta il controllo VTX per gli ornitotteri FPV. I moduli VTX possono essere configurati tramite OrniFlight Configurator, MSP o CLI — impostando banda, canale, livello di potenza e modalità pit.

## Protocolli supportati

1. **IRC Tramp** — Comune sui moduli VTX piccoli, ideale per ornitotteri FPV leggeri
2. **TBS SmartAudio** — Protocollo digitale con supporto modalità pit
3. **RTC6705** — Controllo diretto SPI su schede con VTX integrato (es. SPRACINGF3NEO)

##Configurazione

Le impostazioni di VTX sono gestite tramite la scheda **VTX** nel Configuratore OrniFlight o tramite CLI:

```
set vtx_band = 5           # Raceband
set vtx_channel = 1        # 5658 MHz
set vtx_power = 2          # 200mW
set vtx_low_power_disarm = ON  # Lower power when disarmed
set vtx_pit_mode_freq = 0  # Pit mode frequency (0 = disabled)
```

## Porta seriale

Il controllo VTX richiede un pin UART TX dedicato. Configura la porta nella scheda **Porte** con la periferica `IRC Tramp` o `TBS SmartAudio`.

## FPV Considerazioni sugli ornitotteri

- Il peso è fondamentale — scegli moduli VTX leggeri (Tramp Nano, Eachine Nano)
- Montaggio dell'antenna: garantire la distanza dalle ali che sbattono
- Filtraggio alimentazione: collega l'alimentazione VTX dopo il filtro LC per evitare il rumore del servo nel video
- La modalità Pit è consigliata per i test al banco per evitare il surriscaldamento dei piccoli moduli VTX