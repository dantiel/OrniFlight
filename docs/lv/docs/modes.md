# Lidojuma režīmi

Režīmi tiek pārslēgti, izmantojot raidītāja AUX slēdžus. Katru režīmu var piešķirt noteiktam AUX kanālu diapazonam OrniFlight Configurator cilnē **Modes**.

## Standarta režīmi

| Režīms | Funkcija |
|------|----------|
| **ARM** | Iespējot lidojuma vadību (motori/servo aktīvi) |
| **ANGLE** | Automātiskā līmeņa — kuģis atgriežas līmenī, kad nūjas ir centrētas |
| **HORIZON** | Hibrīds — leņķa režīms tuvu centram, acro pie pilnas nūjas |
| **ACRO** | Noklusējuma — nav automātiskā līmeņa, tīra ātruma kontrole |
| **AIRMODE** | Uztur PID cilpu aktīvu pie nulles droseles, lai nodrošinātu pilnu autoritāti |

## OrniFlight-specifiskie režīmi

| ID | Režīms | Funkcija |
|----|------|----------|
| 50 | **INDEPENDENT** | Neatkarīga spārna vadība — katrs spārns reaģē uz savu servo kanālu |
| 51 | **GLIDE** | Slīdēšanas režīms — spārni fiksēti horizontālā stāvoklī, lai planētu |
| 52 | **PROFILE** | Lidojuma profila izvēle — pārslēgšanās starp 3 PID/ONDAS profiliem |

## Lietderīgie režīmi

| Režīms | Funkcija |
|------|----------|
| **BEEPER** | Aktivizēt zummeru, lai atrastu pazudušo lidaparātu |
| **BLACKBOX** | Sākt/apturēt Blackbox reģistrēšanu |
| **FAILSAFE** | Manuāli iedarbiniet 2. atteices posmu (panikas slēdzis) |
| **OSD** | Pārslēgt OSD displeju |
| **TELEMETRY** | Iespējot/atspējot telemetrijas izvadi |

## Ornitoptera piezīmes

- **INDEPENDENT** režīms ir unikāls OrniFlight —, tas nodrošina katra spārna servo kartēšanu asimetriskai vilces un diferenciāla spārnu kontrolei
- **GLIDE** režīms notur spārnus neitrālā stāvoklī, noder termiskai planēšanai un energoefektīvai nolaišanai
- **PROFILE** pārslēgšana ļauj lidojuma laikā mainīt ONDAS parametrus dažādos lidojuma apstākļos (piemēram, kruīza un agresīvas manevrēšanas gadījumā).