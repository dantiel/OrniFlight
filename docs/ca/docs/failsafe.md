# A prova de fallades

OrniFlight té un sistema de seguretat de dues etapes per protegir el vostre ornitòpter en cas de pèrdua de senyal del receptor.

## Sistema de dues etapes

### Etapa 1 — S'ha detectat una pèrdua de senyal

Activat quan:
- Qualsevol canal de vol té una longitud de pols no vàlida
- El receptor informa en mode de seguretat
- Sense senyal del receptor durant un temps configurat

**Acció**: tots els canals canvien a valors de reserva (configurats mitjançant `rxfail`). S'inicia una breu finestra de recuperació — si el senyal torna, es reprèn el vol normal.

### Etapa 2 — Temps de guàrdia caducat

S'introdueix quan l'etapa 1 persisteix més que `failsafe_delay` (per defecte: 400 ms) I l'embarcació està armada.

**Procediments** (configurable mitjançant `failsafe_procedure`):

| Procediment | Comportament |
|-----------|-----------|
| **DROP** | Desarmar immediatament — les ales s'aturen, l'avió baixa |
| **LAND** | Mode de lliscament — ales bloquejades horitzontals, descens controlat |

**LAND** és el procediment recomanat per als ornitòpters — manté les ales en una posició neutra per a un descens lliscant, donant temps per a la recuperació del senyal.

## CLI Configuració

```
set failsafe_delay = 4         # Guard time in 0.1s (4 = 400ms)
set failsafe_procedure = LAND  # DROP or LAND
set failsafe_throttle = 1000   # Fallback throttle (low)
set failsafe_switch_mode = STAGE1  # Transmitter switch behavior
```

## Receptor Failsafe

També configureu la seguretat del vostre receptor per emetre **sense polsos** en pèrdua de senyal. Això permet al controlador de vol detectar la pèrdua i activar l'etapa 1.

## Prova

Prova de seguretat **amb l'articulació de l'ala desconnectada** al banc:
1. Assigna el mode FAILSAFE a un interruptor
2. Arma l'oficina
3. Commuteu l'interruptor → observeu el procediment de seguretat
4. Verifiqueu que el comportament del servo coincideix amb les expectatives