# PID Afinació

OrniFlight utilitza un controlador PID (Proporcional-Integral-Derivat) adaptat per al vol d'ala batedora. L'ajustament difereix significativament dels avions convencionals a causa de la naturalesa periòdica de l'empenta de l'aleteig.

## Ornithopter PID Conceptes bàsics

A diferència dels avions convencionals on l'empenta és gairebé contínua, l'empenta de l'ornitòpter oscil·la amb cada cop d'ala. Això crea:

- **Ondulació d'empenta** a freqüència de bateig (normalment 5–15 Hz)
- **Autoritat de control depenent de la fase** — la mateixa sortida PID té un efecte diferent depenent del lloc on s'aplica al cicle de traç
- **Dinàmica de guidada acoblada** — l'empenta de l'ala asimètrica afecta els dos eixos simultàniament

## PID Condicions

| Termini | Efecte | Nota de l'ornitòpter |
|------|---------|------------------|
| **P** | Correcció immediata — proporcional | Utilitzar valors conservadors; l'oscil·lació és aleteig-sincrònic |
| **jo** | Correcció d'errors persistents integral — | Imprescindible per mantenir l'actitud durant els lliscaments |
| **D** | La derivada — esmorteeix les oscil·lacions | Ajustat a la velocitat de carrera de l'ala, no a les oscil·lacions del quadre |
| **F** | Feed-forward — enganxament directe a la sortida | Útil per a una resposta nítida a l'eix de rodatge |

## Valors inicials

Per a un ornitòpter de mida mitjana (1–1,5 m d'envergadura):

| Eix | P | jo | D | F |
|------|---|---|---|---|
| Roll | 25 | 30 | 15 | 30 |
| Pitch | 30 | 35 | 20 | 35 |
| Guia | 40 | 35 | 10 | 20 |

## Procediment d'afinació

### 1. Ajustar la tarifa primer

Abans de la sintonització de PID, establiu tarifes que us resultin còmodes:
- Comenceu amb RC Tarifa 0,90, Super Tarifa 0,65, Expo 0,30
- Ajusteu el vostre estil de vol i la mida de l'ornitòpter

### 2. Guany P

Augmenteu P fins que vegeu una oscil·lació a la freqüència de bateig i, a continuació, retrocediu un 20%:
- Oscil·lació de gir: oscil·lació de l'ala a la velocitat de carrera
- Oscil·lació del to: balanceig de proa-popa
- Oscil·lació de guiñada: moviment de la cua sincronitzat amb els cops

### 3. D Guany

Augmenteu D per esmorteir el rebot després d'introduir un pal afilat:
- Massa: agitació del servo, sobreescalfament
- Massa poc: sons després de les parades de gir o de llançament

### 4. Guanyo

Guanyo comptadors de deriva persistent:
- Augmentar fins que s'elimini la deriva
- Massa: oscil·lació lenta a 1–2 Hz (per sota de la velocitat de bateig)

## ONDAS Integració

ONDAS (sistema aerodinàmic dinàmic no lineal d'ornitòpters) modula la sortida PID dins de cada cop d'ala. Després de l'afinació bàsica de PID:

1. Estableix **Cadence Gain** — canvia la finestra de modulació a la fase aerodinàmicament òptima
2. Estableix **Ferocity P** — impuls d'empenta asimètric immediat
3. Estableix **Ferocity D** — l'explotació d'arrossegament anticipada
4. Afina **Balance** — la simetria de l'ala esquerra/dreta

Vegeu [ONDAS Tuning Guide](ondas_tuning.html) per obtenir un procediment detallat.

## Anàlisi Blackbox

Activeu el registre de Blackbox per visualitzar el rendiment de PID. Busca:
- **Oscil·lació del terme P** a la freqüència de bateig → redueix P
- **I-term windup** durant girs sostinguts → redueix I o augmenta I-term relax
- **Soroll a termini D** de la vibració → primer comproveu l'equilibri mecànic i després reduïu D

## Perfils de vol

OrniFlight admet 3 perfils de vol commutables a mig vol:

| Perfil | Cas d'ús |
|---------|----------|
| 1 | Creuer estàndard |
| 2 | Alta agilitat / agressiu |
| 3 | Eficiència / elevació tèrmica |