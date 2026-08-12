# Uzstādīšana

Kā instalēt OrniFlight programmaparatūru lidojuma kontrolierī.

## Priekšnoteikumi

- **OrniFlight Configurator** (jaunākā versija)
- USB datu kabelis (nav tikai maksas)
- Atbalstīta lidojuma vadības panelis

## Atbalstītie dēļi

| Valde | Mērķis | Zibspuldze | Piezīmes |
|-------|--------|-------|-------|
| OMNIBUSF4 | `OMNIBUSF4` | 16 MB | STM32F405, MPU6000, OSD |
| TINYFISH | `TINYFISH` | 256KB | STM32F411, MPU6000 |

## Mirgojoši soļi

### 1. Ievadiet DFU/Bootloader Mode

**OMNIBUSF4**: turiet nospiestu pogu BOOT, kamēr pievienojat USB. Sarkans LED paliek nemainīgs — jūs esat DFU režīmā.

**TINYFISH**: turiet pogu BOOT, kamēr pievienojat USB.

### 2. Flash, izmantojot konfiguratoru

1. Atveriet programmu OrniFlight Configurator
2. Atveriet cilni **Firmware Flasher**
3. Nolaižamajā izvēlnē atlasiet savu mērķi
4. Izvēlieties programmaparatūras versiju (ieteicama jaunākā stabilā versija)
5. Noklikšķiniet uz **Ielādēt programmaparatūru (tiešsaistē)** vai atlasiet lokālo hex failu
6. Noklikšķiniet uz **Flash programmaparatūra**.
7. Pagaidiet “Programmēšana: Veiksmīgi”

### 3. Pirmais savienojums

Pēc mirgošanas:
1. Atvienojiet un atkārtoti pievienojiet USB (bez pogas BOOT)
2. Konfiguratoram ir jāpievienojas automātiski
3. Pieņemiet uzvedni “Lietot pielāgotus noklusējumus”.
4. Pārbaudiet plates informāciju cilnē Iestatīšana

## Traucējummeklēšana

### Nav DFU porta

**macOS/Linux**: DFU jāparādās automātiski. Ja nē:
```bash
# Check for DFU device
system_profiler SPUSBDataType | grep -A 10 STM
```

**Windows**: instalējiet [Zadig](https://zadig.akeo.ie/), lai aizstātu STM32 DFU draiveri:
1. Palaidiet Zadigu
2. Opcijas → Visu ierīču saraksts
3. Atlasiet “STM32 BOOTLOADER”
4. Aizstāt draiveri ar "WinUSB"

### Flash neizdodas

- Izmēģiniet citu USB kabeli (ar datu pārraidi, nevis tikai uzlādi)
- Izmēģiniet citu USB portu (tiešo, nevis centrmezglu)
- Turiet BOOT pogu visa zibspuldzes procesa laikā
- **OMNIBUSF4**: var būt nepieciešams pilnībā dzēst mikroshēmu. — atzīmējiet opciju "Pilna mikroshēmu dzēšana".

### Konfigurators nevar izveidot savienojumu

- Pārbaudiet, vai USB kabelis ir datu spējīgs
- Pārbaudes dēlis nav DFU režīmā (LED mirgo = parastais režīms)
- Restartējiet konfiguratoru
- Izmēģiniet citu USB portu

## CLI Flash (uzlabots)

Pieredzējušiem lietotājiem zibspuldze, izmantojot STM32CubeProgrammer vai st-flash:

```bash
st-flash write orniflight_0.4.6_OMNIBUSF4.hex 0x08000000
```

Pēc mirgošanas pārbaudiet ar:

```bash
st-flash verify orniflight_0.4.6_OMNIBUSF4.hex 0x08000000
```