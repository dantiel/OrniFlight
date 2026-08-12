#Primeiro Flash

> *Colocando OrniFlight em seu controlador de vôo — passo a passo.*

## O que você precisa

- controlador de vôo baseado em STM32F4 (OMNIBUSF4, TINYFISH, MATEKF405, etc.)
- cabo USB
- [dfu-util](http://dfu-util.sourceforge.net/) ou STM32CubeProgrammer
- arquivo OrniFlight `.hex` da [página de lançamentos](https://github.com/dantiel/OrniFlight/releases)

## Etapa 1: Entre no modo DFU

1. **Segure o botão BOOT** no seu controlador de vôo
2. **Conecte USB** enquanto segura o botão
3. **Solte** após 2 segundos

Verifique no macOS/Linux:

```
dfu-util -l
```

Deveria mostrar `Found DFU: [0483:df11]`

## Etapa 2: Flash

```
dfu-util -a 0 -D obj/orniflight_0.4.6_OMNIBUSF4.hex
```

## Etapa 3: primeira inicialização

1. Desconecte USB
2. Conecte USB novamente (não segure BOOT)
3. Conecte-se via configurador OrniFlight

## Etapa 4: configuração básica

No Configurador:

1. **Guia Portas**: Configure UART para seu receptor (Serial RX)
2. **Guia Configuração**: Selecione o protocolo do receptor (CRSF recomendado)
3. **Guia Modos**: Configure os interruptores ARM, GLIDE/INDEPENDENT e PROFILE
4. **Guia → ONDAS avançada**: revise os padrões, ajuste Cadence primeiro

## Solução de problemas

| Problema | Correção |
|--------|-----|
| dispositivo DFU não encontrado | Experimente um cabo USB diferente, verifique o botão BOOT |
| Flash falha | Verifique a instalação do dfu-util, permissões USB |
| Sem inicialização após flash | Flash novamente, verifique se o hexadecimal corresponde ao seu alvo |
| O configurador não conecta | Verifique a porta COM e a taxa de transmissão |

---

*Próximo: [Configuração básica](basic_setup.html) →*