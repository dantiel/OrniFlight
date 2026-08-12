# Instalacija

Kako instalirati firmware OrniFlight na vaš kontroler leta.

## Preduvjeti

- **OrniFlight Configurator** (latest version)
- USB data cable (not charge-only)
- Supported flight controller board

## Podržane ploče

| Odbor | Cilj | Bljesak | Bilješke |
|-------|--------|-------|-------|
| OMNIBUSF4 | `OMNIBUSF4` | 16 MB | STM32F405, MPU6000, OSD |
| TINYFISH | `TINYFISH` | 256KB | STM32F411, MPU6000 |

## Koraci koji trepću

### 1. Enter DFU/Bootloader Mode

**OMNIBUSF4**: Držite gumb BOOT dok povezujete USB. Crveno LED ostaje čvrsto — u načinu ste DFU.

**TINYFISH**: Držite gumb BOOT dok povezujete USB.

### 2. Flash via Configurator

1. Open OrniFlight Configurator
2. Idite na karticu **Firmware Flasher**
3. Odaberite cilj s padajućeg izbornika
4. Odaberite verziju firmvera (preporučuje se najnovija stabilna)
5. Kliknite **Učitaj firmver (online)** ili odaberite lokalnu hex datoteku
6. Kliknite **Flash Firmware**
7. Wait for "Programming: SUCCESSFUL"

### 3. Prva veza

Nakon treptanja:
1. Odspojite i ponovno spojite USB (bez gumba BOOT)
2. Configurator should auto-connect
3. Prihvatite upit "Primijeni prilagođene zadane postavke".
4. Verify board info on Setup tab

## Rješavanje problema

### Nema priključka DFU

**macOS/Linux**: DFU bi se trebao pojaviti automatski. Ako ne:
```bash
# Check for DFU device
system_profiler SPUSBDataType | grep -A 10 STM
```

**Windows**: Instalirajte [Zadig](https://zadig.akeo.ie/) da biste zamijenili upravljački program STM32 DFU:
1. Pokrenite Zadig
2. Opcije → Popis svih uređaja
3. Odaberite "STM32 BOOTLOADER"
4. Zamijenite upravljački program sa "WinUSB"

### Flash ne uspijeva

- Pokušajte s drugim USB kabelom (podatkovnim, ne samo punim)
- Pokušajte s drugim USB priključkom (izravnim, ne čvorištem)
- Držite gumb BOOT tijekom cijelog procesa bljeskanja
- **OMNIBUSF4**: Možda će biti potrebno potpuno brisanje čipa — provjerite opciju "Potpuno brisanje čipa"

### Konfigurator se ne povezuje

- Provjerite je li USB kabel sposoban za prijenos podataka
- Provjerite nije li ploča u načinu DFU (LED treperi = normalan način)
- Ponovno pokrenite konfigurator
- Pokušajte s drugim USB portom

## CLI Flash (napredno)

Za napredne korisnike, flash preko STM32CubeProgrammera ili st-flash:

```bash
st-flash write orniflight_0.4.6_OMNIBUSF4.hex 0x08000000
```

Nakon treptanja potvrdite pomoću:

```bash
st-flash verify orniflight_0.4.6_OMNIBUSF4.hex 0x08000000
```