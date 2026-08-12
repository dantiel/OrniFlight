# Prijemnik (RX)

OrniFlight podržava više protokola prijemnika za radio kontrolu vašeg ornitoptera.

## Podržani protokoli

| Protokol | Upišite | Bilješke |
|----------|------|-------|
| **CRSF** (Unakrsna vatra) | Serijski | Niska latencija, telemetrija, preporučeno |
| **SBUS** | Serijski | Obrnuto, potreban je pretvarač na F4 |
| **IBUS** (FlySky) | Serijski | Neobrnuto, izravno UART |
| **PPM** | Jednožilni analogni | 8ch, naslijeđe, ne preporučuje se |
| **SPEKTRUM** | Serijski | 1024/2048, vezanje putem CLI |
| **FPORT** | Serijski | FrSky, kombinira RX+telemetriju |
| **GHST** (Duh) | Serijski | ImmersionRC, niska latencija |

## Serijska RX konfiguracija

1. Spojite prijemnik na slobodni UART RX pin
2. U konfiguratoru → **Portovi**: postavite UART na `Serial RX`
3. U konfiguratoru → **Konfiguracija**: odaberite protokol
4. Za SBUS na F4: omogućite `set sbus_inversion = ON`

## CLI Brzo postavljanje

```
feature RX_SERIAL
set serialrx_provider = CRSF
set serialrx_inverted = OFF
set serialrx_halfduplex = OFF
save
```

## Sigurno

Konfigurirajte prijemnik failsafe tako da prijamnik emitira **bez impulsa** pri gubitku signala. Kontrolor leta će to zatim detektirati i aktivirati vlastitu proceduru zaštite od greške. Pogledajte [Failsafe](failsafe.html) za konfiguraciju na razini FC.