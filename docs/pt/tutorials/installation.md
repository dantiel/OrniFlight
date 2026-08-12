# Instalação

Como instalar o firmware OrniFlight em seu controlador de vôo.

## Pré-requisitos

- **Configurador OrniFlight** (versão mais recente)
- cabo de dados USB (não apenas para carga)
- Placa controladora de vôo suportada

## Placas suportadas

| Conselho | Alvo | Flash | Notas |
|-------|--------|-------|-------|
| OMNIBUSF4 | `OMNIBUSF4` | 16 MB | STM32F405, MPU6000, OSD |
| TINYFISH | `TINYFISH` | 256 KB | STM32F411, MPU6000 |

## Etapas intermitentes

### 1. Entre no modo DFU/Bootloader

**OMNIBUSF4**: Segure o botão BOOT enquanto conecta o USB. Vermelho LED permanece sólido — você está no modo DFU.

**TINYFISH**: Segure o botão BOOT enquanto conecta o USB.

### 2. Flash via configurador

1. Abra o configurador OrniFlight
2. Vá para a guia **Firmware Flasher**
3. Selecione seu alvo no menu suspenso
4. Escolha a versão do firmware (recomendado o último estável)
5. Clique em **Carregar Firmware (Online)** ou selecione um arquivo hexadecimal local
6. Clique em **Firmware Flash**
7. Aguarde "Programação: SUCESSO"

### 3. Primeira conexão

Depois de piscar:
1. Desconecte e reconecte USB (sem botão BOOT)
2. O configurador deve se conectar automaticamente
3. Aceite o prompt "Aplicar padrões personalizados"
4. Verifique as informações da placa na guia Configuração

## Solução de problemas

### Sem porta DFU

**macOS/Linux**: DFU deve aparecer automaticamente. Se não:
```bash
# Check for DFU device
system_profiler SPUSBDataType | grep -A 10 STM
```

**Windows**: Instale [Zadig](https://zadig.akeo.ie/) para substituir o driver STM32 DFU:
1. Execute o Zadig
2. Opções → Listar todos os dispositivos
3. Selecione "STM32 BOOTLOADER"
4. Substitua o driver por “WinUSB”

### Flash falha

- Experimente um cabo USB diferente (com capacidade de dados, não apenas para carga)
- Experimente uma porta USB diferente (direta, não hub)
- Segure o botão BOOT durante todo o processo de flash
- **OMNIBUSF4**: Pode ser necessário apagar completamente o chip — marque a opção "Apagar completamente o chip"

### O configurador não conecta

- Verifique se o cabo USB é compatível com dados
- Verifique se a placa não está no modo DFU (LED piscando = modo normal)
- Reinicie o configurador
- Experimente uma porta USB diferente

## CLI Flash (Avançado)

Para usuários avançados, atualize via STM32CubeProgrammer ou st-flash:

```bash
st-flash write orniflight_0.4.6_OMNIBUSF4.hex 0x08000000
```

Depois de piscar, verifique com:

```bash
st-flash verify orniflight_0.4.6_OMNIBUSF4.hex 0x08000000
```