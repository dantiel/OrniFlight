# Registre de Blackbox

Blackbox registra les dades de vol per a l'anàlisi, l'ajustament i la depuració després del vol. OrniFlight admet el registre al xip flash integrat o al dispositiu OpenLog extern.

## Què es registra

- **Gyro** — velocitat angular de 3 eixos en brut i filtrat
- **Acceleròmetre** — acceleració de 3 eixos
- **PID Sortida** — Contribucions P, I, D, F per eix
- **ONDAS** — Cadence, Ferocity P/D i altres paràmetres específics del bateig
- **Comandes RC** Posicions del pal — després de les tarifes/exposició
- **Sortida de servo** — sortida final a cada canal de servo
- **Bateria** tensió i corrent — per iteració
- **GPS** — posició, velocitat, altitud (quan estigui disponible)

## Configuració

### Flash integrat (OMNIBUSF4)

El OMNIBUSF4 inclou 16 MB de flaix integrat per al registre de Blackbox. Habilita al configurador:

1. Pestanya **Blackbox** → Estableix `Blackbox logging device` a `Onboard flash`
2. Establiu la taxa de registre (recomaneu: `1/N` amb N=2-4 per a objectius F4)
3. Assigna un interruptor per iniciar/aturar el registre

### Zzz36zzz extern

Connecteu OpenLog a un pin UART TX gratuït:

1. Pestanya **Ports** → Estableix el UART a `Blackbox logging` a 115200 bauds
2. Connecteu OpenLog: FC TX → OpenLog RX, més 5V/GND

## Eines d'anàlisi

- [Blackbox Explorer](https://github.com/betaflight/blackbox-log-viewer) — visualitzador de registres basat en web
- Converteix `blackbox_decode` — a CSV per a una anàlisi personalitzada

## ONDAS-Específic

Blackbox és essencial per ajustar els paràmetres ONDAS. Les dades registrades ONDAS inclouen:
- Temporització de la finestra de modulació `ondas_cadence_phase` —
- `ondas_ferocity_p` / `ondas_ferocity_d` — components d'empenta asimètrics
- `ondas_balance` — equilibri ala esquerra/dreta
- Sortida per servo a cada iteració

Això permet una anàlisi precisa de la mecànica del bateig i les correccions d'asimetria de les ales.