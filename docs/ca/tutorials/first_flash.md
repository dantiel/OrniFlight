# Primer Flash

> *Aconseguint OrniFlight al vostre controlador de vol — pas a pas.*

## El que necessites

- Controlador de vol basat en STM32F4 (OMNIBUSF4, TINYFISH, MATEKF405, etc.)
- cable USB
- [dfu-util](http://dfu-util.sourceforge.net/) o STM32CubeProgrammer
- Fitxer OrniFlight `.hex` de la [pàgina de llançaments](https://github.com/dantiel/OrniFlight/releases)

## Pas 1: introduïu el mode DFU

1. **Mantén premut el botó BOOT** del controlador de vol
2. **Connecteu USB** mentre premeu el botó
3. **Allibera** després de 2 segons

Verifiqueu a macOS/Linux:

```
dfu-util -l
```

Hauria de mostrar `Found DFU: [0483:df11]`

## Pas 2: Flash

```
dfu-util -a 0 -D obj/orniflight_0.4.6_OMNIBUSF4.hex
```

## Pas 3: primer arrencada

1. Desconnecteu USB
2. Torneu a connectar USB (no prengui BOOT)
3. Connecteu-vos mitjançant OrniFlight Configurator

## Pas 4: Configuració bàsica

Al Configurador:

1. **Pestaña Ports**: configureu UART per al vostre receptor (sèrie RX)
2. **Pestanya de configuració**: seleccioneu el protocol del receptor (es recomana CRSF)
3. **Pestanya Modes**: configureu els interruptors ARM, GLIDE/INDEPENDENT i PROFILE
4. **Pestanya → ONDAS avançada**: revisa els valors predeterminats, primer ajusta Cadence

## Resolució de problemes

| Problema | Arreglar |
|----------|-----|
| No s'ha trobat el dispositiu DFU | Proveu un cable USB diferent, comproveu el botó BOOT |
| El flash falla | Comproveu la instal·lació de dfu-util, els permisos USB |
| Sense arrencada després del flash | Torneu a flashejar, verifiqueu que l'hex coincideix amb el vostre objectiu |
| El configurador no es connecta | Comproveu el port COM i la velocitat de transmissió |

---

*Següent: [Configuració bàsica](basic_setup.html) →*