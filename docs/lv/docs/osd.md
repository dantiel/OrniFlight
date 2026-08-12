# Ekrāna displejs (OSD)

OrniFlight ietver iebūvētu OSD (ekrāna displeju), izmantojot MAX7456 vai AT7456E mikroshēmu. Zzz14zzz pārklāj lidojuma datus jūsu FPV video plūsmā.

## Atbalstītie elementi

Konfigurējiet elementus OrniFlight Configurator cilnē **OSD**. Velciet un nometiet elementus, lai novietotu tos ekrānā.

### Lidojuma dati

| Elements | Displeji |
|---------|-----------|
| Akumulatora spriegums | Galvenā akumulatora spriegums (piemēram, 14,8 V) |
| Vidējais šūnu spriegums | Spriegums uz vienu šūnu (piemēram, 3,7 V) |
| Pašreizējā izloze | Momentānie ampēri |
| mAh Drawn | Kumulatīvā patērētā jauda |
| RSSI | Signāla stiprums no uztvērēja |
| Lidojuma režīms | Pašreizējais režīms (INDEPENDENT, GLIDE utt.) |
| Droseles pozīcija | Pašreizējais droseles procents |
| Taimeris | Lidojuma laiks / bruņotais laiks |
| Amatniecības nosaukums | OrniFlight amatniecības nosaukums |

### Ornitopteram specifisks

| Elements | Displeji |
|----------|-----------|
| Pūšanas biežums | Pašreizējais spārna gājiena ātrums Hz |
| ONDAS Profils | Aktīvā lidojuma profila numurs (1-3) |
| Cadence Fāze | Strāvas modulācijas fāzes nobīde |
| Servo leņķis | Spārna servo stāvoklis |

## Fontu pārvaldība

Zzz18zzz izmanto uz rakstzīmēm balstītu displeja sistēmu. Zzz8zzz Configurator cilnē **OSD** ir iekļauts **Fontu pārvaldnieks** pielāgotu fontu un glifu augšupielādei.

## CLI iestatījumi

```
set osd_units = METRIC
set osd_warn_bitmask = 270335  # Warning flag bitmask
set osd_tim1 = 2560            # Timer 1 source
set osd_tim2 = 2561            # Timer 2 source
```

## Aparatūra

Pašlaik atbalstītā OSD mikroshēma: **AT7456E** (atrodas uz OMNIBUSF4 un saderīgām platēm). MAX7456 ir saderīgs un tiek automātiski noteikts.