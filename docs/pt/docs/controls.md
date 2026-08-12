# Controles

OrniFlight usa mapeamento de stick RC padrão com extensões específicas para ornitópteros.

## Mapeamento de bastão

| Vara | Eixo | Efeito Primário |
|-------|------|---------------|
| Acelerador (esquerda, vertical) | Acelerador | Amplitude / impulso de oscilação |
| Guinada (esquerda, horizontal) | Guinada | Impulso diferencial da asa para giro |
| Inclinação (direita, vertical) | Argumento | Inclinação para frente/trás |
| Rolar (direita, horizontal) | Rolo | Banco esquerdo/direito |

## Modos de voo

| Modo | Comportamento da vara |
|------|---------------|
| **ACRO** | Sticks controlam taxa angular — sem nível automático |
| **ANGLE** | Mantém o ângulo de controle — no nível automático quando liberado |
| **HORIZON** | ANGLE próximo ao centro, ACRO em deflexão total |

ACRO é recomendado para pilotos experientes. ANGLE é bom para primeiros vôos e subidas térmicas.

## Controles específicos para ornitópteros

### Modo INDEPENDENT

Quando o modo INDEPENDENT está ativo, cada servo de asa responde de forma independente:
- **Controle esquerdo** servos da asa esquerda →
- **Controle direito** → servos da asa direita
- Permite bater assimétrico para manobras agressivas

### Modo GLIDE

O modo GLIDE bloqueia ambas as asas na posição horizontal. O ornitóptero vira planador:
- **Aceleração** não tem efeito na posição da asa
- **Pitch/Roll/Yaw** ainda influencia as superfícies de controle da cauda (se equipado)

### Troca de perfil

A troca de perfil em voo via canal AUX permite alterar os parâmetros PID/ONDAS durante o voo:
- **Perfil 1**: configurações de cruzeiro padrão
- **Perfil 2**: Configurações de alta agilidade
- **Perfil 3**: Configurações de eficiência/deslizamento

## Tarifas

Configure as taxas na aba **PID Tuning**. Para ornitópteros, comece com taxas conservadoras — a dinâmica de oscilação amplifica as entradas de controle:
- Taxa RC: 0,80–1,00
- Super Taxa: 0,60–0,70
- Expo: 0,20–0,40