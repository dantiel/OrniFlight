# À prova de falhas

OrniFlight possui um sistema à prova de falhas de dois estágios para proteger seu ornitóptero em caso de perda de sinal do receptor.

## Sistema de dois estágios

### Perda de sinal — do estágio 1 detectada

Acionado quando:
- Qualquer canal de voo possui comprimento de pulso inválido
- Receptor relata modo à prova de falhas
- Nenhum sinal do receptor durante um período configurado

**Ação**: Todos os canais mudam para valores alternativos (configurados via `rxfail`). Uma breve janela de recuperação começa — se o sinal retornar, o vôo normal será retomado.

### Estágio 2 — Tempo de proteção expirado

Inserido quando o Estágio 1 persiste por mais de `failsafe_delay` (padrão: 400ms) E a nave está armada.

**Procedimentos** (configuráveis via `failsafe_procedure`):

| Procedimento | Comportamento |
|-----------|----------|
| **DROP** | Desarme imediatamente — asas param, aeronave desce |
| **LAND** | Modo de planeio — asas travadas horizontalmente, descida controlada |

**LAND** é o procedimento recomendado para ornitópteros. — mantém as asas em posição neutra para uma descida plana, dando tempo para recuperação do sinal.

## CLI Configurações

```
set failsafe_delay = 4         # Guard time in 0.1s (4 = 400ms)
set failsafe_procedure = LAND  # DROP or LAND
set failsafe_throttle = 1000   # Fallback throttle (low)
set failsafe_switch_mode = STAGE1  # Transmitter switch behavior
```

## Receptor à prova de falhas

Configure também o sistema à prova de falhas do seu receptor para emitir **sem pulsos** em caso de perda de sinal. Isso permite que o controlador de vôo detecte a perda e ative o Estágio 1.

## Teste

Teste à prova de falhas **com a articulação da asa desconectada** na bancada:
1. Atribua o modo FAILSAFE a um switch
2. Arme a nave
3. Alterne a chave → e observe o procedimento à prova de falhas
4. Verifique se o comportamento do servo corresponde às expectativas