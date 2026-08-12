# Receptor (RX)

OrniFlight admet diversos protocols de receptor per al control de ràdio del vostre ornitòpter.

## Protocols compatibles

| Protocol | Tipus | Notes |
|----------|------|-------|
| **CRSF** (Foc creuat) | Serial | Baixa latència, telemetria, recomanada |
| **SBUS** | Serial | Invertit, necessita inversor a F4 |
| **IBUS** (FlySky) | Serial | No invertida, directe UART |
| **PPM** | Analògic d'un sol cable | 8ch, llegat, no recomanat |
| **SPEKTRUM** | Serial | 1024/2048, vincular mitjançant CLI |
| **FPORT** | Serial | FrSky, combina RX+Telemetria |
| **GHST** (fantasma) | Serial | ImmersionRC, latència baixa |

## Configuració sèrie RX

1. Connecteu el receptor a un pin UART RX lliure
2. Al Configurator → **Ports**: configureu UART a `Serial RX`
3. Al Configurador → **Configuració**: seleccioneu el protocol
4. Per a SBUS a F4: activa `set sbus_inversion = ON`

## CLI Configuració ràpida

```
feature RX_SERIAL
set serialrx_provider = CRSF
set serialrx_inverted = OFF
set serialrx_halfduplex = OFF
save
```

## A prova de fallades

Configureu el receptor a prova d'errors perquè el receptor emeti **cap polsos** en pèrdua de senyal. Aleshores, el controlador de vol detectarà això i activarà el seu propi procediment de seguretat. Vegeu [Failsafe](failsafe.html) per a la configuració a nivell de FC.