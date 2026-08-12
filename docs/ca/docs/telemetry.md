# Telemetria

La telemetria envia dades de vol des de OrniFlight al vostre transmissor de ràdio — tensió de la bateria, corrent, coordenades RSSI, GPS, altitud i molt més.

## Protocols compatibles

| Protocol | Sistema de ràdio | Recompte de fils |
|----------|-------------|-------------|
| **CRSF** | Foc creuat / Traçador / ELRS | Integrat amb RX (bidireccional) |
| **SmartPort** | FrSky | 1 cable (pin TX) |
| **HoTT** | Graupner | 1 cable (TX+TZ) |
| **IBUS** | FlySky | 1 cable (sensor TX) |
| **LTM** | Telemetria de llum (MWP) | 1 fil (TX) |

## Configuració

1. Al Configurator → **Ports**: configureu el pin UART TX al protocol de telemetria adequat
2. Activa la funció de telemetria: `feature TELEMETRY`
3. Configureu la inversió de telemetria si cal

Per a **CRSF**, la telemetria es gestiona automàticament — no cal un port separat.

## SmartPort (FrSky)

SmartPort requereix inversió de senyal als processadors F4. O bé:
- Utilitzeu un controlador de vol amb inversor integrat
- Utilitzeu SoftSerial amb `set tlm_inversion = ON`

```
feature TELEMETRY
set tlm_inverted = ON
set tlm_halfduplex = ON
```

## Dades de telemetria

OrniFlight transmet:
- voltatge VBAT (bateria principal)
- Consum actual / mAh consumit
- RSSI (intensitat del senyal)
- Mode de vol / estat del braç
- Coordenades GPS (si està equipat)
- Altitud / vario (si baròmetre)
- Perfil de vol ONDAS actiu