# Primeiros passos

Bem-vindo ao OrniFlight! Este guia orienta você na configuração inicial do controlador de vôo do ornitóptero.

## O que você precisa

- **Configurador OrniFlight** download do — em [orniflight.org](https://orniflight.org)
- **cabo USB** — para conectar o controlador de vôo ao computador
- **Ornitóptero** com:
  - Controlador de voo compatível (OMNIBUSF4, TINYFISH)
  - Servos para acionamento das asas
  - Receptor vinculado ao seu transmissor
  - Bateria (2S–4S LiPo)

## Início rápido

### 1. Firmware Flash

1. Abra o **Configurador OrniFlight**
2. Vá para a guia **Firmware Flasher**
3. Selecione o alvo do seu tabuleiro (OMNIBUSF4 ou TINYFISH)
4. Escolha a versão estável mais recente
5. Clique em **Carregar Firmware** e depois em **Flash Firmware**

### 2. Configuração inicial

Depois de piscar, o Configurador solicitará que você aplique padrões personalizados. **Sempre aceite.**

### 3. Configuração do receptor

1. Vá para a guia **Portas** → e defina o UART correto como `Serial RX`
2. Vá para a guia **Configuração** → e selecione o protocolo do receptor (CRSF, SBUS, etc.)
3. Vá para a guia **Receptor** → para verificar se os movimentos do stick correspondem aos canais esperados
4. Defina os pontos finais do canal: 1000–2000 com 1500 centro

### 4. Configuração do Servo

1. Acesse a aba **Servos**
2. Verifique se o mapeamento do servo corresponde à configuração da asa do seu ornitóptero
3. Teste a direção do servo — reversa, se necessário
4. Defina a posição central (asas horizontais = 1500)

### 5. Configuração de modos

1. Vá para a guia **Modos**
2. Atribua ARM a um switch AUX
3. Atribua modos de voo (ANGLE / ACRO / HORIZON) conforme desejado
4. Atribua INDEPENDENT e GLIDE aos switches sobressalentes
5. Configure BEEPER para localização de modelo perdido

### 6. Primeiro vôo

1. **Desconecte a articulação da asa para testes de bancada**
2. Arme e verifique a direção do movimento do servo
3. Verifique a resposta do acelerador
4. Para o primeiro voo real: use o modo ANGLE, taxas baixas
5. Passe o mouse no nível dos olhos e corte conforme necessário

## Próximas etapas

- [Configuração básica](basic_setup.html) passo a passo detalhado da configuração do —
- [ajuste ONDAS](../../tutorials/ondas_tuning.html) — sintoniza a dinâmica de oscilação
- [PID Tuning](../../tutorials/tuning.html) — ajustar características de voo