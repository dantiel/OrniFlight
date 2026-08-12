# Registro de caixa negra

Blackbox rexistra datos de voo para a análise, axuste e depuración posterior ao voo. OrniFlight admite o rexistro no chip flash integrado ou no dispositivo OpenLog externo.

## O que se rexistra

- **Gyro** — velocidade angular de 3 eixes en bruto e filtrada
- **Acelerómetro** — Aceleración de 3 eixes
- **PID Saída** — Contribucións P, I, D, F por eixe
- **ONDAS** — Cadence, Ferocity P/D e outros parámetros específicos de aleteo
- **Comandos RC** Posicións do stick — despois das tarifas/expo
- **Saída de servo** — saída final a cada canle de servo
- **Batería** — tensión e corrente por iteración
- **GPS** — posición, velocidade, altitude (se está dispoñible)

## Configuración

### Flash integrado (OMNIBUSF4)

O OMNIBUSF4 inclúe 16 MB de flash integrado para o rexistro de Blackbox. Activar no Configurador:

1. Pestana **Blackbox** → Establecer `Blackbox logging device` en `Onboard flash`
2. Establece a taxa de rexistro (recomendo: `1/N` con N=2-4 para obxectivos F4)
3. Asigne un interruptor para iniciar/deter o rexistro

### Externo OpenLog

Conecta OpenLog a un pin UART TX gratuíto:

1. Pestana **Portos** → Establece o UART en `Blackbox logging` a 115200 baudios
2. Conecta OpenLog: FC TX → OpenLog RX, máis 5V/GND

## Ferramentas de análise

- [Blackbox Explorer](https://github.com/betaflight/blackbox-log-viewer) — visor de rexistro baseado na web
- `blackbox_decode` — converte a CSV para unha análise personalizada

## ONDAS-Específico

Blackbox é esencial para axustar os parámetros ONDAS. Os datos ONDAS rexistrados inclúen:
- Temporización da ventá de modulación `ondas_cadence_phase` —
- `ondas_ferocity_p` / `ondas_ferocity_d` — compoñentes de empuxe asimétricos
- `ondas_balance` — equilibrio á esquerda/dereita
- Saída por servo en cada iteración

Isto permite unha análise precisa da mecánica do aleteo e as correccións da asimetría das ás.