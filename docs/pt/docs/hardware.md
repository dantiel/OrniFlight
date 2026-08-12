#Hardware Suportado

OrniFlight é executado em controladores de voo comuns STM32F3/F4/F7. A linha de base é **STM32F3** — qualquer alvo F3 com pinos de temporizador com capacidade de servo voará.

## Controladores de vôo

| Conselho | MCU | IMU | Flash | Receptor | Estado |
|-------|-----|-----|-------|----------|--------|
| **TINYFISH** | STM32F303 | MPU6000 (SPI) | 256 KB | FrSky D8 (integrado) | ✅ Primário |
| **OMNIBUSF4** | STM32F405 | MPU6000 (SPI) | 1 MB + 16 MB SPI | — | ✅ Suportado |

### TINYFISH — O alvo OrniFlight mais leve

Projetado por fishpepper, TINYFISH é o controlador de vôo de ornitóptero ideal: leve, baseado em F3 e carregando um **receptor FrSky D8 integrado** a bordo. Sem RX externo, sem fiação extra — apenas alimentação, servos e voo.

- **MCU**: STM32F303CCT6 @ 72 MHz
- **Giroscópio**: MPU6000 (SPI, compatível com 8 kHz)
- **Flash**: 256 KB no chip
- **RAM**: 40 KB
- **Receptor**: FrSky D8 integrado (SBUS roteado internamente para UART2)
- **UARTs**: VCP + 2 UARTs de hardware (UART1 gratuito para o complemento GPS/CRSF)
- **Entrada**: 2-4S LiPo (potência direta do servo)
**Peso**: ~2,5 g

TINYFISH prova que o controle de oscilação transcendente não precisa de um F7. O STM32F303 executa o pipeline ONDAS completo — 10 canais de modulação, asa trapezoidal ODE, 4 perfis de voo — dentro de 256 KB.

### OMNIBUSF4 — O burro de carga acessível

O clássico alvo F4. Barato, onipresente, completo com OSD e amplo flash SPI para registro em Blackbox. A escolha certa para desenvolvimento e construções maiores.

- **MCU**: STM32F405RGT6 @ 168 MHz
- **Giroscópio**: MPU6000 (SPI, compatível com 8 kHz)
- **Flash**: 1 MB no chip + 16 MB SPI (caixa preta)
- **RAM**: 192 KB
- **OSD**: AT7456E (compatível com MAX7456)
- **UARTs**: VCP + 5 UARTs de hardware
- **Barômetro**: BMP280 (algumas variantes)
- **Entrada**: 2-6S LiPo

---

## Anatomia do Ornitóptero

### Servos de Asa

OrniFlight controla a oscilação através dos servos PWM. Especificações principais:

| Parâmetro | Faixa típica |
|-----------|--------------|
| Largura de pulso | 500–2500 µs |
| Centro | 1500 µs |
| Frequência | 50–330 Hz |
| Ângulo do curso | ±15–45° |

Para ornitópteros de alto desempenho, são recomendados servos digitais com taxa de atualização de 330 Hz. Os servos analógicos funcionam a 50 Hz, mas têm menor precisão.

### Receptor

Qualquer protocolo de receptor serial é suportado. CRSF (TBS Crossfire / ExpressLRS) é recomendado para:
- Baixa latência (crítica para controle de oscilação)
- Telemetria integrada
- RSSI sobre protocolo (sem fiação extra)

### Bateria

- **2S (7,4V)**: Pequenos ornitópteros, alimentados diretamente por servo
- **3S (11,1V)**: Ornitópteros médios, BEC necessários para servos
- **4S (14,8V)**: ornitópteros grandes, BEC externo recomendado

---

## Periféricos Suportados

| Periférico | Através de | Notas |
|----------|-----|-------|
| GPS | UART | UBlox M8N ou compatível |
| VTX | UART TX | Vagabundo, SmartAudio |
| Câmera | — | Qualquer câmera analógica FPV |
| Campainha | almofada BUZZ | Campainha ativa 5V |
| LED Tira | almofada LED | WS2812 / SK6812 |
| OpenLog | UART TX | Registro de caixa preta |
| Bluetooth | UART | passagem MSP para ajuste móvel |

---

## Metas Futuras

OrniFlight tem como objetivo oferecer suporte a alvos STM32F4/F7 adicionais onde UART e recursos de temporizador suficientes estão disponíveis para controle de servo oscilante. Contribuições são bem-vindas.