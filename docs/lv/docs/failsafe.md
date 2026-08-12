# Neveiksmīgs

Zzz11zzz ir divpakāpju bezatteices sistēma, lai aizsargātu jūsu ornitopteri uztvērēja signāla zuduma gadījumā.

## Divpakāpju sistēma

### 1. posms — Atklāts signāla zudums

Aktivizēts, kad:
- Jebkuram lidojuma kanālam ir nederīgs impulsa garums
- Uztvērējs ziņo par nedrošības režīmu
- Nav signāla no uztvērēja konfigurētu laiku

**Darbība**: visi kanāli pārslēdzas uz atkāpšanās vērtībām (konfigurētas, izmantojot `rxfail`). Ja signāls atgriežas, sākas īss atkopšanas logs —, atsāksies normāls lidojums.

### 2. posms — Apsardzes laiks beidzies

Tiek ievadīts, ja 1. posms turpinās ilgāk par `failsafe_delay` (noklusējums: 400 ms) UN kuģis ir bruņots.

**Procedūras** (konfigurējama, izmantojot `failsafe_procedure`):

| Procedūra | Uzvedība |
|-----------|----------|
| **DROP** | Nekavējoties atbruņot — spārni apstājas, lidmašīna nolaižas |
| **LAND** | Slīdēšanas režīms — spārni bloķēti horizontāli, kontrolēta nolaišanās |

**LAND** ir ieteicamā procedūra ornitopteriem — tas notur spārnus neitrālā pozīcijā slīdošai nolaišanai, dodot laiku signāla atjaunošanai.

## CLI Iestatījumi

```
set failsafe_delay = 4         # Guard time in 0.1s (4 = 400ms)
set failsafe_procedure = LAND  # DROP or LAND
set failsafe_throttle = 1000   # Fallback throttle (low)
set failsafe_switch_mode = STAGE1  # Transmitter switch behavior
```

## Uztvērējs ir nedrošs

Konfigurējiet arī uztvērēja bezatteices režīmu, lai signāla zuduma gadījumā izvadītu **bez impulsiem**. Tas ļauj lidojuma kontrolierim noteikt zaudējumu un aktivizēt 1. posmu.

## Pārbaude

Pārbaudīt bezatteices **ar atvienotu spārnu savienojumu** uz stenda:
1. Piešķiriet slēdzim režīmu FAILSAFE
2. Apbruņojiet kuģi
3. Pārslēdziet slēdzi → novērot bezatteices procedūru
4. Pārbaudiet, vai servo darbība atbilst cerībām