# Modos de voo

Os modos são alternados por meio dos interruptores AUX em seu transmissor. Cada modo pode ser atribuído a um intervalo de canal AUX específico na guia **Modos** do configurador OrniFlight.

## Modos padrão

| Modo | Função |
|------|----------|
| **ARM** | Habilitar controle de vôo (motores/servos ativos) |
| **ANGLE** | A embarcação — de nível automático retorna ao nível quando os bastões são centralizados |
| **HORIZON** | Modo de ângulo híbrido — próximo ao centro, acro em full stick |
| **ACRO** | Zzz2zzz padrão sem nível automático, controle de taxa puro |
| **AIRMODE** | Mantém o loop PID ativo em aceleração zero para autoridade total |

## Modos específicos do OrniFlight

| ID | Modo | Função |
|----|------|----------|
| 50 | **INDEPENDENT** | Controle independente de asa — cada asa responde ao seu próprio canal servo |
| 51 | **GLIDE** | Modo de planeio — asas travadas na posição horizontal para voar alto |
| 52 | **PROFILE** | Seleção de perfil de voo — alternar entre 3 perfis PID/ONDAS |

## Modos Utilitários

| Modo | Função |
|------|----------|
| **BEEPER** | Ativar campainha para localização de aeronaves perdidas |
| **BLACKBOX** | Iniciar/parar o registro do Blackbox |
| **FAILSAFE** | Acionar manualmente o estágio de segurança 2 (interruptor de pânico) |
| **OSD** | Alternar exibição OSD |
| **TELEMETRY** | Ativar/desativar saída de telemetria |

## Notas sobre ornitópteros

- O modo **INDEPENDENT** é exclusivo do OrniFlight — e permite mapeamento de servo por asa para impulso assimétrico e controle diferencial da asa
O modo **GLIDE** mantém as asas na posição neutra, útil para subida térmica e descida com eficiência energética
- A comutação **PROFILE** permite alterações de parâmetros ONDAS durante o voo para diversas condições de voo (por exemplo, cruzeiro vs. manobras agressivas)