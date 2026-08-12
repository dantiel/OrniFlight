# Registro de caixa preta

O Blackbox registra dados de voo para análise, ajuste e depuração pós-voo. OrniFlight suporta registro em chip flash integrado ou dispositivo OpenLog externo.

## O que é registrado

- **Gyro** — velocidade angular de 3 eixos bruta e filtrada
- **Acelerômetro** — aceleração de 3 eixos
- **Saída PID** — Contribuições P, I, D, F por eixo
- **ONDAS** — Cadence, Ferocity P/D e outros parâmetros específicos de oscilação
- **Comandos RC** — fixa posições após taxas/expo
- **Saída Servo** saída final — para cada canal servo
- **Bateria** tensão e corrente — por iteração
- **GPS** — posição, velocidade, altitude (quando disponível)

## Configuração

### Flash integrado (OMNIBUSF4)

O OMNIBUSF4 inclui flash integrado de 16 MB para registro no Blackbox. Habilite no configurador:

1. **Caixa preta** guia → Defina `Blackbox logging device` como `Onboard flash`
2. Defina a taxa de registro (recomendado: `1/N` com N = 2-4 para alvos F4)
3. Atribua uma opção para iniciar/parar o registro

### OpenLog externo

Conecte OpenLog a um pino UART TX gratuito:

1. Guia **Portas** → Defina UART como `Blackbox logging` a 115200 baud
2. Conecte OpenLog: FC TX → OpenLog RX, mais 5V/GND

## Ferramentas de análise

- [Blackbox Explorer](https://github.com/betaflight/blackbox-log-viewer) — visualizador de log baseado na web
- `blackbox_decode` — convertido para CSV para análise personalizada

## ONDAS-Específico

Blackbox é essencial para ajustar os parâmetros ONDAS. Os dados ONDAS registrados incluem:
- temporização da janela de modulação `ondas_cadence_phase` —
- `ondas_ferocity_p` / `ondas_ferocity_d` — componentes de impulso assimétricos
- `ondas_balance` — equilíbrio da asa esquerda/direita
- Saída por servo em cada iteração

Isto permite uma análise precisa da mecânica de oscilação e correções de assimetria das asas.