# Pirmā zibspuldze

> *Soli pa solim OrniFlight pievienošana lidojuma kontrolierim —.*

## Kas jums nepieciešams

- uz STM32F4 balstīts lidojuma kontrolieris (OMNIBUSF4, TINYFISH, MATEKF405 utt.)
- USB kabelis
- [dfu-util](http://dfu-util.sourceforge.net/) vai STM32CubeProgrammer
- OrniFlight `.hex` fails no [izlaidumu lapas](https://github.com/dantiel/OrniFlight/releases)

## 1. darbība: ieejiet DFU režīmā

1. **Turiet nospiestu BOOT pogu** uz lidojuma kontroliera
2. **Pieslēdziet USB**, turot pogu
3. **Atlaidiet** pēc 2 sekundēm

Pārbaudiet operētājsistēmā macOS/Linux:

```
dfu-util -l
```

Jārāda `Found DFU: [0483:df11]`

## 2. darbība. Zibspuldze

```
dfu-util -a 0 -D obj/orniflight_0.4.6_OMNIBUSF4.hex
```

## 3. darbība. Pirmā palaišana

1. Atvienojiet USB
2. Pieslēdziet USB atpakaļ (neturiet BOOT)
3. Izveidojiet savienojumu, izmantojot programmu OrniFlight Configurator

## 4. darbība: pamata konfigurācija

Konfiguratorā:

1. **Cilne Ports**: konfigurējiet UART savam uztvērējam (serial RX)
2. **Cilne Konfigurācija**: atlasiet uztvērēja protokolu (ieteicams CRSF)
3. **Cilne Režīmi**: iestatiet ARM, GLIDE/INDEPENDENT un PROFILE slēdžus.
4. **Papildu cilne → ONDAS**: pārskatiet noklusējuma iestatījumus, vispirms noregulējiet Cadence

## Traucējummeklēšana

| Problēma | Labot |
|---------|-----|
| DFU ierīce nav atrasta | Izmēģiniet citu USB kabeli, pārbaudiet pogu BOOT |
| Flash neizdodas | Pārbaudiet dfu-util instalāciju, USB atļaujas |
| Nav sāknēšanas pēc zibspuldzes | Atkārtoti mirgojiet, pārbaudiet, vai hex atbilst jūsu mērķim |
| Konfigurators nevar izveidot savienojumu | Pārbaudiet COM portu un datu pārraides ātrumu |

---

*Tālāk: [Pamata iestatīšana](basic_setup.html) →*