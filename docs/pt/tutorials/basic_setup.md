# Configuração básica

> *Configure seu ornitóptero para o primeiro voo.*

## Lista de verificação pré-voo

Antes de mais nada:

- [] Controlador de vôo piscou com OrniFlight
- [] Receptor vinculado ao transmissor
- [ ] Servos conectados para corrigir as saídas PWM
- [] Bateria conectada (asas seguras!)

## Configuração do receptor

### CRSF (recomendado)

1. **Guia Portas**: Defina UART (por exemplo, UART1) como "Serial RX"
2. **Guia Configuração**: Modo Receptor = "Receptor baseado em serial", Provedor = "CRSF"
3. Desligue e ligue, verifique se as entradas do canal se movem na guia Receptor

### SBUS / Outro

Mesmo processo — selecione o protocolo apropriado na guia Configuração.

## Mapeamento Servo

Na **aba Servos**:

| Servo | Função | Taxa padrão |
|-------|----------|------------|
| Servo 0 | Ala Esquerda | 250 Hz |
| Servo 1 | Direita | 250 Hz |
| Servo2 | Crista/Leme | 50 Hz |

Ajuste min/max/meio para corresponder ao alcance do seu servo. Teste com "Override" para verificar a direção.

## Seleção do modo de voo

Na **guia Modos**:

1. **ARM**: Atribuir a um switch (segurança!)
2. **ORNITHOPTER INDEPENDENT** ou **ORNITHOPTER GLIDE**: Escolha seu modo de voo principal
3. **ORNITHOPTER PROFILE**: atribuição — opcional para troca de perfil em voo

## ONDAS Primeira Afinação

Vá para **subguia → ONDAS avançado**:

1. **Cadence Ganho**: Comece em 50 (meio). Este é o parâmetro mais importante.
2. **Ferocity D Gain**: Comece em 30. Esta é a sua estabilização primária.
3. **Ferocity P Ganho**: Comece em 20 para rolar/inclinar, 0 para guinada.
4. **Balance Ganho**: 0 (centralizado).

Conecte uma bateria, **prenda o ornitóptero com firmeza** e ARM. Observe o movimento do servo —, ele deve ser suave, oscilando senoidalmente.

## Primeiro voo

1. Comece com um movimento suave contra o vento
2. Use o modo GLIDE para uma sensação natural de subida
3. Use o modo INDEPENDENT quando desejar controle direto de frequência
4. Pouse, ajuste ONDAS, repita

---

*Próximo: [Guia de ajuste ONDAS](ondas_tuning.html) →*