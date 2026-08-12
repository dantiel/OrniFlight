# A prueba de fallos

OrniFlight ten un sistema de seguridade de dúas etapas para protexer o seu ornitóptero en caso de perda de sinal do receptor.

## Sistema de dúas etapas

### Etapa 1 — Detectouse a perda de sinal

Activado cando:
- Calquera canle de voo ten unha lonxitude de pulso non válida
- O receptor informa do modo de seguridade
- Non hai sinal do receptor durante un tempo configurado

**Acción**: todas as canles cambian a valores alternativos (configurados mediante `rxfail`). Comeza unha pequena xanela de recuperación — se o sinal volve, retómase o voo normal.

### Fase 2 — Tempo de garda caducado

Introdúcese cando a fase 1 persiste máis de `failsafe_delay` (predeterminado: 400 ms) E a nave está armada.

**Procedementos** (configurable mediante `failsafe_procedure`):

| Procedemento | Comportamento |
|-----------|----------|
| **DROP** | Desarme inmediatamente — as ás paran, o avión descende |
| **LAND** | Modo de deslizamento — ás bloqueadas horizontalmente, descenso controlado |

**LAND** é o procedemento recomendado para ornitópteros — mantén as ás en posición neutra para un descenso planeador, dando tempo para a recuperación do sinal.

## CLI Configuración

zz0zzz

## Receptor Failsafe

Tamén configura a proba de fallos do teu receptor para emitir **sen pulsos** na perda de sinal. Isto permite que o controlador de voo detecte a perda e active a fase 1.

## Probas

Proba a proba de seguridade **coa conexión de ala desconectada** no banco:
1. Asigne o modo FAILSAFE a un interruptor
2. Arma o oficio
3. Active o interruptor → observe o procedemento de seguridade
4. Verifique que o comportamento do servo coincida coas expectativas