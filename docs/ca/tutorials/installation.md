# Instal·lació

Com instal·lar el firmware OrniFlight al controlador de vol.

## Requisits previs

- **OrniFlight Configurator** (última versió)
- Cable de dades USB (no només de càrrega)
- Tauler de controlador de vol compatible

## Taulers admesos

| Junta | Objectiu | Flash | Notes |
|-------|---------|--------|--------|
| OMNIBUSF4 | `OMNIBUSF4` | 16 MB | STM32F405, MPU6000, OSD |
| TINYFISH | `TINYFISH` | 256 KB | STM32F411, MPU6000 |

## Passos intermitents

### 1. Entreu al mode DFU/Bootloader

**OMNIBUSF4**: manteniu premut el botó BOOT mentre connecteu USB. El vermell LED es manté sòlid —, estàs en mode DFU.

**TINYFISH**: manteniu premut el botó BOOT mentre connecteu USB.

### 2. Flaix mitjançant el configurador

1. Obriu OrniFlight Configurator
2. Aneu a la pestanya **Firmware Flasher**
3. Seleccioneu el vostre objectiu al menú desplegable
4. Trieu la versió del microprogramari (es recomana l'última estable)
5. Feu clic a **Carga firmware (en línia)** o seleccioneu un fitxer hexadecimal local
6. Feu clic a **Firmware Flash**
7. Espereu a "Programació: EXITOSA"

### 3. Primera connexió

Després de parpellejar:
1. Desconnecteu i torneu a connectar USB (sense el botó BOOT)
2. El configurador s'ha de connectar automàticament
3. Accepteu el missatge "Aplica els valors predeterminats personalitzats".
4. Verifiqueu la informació del tauler a la pestanya Configuració

## Resolució de problemes

### Sense port DFU

**macOS/Linux**: DFU hauria d'aparèixer automàticament. Si no:
```bash
# Check for DFU device
system_profiler SPUSBDataType | grep -A 10 STM
```

**Windows**: instal·leu [Zadig](https://zadig.akeo.ie/) per substituir el controlador STM32 DFU:
1. Executar Zadig
2. Opcions → Llista tots els dispositius
3. Seleccioneu "STM32 BOOTLOADER"
4. Substituïu el controlador per "WinUSB"

### Falla de flaix

- Proveu un cable USB diferent (apte per a dades, no només de càrrega)
- Proveu un port USB diferent (directe, no concentrador)
- Mantingueu premut el botó BOOT durant tot el procés de flaix
- **OMNIBUSF4**: és possible que es necessiti esborrat complet del xip — comproveu l'opció "Esborrat complet del xip"

### El configurador no es connecta

- Verifiqueu que el cable USB sigui capaç de dades
- El tauler de comprovació no està en mode DFU (LED parpellejant = mode normal)
- Reinicieu el configurador
- Proveu un port USB diferent

## CLI Flash (avançat)

Per a usuaris avançats, flasheu mitjançant STM32CubeProgrammer o st-flash:

```bash
st-flash write orniflight_0.4.6_OMNIBUSF4.hex 0x08000000
```

Després de parpellejar, comproveu amb:

```bash
st-flash verify orniflight_0.4.6_OMNIBUSF4.hex 0x08000000
```