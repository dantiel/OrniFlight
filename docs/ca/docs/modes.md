# Modes de vol

Els modes es canvien mitjançant els interruptors AUX del vostre transmissor. Cada mode es pot assignar a un interval de canals AUX específic a la pestanya **Modes** del Configurador OrniFlight.

## Modes estàndard

| Mode | Funció |
|------|----------|
| **ARM** | Habilita el control de vol (motors/servos actius) |
| **ANGLE** | El nivell automàtic — craft torna al nivell quan els pals estan centrats |
| **HORIZON** | Mode d'angle híbrid — prop del centre, acro a tot el pal |
| **ACRO** | Per defecte — sense nivell automàtic, control de velocitat pur |
| **AIRMODE** | Manté el bucle PID actiu a l'acceleració zero per a tota l'autoritat |

## OrniFlight-Modes específics

| ID | Mode | Funció |
|----|------|-----------|
| 50 | **INDEPENDENT** | Control d'ala independent — cada ala respon al seu propi canal de servo |
| 51 | **GLIDE** | Mode de lliscament — ales bloquejades en posició horitzontal per volar |
| 52 | **PROFILE** | Selecció de perfils de vol — canviar entre 3 perfils PID/ONDAS |

## Modes d'utilitat

| Mode | Funció |
|------|----------|
| **BEEPER** | Activa el timbre per localitzar avions perduts |
| **BLACKBOX** | Inicia/atura el registre de Blackbox |
| **FAILSAFE** | Activar manualment l'etapa de seguretat 2 (interruptor de pànic) |
| **OSD** | Commuta la visualització OSD |
| **TELEMETRY** | Activa/desactiva la sortida de telemetria |

## Notes d'ornitòpters

- El mode **INDEPENDENT** és exclusiu de OrniFlight —, permet el mapeig de servo per ala per a l'empenta asimètrica i el control de l'ala diferencial
- El mode **GLIDE** manté les ales en posició neutra, útil per a l'elevació tèrmica i el descens energèticament eficient
- La commutació **PROFILE** permet canviar els paràmetres ONDAS durant el vol per a diferents condicions de vol (p. ex., creuer i maniobres agressives)