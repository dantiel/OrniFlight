#MSP Protocolo

> *MultiWii Protocolo serial — como o Configurador se comunica com OrniFlight.*

## Visão geral

OrniFlight estende o Betaflight MSP com mensagens específicas para ornitópteros. A especificação oficial reside no repositório de firmware em `src/main/msp/`.

**Versão atual:** apiVersion 1.46 (OrniFlight v0.4.6)

## Mensagens principais

### MSP_PID_ADVANCED (112/0x70)

A principal mensagem de ajuste do ONDAS. Cresceu de 48 bytes (legado) para 87 bytes (1,46).

| Versão API | Tamanho | Novos Conteúdos |
|------------|------|-------------|
| 1,33 | 48 | Legado PID avançado |
| 1,42 | 59 | + itermRelaxCutoff, 10 ganhos ONDAS v2 |
| 1,43 | 71 | + servo_mount_angle[4], phase_shift[4], presciência, espelho, saudade, ssff |
| 1,44 | 75 | + servo_speed, max_amplitude, flap_magnitude, wing_origin_offset[4] |
| 1,45 | 82 | + freq_channel, freq_min_hz, freq_max_hz, modo de vôo, flutter_gain, flutter_hz, acelerador_bypass |
| 1,46 | 87 | + profile_index, ferocity_downstroke, ferocity_upstroke, aeroelastic_glide, aeroelastic_flap |

### MSP_SERVO_CONFIGURATIONS (120/0x78)

Configuração servo com 4 bytes finais ONDAS: glide_deg + triplo ONDAS v1.

## Compatibilidade com versões anteriores

Todas as versões do API são compatíveis com versões anteriores. Um remetente de 48 bytes se comunica com um receptor de 1,46 — campos extras padrão para valores sensíveis.

## Formato de fio

Todos os valores multibyte são little endian. Valores assinados armazenados como `value + 128` na ligação. Os valores de ganho não assinados (0–100) são diretos. Comprimentos de array precedidos por contagem u8.

---

*Veja `docs/MSP_FIRMWARE_INTERFACE.md` no repositório de firmware para a especificação completa.*