# Prikaz na zaslonu (OSD)

OrniFlight uključuje ugrađeni OSD (On-Screen Display) pomoću MAX7456 ili AT7456E čipa. Zzz14zzz prekriva podatke o letu na vaš FPV video feed.

## Podržani elementi

Konfigurirajte elemente u kartici **OSD** OrniFlight konfiguratora. Povucite i ispustite elemente kako biste ih pozicionirali na zaslonu.

### Podaci o letu

| Element | Prikazuje |
|---------|----------|
| Napon baterije | Napon glavne baterije (npr. 14,8 V) |
| Prosječni napon ćelije | Napon po ćeliji (npr. 3,7 V) |
| Trenutno izvlačenje | Trenutačna pojačala |
| mAh iscrtano | Kumulativni potrošeni kapacitet |
| RSSI | Jačina signala iz prijemnika |
| Način letenja | Trenutačni način rada (INDEPENDENT, GLIDE, itd.) |
| Položaj leptira za gas | Trenutačni postotak gasa |
| Odbrojavanje | Vrijeme leta / vrijeme naoružanja |
| Naziv obrta | OrniFlight naziv obrta |

### Specifično za ornitopter

| Element | Prikazuje |
|----------|----------|
| Frekvencija lepršanja | Trenutačna brzina zamaha krila u Hz |
| ONDAS Profil | Broj profila aktivnog leta (1-3) |
| Cadence faza | Trenutni fazni pomak modulacije |
| Servo kut | Položaj servo krila |

## Upravljanje fontovima

Zzz18zzz koristi sustav prikaza temeljen na znakovima. Kartica **OSD** konfiguratora OrniFlight uključuje **Upravitelj fontova** za učitavanje prilagođenih fontova i glifova.

## CLI Postavke

```
set osd_units = METRIC
set osd_warn_bitmask = 270335  # Warning flag bitmask
set osd_tim1 = 2560            # Timer 1 source
set osd_tim2 = 2561            # Timer 2 source
```

## Hardver

Trenutačno podržan OSD čip: **AT7456E** (nalazi se na OMNIBUSF4 i kompatibilnim pločama). MAX7456 je kompatibilan i automatski se detektira.