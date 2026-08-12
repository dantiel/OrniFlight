# Ricevitore (RX)

OrniFlight supporta più protocolli di ricezione per il controllo radio del tuo ornitottero.

## Protocolli supportati

| Protocollo | Digitare | Note |
|----------|------|-------|
| **CRSF** (Fuoco incrociato) | Seriale | Bassa latenza, telemetria, consigliata |
| **SBUS** | Seriale | Invertito, necessita di inverter su F4 |
| **IBUS** (FlySky) | Seriale | Non invertito, diretto UART |
| **PPM** | Analogico a filo singolo | 8ch, legacy, non consigliato |
| **SPEKTRUM** | Seriale | 1024/2048, vincolante via CLI |
| **FPORT** | Seriale | FrSky, combina RX+Telemetria |
| **GHST** (Fantasma) | Seriale | ImmersionRC, bassa latenza |

## Configurazione seriale RX

1. Collegare il ricevitore a un pin UART RX libero
2. Nel Configuratore → **Porte**: imposta UART su `Serial RX`
3. Nel Configuratore → **Configurazione**: selezionare il protocollo
4. Per SBUS su F4: abilita `set sbus_inversion = ON`

## CLI Configurazione rapida

```
feature RX_SERIAL
set serialrx_provider = CRSF
set serialrx_inverted = OFF
set serialrx_halfduplex = OFF
save
```

## A prova di errore

Configurare il failsafe del ricevitore in modo che il ricevitore non emetta **nessun impulso** in caso di perdita di segnale. Il controllore di volo lo rileverà e attiverà la propria procedura di failsafe. Vedere [Failsafe](failsafe.html) per la configurazione a livello FC.