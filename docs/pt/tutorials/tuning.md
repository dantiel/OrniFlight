# PID Ajuste

OrniFlight usa um controlador PID (Proporcional-Integral-Derivativo) adaptado para vôo com asas batendo. O ajuste difere significativamente das aeronaves convencionais devido à natureza periódica do empuxo oscilante.

## Ornitóptero PID Noções básicas

Ao contrário das aeronaves convencionais, onde o empuxo é quase contínuo, o empuxo do ornitóptero oscila a cada golpe de asa. Isso cria:

- **Ondulação de impulso** na frequência de oscilação (normalmente 5–15 Hz)
- **Autoridade de controle dependente de fase** — a mesma saída PID tem efeito diferente dependendo de onde no ciclo de curso ela é aplicada
- **Dinâmica de rotação e guinada acoplada** O empuxo assimétrico da asa — afeta ambos os eixos simultaneamente

## PID Termos

| Prazo | Efeito | Nota sobre ornitóptero |
|------|--------|-----------------|
| **P** | Correção imediata — proporcional | Use valores conservadores; oscilação é oscilante síncrona |
| **Eu** | Correção de erro persistente — integral | Essencial para manter a atitude durante os planeios |
| **D** | Derivada — amortece oscilações | Ajustado à taxa de curso da asa, não às oscilações do quadro |
| **Foda-se** | Feed-forward — direto stick-to-output | Útil para resposta nítida no eixo de rotação |

## Valores iniciais

Para um ornitóptero de tamanho médio (1–1,5 m de envergadura):

| Eixo | P | eu | D | F |
|------|---|---|---|---|
| Rolo | 25 | 30 | 15 | 30 |
| Argumento | 30 | 35 | 20 | 35 |
| Guinada | 40 | 35 | 10 | 20 |

## Procedimento de ajuste

### 1. Avalie o ajuste primeiro

Antes de ajustar o PID, defina taxas que sejam confortáveis:
- Comece com RC Taxa 0,90, Super Taxa 0,65, Expo 0,30
- Ajuste de acordo com seu estilo de vôo e tamanho do ornitóptero

### 2. Ganho P

Aumente P até ver a oscilação na frequência de oscilação e, em seguida, diminua 20%:
- Oscilação de rotação: oscilação da asa na taxa de curso
- Oscilação de passo: balanço para frente e para trás
- Oscilação de guinada: abanar a cauda sincronizado com os golpes

### 3. Ganho D

Aumente D para amortecer o retorno após movimentos bruscos do stick:
- Demais: servo jitter, superaquecimento
- Muito pouco: toque após parar o roll/pitch

### 4. Eu ganho

Eu ganho desvio persistente de contadores:
- Aumente até que a deriva seja eliminada
- Demais: oscilação lenta a 1–2 Hz (abaixo da taxa de oscilação)

## Integração ONDAS

ONDAS (Ornithopter Nonlinear Dynamic Aerodynamic System) modula a saída PID dentro de cada golpe de asa. Após o ajuste básico do PID:

1. Defina **Cadence Gain** — muda a janela de modulação para a fase aerodinamicamente ideal
2. Defina **Ferocity P** — impulso de impulso assimétrico imediato
3. Definir **Ferocity D** — exploração antecipada de arrasto
4. Ajuste **Balance** — simetria da asa esquerda/direita

Consulte o [Guia de ajuste ONDAS](ondas_tuning.html) para obter procedimentos detalhados.

## Análise de caixa preta

Ative o registro do Blackbox para visualizar o desempenho do PID. Procure:
- **Oscilação do termo P** na frequência de oscilação → reduz P
- **Encerramento do termo I** durante curvas sustentadas → reduz I ou aumenta o relaxamento do termo I
- **Ruído de termo D** da vibração → verifique primeiro o equilíbrio mecânico e depois reduza D

## Perfis de voo

OrniFlight suporta 3 perfis de voo comutáveis durante o voo:

| Perfil | Caso de uso |
|--------|----------|
| 1 | Cruzeiro padrão |
| 2 | Alta agilidade/agressividade |
| 3 | Eficiência / elevação térmica |