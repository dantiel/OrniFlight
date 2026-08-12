# Installation

Hur man installerar OrniFlight firmware på din flygkontroll.

## Förutsättningar

- **OrniFlight Configurator** (senaste versionen)
- USB datakabel (ej endast för laddning)
- Flygkontrollkort som stöds

## Anslagstavlor som stöds

| Styrelse | Mål | Flash | Anteckningar |
|-------|--------|-------|-------|
| OMNIBUSF4 | `OMNIBUSF4` | 16MB | STM32F405, MPU6000, OSD |
| TINYFISH | `TINYFISH` | 256KB | STM32F411, MPU6000 |

## Blinkande steg

### 1. Gå till DFU/Bootloader-läge

**OMNIBUSF4**: Håll ned BOOT-knappen medan du ansluter USB. Röd LED förblir solid — du är i DFU-läge.

**TINYFISH**: Håll ned BOOT-knappen medan du ansluter USB.

### 2. Flash via Configurator

1. Öppna OrniFlight Configurator
2. Gå till fliken **Firmware Flasher**
3. Välj ditt mål i rullgardinsmenyn
4. Välj firmwareversion (senaste stabila rekommenderas)
5. Klicka på **Load Firmware (Online)** eller välj en lokal hex-fil
6. Klicka på **Flash Firmware**
7. Vänta på "Programmering: Lyckad"

### 3. Första anslutningen

Efter att ha blinkat:
1. Koppla från och återanslut USB (utan BOOT-knapp)
2. Konfiguratorn ska anslutas automatiskt
3. Acceptera uppmaningen "Apply Custom Defaults".
4. Verifiera kortinformation på fliken Inställningar

## Felsökning

### Ingen DFU-port

**macOS/Linux**: DFU bör visas automatiskt. Om inte:
```bash
# Check for DFU device
system_profiler SPUSBDataType | grep -A 10 STM
```

**Windows**: Installera [Zadig](https://zadig.akeo.ie/) för att ersätta STM32 DFU-drivrutinen:
1. Kör Zadig
2. Alternativ → Lista alla enheter
3. Välj "STM32 BOOTLOADER"
4. Byt ut drivrutinen mot "WinUSB"

### Flash misslyckas

- Prova en annan USB-kabel (datakompatibel, inte endast laddning)
- Prova en annan USB-port (direkt, inte hubb)
- Håll ned BOOT-knappen under hela blixtprocessen
- **OMNIBUSF4**: Full chip-radering kan behövas — markera alternativet "Full Chip Erase"

### Konfiguratorn ansluter inte

- Kontrollera att USB-kabeln är datakompatibel
- Kontrollera att kortet inte är i DFU-läge (LED blinkar = normalt läge)
- Starta om Configurator
- Prova en annan USB-port

## CLI Flash (avancerat)

För avancerade användare, flasha via STM32CubeProgrammer eller st-flash:

```bash
st-flash write orniflight_0.4.6_OMNIBUSF4.hex 0x08000000
```

Efter att ha blinkat, verifiera med:

```bash
st-flash verify orniflight_0.4.6_OMNIBUSF4.hex 0x08000000
```