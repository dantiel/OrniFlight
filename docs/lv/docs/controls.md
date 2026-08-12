# Vadības ierīces

OrniFlight izmanto standarta RC nūju kartēšanu ar ornitopteram raksturīgiem paplašinājumiem.

## Stick Mapping

| Stick | Ass | Primārais efekts |
|-------|------|----------------|
| Droseļvārsts (pa kreisi, vertikāli) | Droseļvārsts | Svārstīšanās amplitūda / vilces spēks |
| Leņķis (pa kreisi, horizontāli) | Žāga | Diferenciālā spārna vilce pagriešanai |
| Solis (pa labi, vertikāli) | Piķis | Noliekt uz priekšu/atpakaļ |
| Roll (pa labi, horizontāli) | Roll | Kreisā/labā mala |

## Lidojuma režīmi

| Režīms | Nūjas uzvedība |
|------|----------------|
| **ACRO** | Spieķi kontrolē leņķisko ātrumu — bez automātiskā līmeņa |
| **ANGLE** | Spieķi vadības leņķis — automātiskais līmenis, kad tas tiek atlaists |
| **HORIZON** | ANGLE tuvu centram, ACRO pie pilnas novirzes |

ACRO ieteicams pieredzējušiem pilotiem. ANGLE ir piemērots pirmajiem lidojumiem un termiskai planēšanai.

## Ornitopteram specifiskās vadības ierīces

### INDEPENDENT režīms

Kad INDEPENDENT režīms ir aktīvs, katrs spārna servo reaģē neatkarīgi:
- **Kreisā svira** → kreisā spārna servo
- **Labā nūja** → labā spārna servo
- Nodrošina asimetrisku plivināšanu agresīviem manevriem

### GLIDE režīms

GLIDE režīms bloķē abus spārnus horizontālā stāvoklī. Ornitopteris kļūst par planieri:
- **Drosele** neietekmē spārnu stāvokli
- **Slīpums/Pavirzīšanās/Pavirzīšanās** joprojām ietekmē astes vadības virsmas (ja ir aprīkojumā)

### Profila maiņa

Profila pārslēgšana lidojuma laikā caur AUX kanālu ļauj mainīt PID/ONDAS parametrus lidojuma laikā:
- **Profils 1**: standarta kruīza iestatījumi
- **2. profils**: augstas veiklības iestatījumi
- **3. profils**: efektivitātes/slīdēšanas iestatījumi

## Likmes

Konfigurējiet tarifus cilnē **PID Tuning**. Ornitopteriem sāciet ar konservatīviem rādītājiem. — plivināšanas dinamika pastiprina vadības ievades:
- RC Likme: 0,80–1,00
- Super Rate: 0,60–0,70
- Expo: 0,20–0,40