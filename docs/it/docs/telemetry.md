# Telemetria

La telemetria invia i dati di volo da OrniFlight al trasmettitore radio —, tensione della batteria, corrente, coordinate RSSI, GPS, altitudine e altro.

## Protocolli supportati

| Protocollo | Sistema radio | Conteggio fili |
|----------|-------------|------------|
| **CRSF** | Fuoco incrociato / Tracciante / ELRS | Integrato con RX (bidirezionale) |
| **SmartPort** | FrSky | 1 filo (pin TX) |
| **HoTT** | Graupner | 1 filo (TX+TZ) |
| **IBUS** | FlySky | 1 filo (sensore TX) |
| **LTM** | Telemetria leggera (MWP) | 1 filo (TX) |

##Configurazione

1. Nel Configuratore → **Porte**: imposta il pin UART TX sul protocollo di telemetria appropriato
2. Abilita la funzione di telemetria: `feature TELEMETRY`
3. Configurare l'inversione della telemetria, se necessario

Per **CRSF**, la telemetria viene gestita automaticamente —, non è necessaria una porta separata.

## SmartPort (FrSky)

SmartPort richiede l'inversione del segnale sui processori F4. O:
- Utilizzare un controller di volo con inverter integrato
- Usa SoftSerial con `set tlm_inversion = ON`

```
feature TELEMETRY
set tlm_inverted = ON
set tlm_halfduplex = ON
```

## Dati di telemetria

OrniFlight trasmette:
- tensione VBAT (batteria principale)
- Corrente assorbita/mAh consumati
- RSSI (potenza del segnale)
- Modalità di volo/stato del braccio
- coordinate GPS (se in dotazione)
- Altitudine/vario (se barometro)
- Profilo volo ONDAS attivo