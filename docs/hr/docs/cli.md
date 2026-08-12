# CLI Referenca

Sučelje naredbenog retka OrniFlight (CLI) pruža potpuni pristup svim postavkama. Pristup preko kartice **CLI** u konfiguratoru OrniFlight, ili preko serijskog terminala na 115200 bauda.

## Osnovne naredbe

| Naredba | Opis |
|---------|------------|
| `help` | Prikaži sve naredbe |
| `status` | Prikaži status sustava |
| `version` | Prikaži verziju firmvera |
| `defaults` | Vrati sve postavke na zadane |
| `save` | Spremite postavke i ponovno pokrenite |
| `exit` | Izlaz CLI (ponovno pokretanje bez spremanja) |
| `diff` | Prikaži promijenjene postavke (korisno za dijeljenje konfiguracija) |
| `dump` | Prikaži sve postavke |
| `dump all` | Prikaži sve postavke uključujući hardverske zadane |

## Essential Settings

### Značajke ploče &amp;a

```
# List available features
feature list

# Enable/disable features
feature GPS
feature TELEMETRY
feature LED_STRIP

# Set mixer type
mixer = ORNITHOPTER
```

### Prijemnik

```
set serialrx_provider = CRSF
set serialrx_inverted = OFF
set serialrx_halfduplex = OFF
set rssi_channel = 0
```

### Baterija

```
set vbat_min_cell_voltage = 330
set vbat_max_cell_voltage = 430
set vbat_warning_cell_voltage = 350
```

### Servosi

```
set servo_pwm_rate = 330
set servo_center_pulse = 1500
set flap_spread = 20
```

## ONDAS Postavke (apiVerzija 1.46+)

```
# Cadence — timing modulation
set ondas_cadence_gain = 50       # 0-100, timing brain
set ondas_cadence_phase = 0       # -180° to +180°

# Ferocity — asymmetric thrust
set ondas_ferocity_p_gain = 40    # Immediate thrust asymmetry
set ondas_ferocity_d_gain = 30    # Anticipatory drag exploitation
set ondas_ferocity_roll_gain = 50 # Roll-axis ferocity scaling
set ondas_ferocity_yaw_gain = 40  # Yaw-axis ferocity scaling

# Balance — wing symmetry
set ondas_balance_gain = 50       # Left/right wing balance

# Advanced
set ondas_warp_gain = 0           # Stroke waveform warping
set ondas_warp_yaw_gain = 0       # Yaw-specific warping
set ondas_anchor_gain = 0         # Phase anchoring strength
set ondas_resonance_gain = 0      # Airframe resonance compensation
```

## Profili leta

```
# Switch between profiles
profile 0  # Profile 1 (default)
profile 1  # Profile 2
profile 2  # Profile 3

# Profile-aware settings use index:
set ondas_cadence_gain = 50       # Current profile only
```

## Servo montažni kut (apiVerzija 1.46+)

```
set servo_mount_angle_0 = 0       # Wing servo 0 mounting offset (±30°)
set servo_mount_angle_1 = 0       # Wing servo 1 mounting offset (±30°)
set servo_mount_angle_2 = 0
set servo_mount_angle_3 = 0
```

## Postavke stope

```
set roll_rc_rate = 90
set roll_srate = 65
set roll_expo = 30

set pitch_rc_rate = 90
set pitch_srate = 65
set pitch_expo = 30

set yaw_rc_rate = 90
set yaw_srate = 50
set yaw_expo = 20
```

## Sigurno

```
set failsafe_delay = 4
set failsafe_procedure = LAND
set failsafe_throttle = 1000
```

## Dijeljenje vaše konfiguracije

Koristite `diff` za izvoz samo postavki koje nisu zadane:

```
# In CLI:
diff

# Copy the output — this is your complete configuration
# To restore, paste the diff output into CLI and type 'save'
```