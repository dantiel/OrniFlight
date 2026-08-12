# CLI 참조

OrniFlight의 명령줄 인터페이스(CLI)는 모든 설정에 대한 전체 액세스를 제공합니다. OrniFlight 구성기의 **CLI** 탭을 통해 또는 115200 보드의 직렬 터미널을 통해 액세스합니다.

## 기본 명령

| 명령 | 설명 |
|---------|------------|
| `help` | 모든 명령 표시 |
| `status` | 시스템 상태 표시 |
| `version` | 펌웨어 버전 표시 |
| `defaults` | 모든 설정을 기본값으로 재설정 |
| `save` | 설정 저장 및 재부팅 |
| `exit` | CLI 종료(저장하지 않고 재부팅) |
| `diff` | 변경된 설정 표시(구성 공유에 유용함) |
| `dump` | 모든 설정 표시 |
| `dump all` | 하드웨어 기본값을 포함한 모든 설정 표시 |

## 필수 설정

### 보드 및 기능

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

### 수신기

```
set serialrx_provider = CRSF
set serialrx_inverted = OFF
set serialrx_halfduplex = OFF
set rssi_channel = 0
```

### 배터리

```
set vbat_min_cell_voltage = 330
set vbat_max_cell_voltage = 430
set vbat_warning_cell_voltage = 350
```

### 서보

```
set servo_pwm_rate = 330
set servo_center_pulse = 1500
set flap_spread = 20
```

## ONDAS 설정 (api버전 1.46+)

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

## 비행 프로필

```
# Switch between profiles
profile 0  # Profile 1 (default)
profile 1  # Profile 2
profile 2  # Profile 3

# Profile-aware settings use index:
set ondas_cadence_gain = 50       # Current profile only
```

## 서보 마운트 각도(apiVersion 1.46+)

```
set servo_mount_angle_0 = 0       # Wing servo 0 mounting offset (±30°)
set servo_mount_angle_1 = 0       # Wing servo 1 mounting offset (±30°)
set servo_mount_angle_2 = 0
set servo_mount_angle_3 = 0
```

## 요금 설정

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

## 안전장치

```
set failsafe_delay = 4
set failsafe_procedure = LAND
set failsafe_throttle = 1000
```

## 구성 공유

기본이 아닌 설정만 내보내려면 `diff`를 사용하십시오.

```
# In CLI:
diff

# Copy the output — this is your complete configuration
# To restore, paste the diff output into CLI and type 'save'
```