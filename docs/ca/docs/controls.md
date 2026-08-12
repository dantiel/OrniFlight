# Controls

OrniFlight utilitza un mapeig estàndard de RC amb extensions específiques d'ornitòpters.

## Mapes de pals

| Pal | Eix | Efecte primari |
|-------|-------|----------------|
| Acelerador (esquerra, vertical) | Acelerador | Amplitud de bateig / empenta |
| Guiada (esquerra, horitzontal) | Guia | Diferencial d'empenta d'ala per girar |
| Pas (Dreta, vertical) | Pitch | Inclinació cap endavant/enrere |
| Rotlla (Dreta, horitzontal) | Roll | Banca esquerra/dreta |

## Modes de vol

| Mode | Comportament del pal |
|------|----------------|
| **ACRO** | Els pals controlen la velocitat angular — sense nivell automàtic |
| **ANGLE** | Els pals controlen l'angle — autonivell quan s'alliberen |
| **HORIZON** | ANGLE a prop del centre, ACRO a la desviació total |

ACRO es recomana per a pilots experimentats. ANGLE és bo per als primers vols i per a la volada tèrmica.

## Controls específics per a ornitòpters

### Mode INDEPENDENT

Quan el mode INDEPENDENT està actiu, cada servo d'ala respon de manera independent:
- **Pasc esquerre** → servos de l'ala esquerra
- **Pasc dret** → servos de l'ala dreta
- Permet un aleteig asimètric per a maniobres agressives

### Mode GLIDE

El mode GLIDE bloqueja les dues ales en posició horitzontal. L'ornitòpter es converteix en un planador:
- **L'accelerador** no té cap efecte en la posició de l'ala
- **Pitch/Roll/Yaw** encara influeix en les superfícies de control de la cua (si està equipat)

### Canvi de perfil

El canvi de perfil durant el vol mitjançant el canal AUX permet canviar els paràmetres PID/ONDAS a mig vol:
- **Perfil 1**: Configuració estàndard del creuer
- **Perfil 2**: Configuració d'alta agilitat
- **Perfil 3**: Configuració d'eficiència/planament

## Tarifes

Configureu les tarifes a la pestanya **PID Tuning**. Per als ornitòpters, comenceu amb taxes conservadores — dinàmiques de flapping amplifiquen les entrades de control:
- Tarifa RC: 0,80–1,00
- Super tarifa: 0,60–0,70
- Expo: 0,20–0,40