# Zumbador

OrniFlight admet timbres actius per a una indicació audible d'estat i la ubicació del model perdut.

## Funcions

- **Arma/Desarma** — tons diferents
- **Bateria baixa** — repetició de bips d'advertència
- **Patró de seguretat** — SOS
- **Model perdut** — so continu mitjançant l'interruptor
- **GPS Fix** — to de confirmació al bloqueig del satèl·lit
- **Calibració** — patrons de so durant la calibració del giroscopi/acceleració
- **RX Senyal perdut** — advertiment quan la connexió del receptor es caiguda

## Maquinari

- Connecteu un timbre actiu de 5 V (NO un piezoel·loqui passiu) als coixinets **BUZZ-** i **BUZZ+**
- El timbre és impulsat per un transistor al FC —, no cal un controlador extern per als timbres estàndard

## CLI Configuració

```
beeper -GYRO_CALIBRATED     # Disable gyro calibration beeps
beeper -RX_LOST             # Enable receiver lost warning
beeper -ON_USB              # Disable beeper when USB connected
```

## Seguretat dels ornitòpters

El beeper és especialment útil per a ornitòpters grans que poden aterrar a l'herba alta o al fullatge. Configureu el mode BEEPER en un interruptor momentani per activar-lo ràpidament quan sigui necessari.