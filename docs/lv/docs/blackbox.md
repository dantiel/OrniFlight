# Blackbox reģistrēšana

Blackbox ieraksta lidojuma datus pēclidojuma analīzei, regulēšanai un atkļūdošanai. OrniFlight atbalsta reģistrēšanu iebūvētajā zibatmiņas mikroshēmā vai ārējā OpenLog ierīcē.

## Kas tiek reģistrēts

- **Gyro** — neapstrādāts un filtrēts 3 asu leņķiskais ātrums
- **Akselerometrs** — 3 asu paātrinājums
- **PID izvade** — P, I, D, F ieguldījumi uz asi
- **ONDAS** — Cadence, Ferocity P/D un citi viļņošanai raksturīgi parametri
- **RC komandas** — nūju pozīcijas pēc likmēm/izstādes
- **Servo izeja** — galīgā izeja katram servo kanālam
- **Akumulators** — spriegums un strāva vienā iterācijā
- **GPS** — pozīcija, ātrums, augstums (ja pieejams)

## Iestatīšana

### iebūvētā zibatmiņa (OMNIBUSF4)

Zzz34zzz ietver 16 MB iebūvēto zibatmiņu Blackbox reģistrēšanai. Iespējot konfiguratorā:

1. **Blackbox** cilne → Iestatīt `Blackbox logging device` uz `Onboard flash`
2. Iestatiet reģistrēšanas ātrumu (ieteicams: `1/N` ar N=2-4 F4 mērķiem)
3. Piešķiriet slēdzi, lai sāktu/pārtrauktu reģistrēšanu

### Ārējais OpenLog

Savienojiet OpenLog ar bezmaksas UART TX tapu:

1. Cilne **Porti** → Iestatiet UART uz `Blackbox logging` pie 115 200 bodu
2. Savienojiet OpenLog: FC TX → OpenLog RX plus 5V/GND

## Analīzes rīki

- [Blackbox Explorer](https://github.com/betaflight/blackbox-log-viewer) — tīmekļa žurnālu skatītājs
- `blackbox_decode` — konvertējiet uz CSV pielāgotai analīzei

## ONDAS-specifiski

Blackbox ir būtiska ONDAS parametru regulēšanai. Reģistrētajos ONDAS datos ietilpst:
- `ondas_cadence_phase` — modulācijas loga laiks
- `ondas_ferocity_p` / `ondas_ferocity_d` — asimetriskas vilces komponentes
- `ondas_balance` — kreisā/labā spārna līdzsvars
- Per-servo izvade katrā iterācijā

Tas ļauj precīzi analizēt plivināšanas mehāniku un spārnu asimetrijas korekcijas.