# Controls

OrniFlight uses standard RC stick mapping with ornithopter-specific extensions.

## Stick Mapping

| Stick | Axis | Primary Effect |
|-------|------|---------------|
| Throttle (Left, vertical) | Throttle | Flapping amplitude / thrust |
| Yaw (Left, horizontal) | Yaw | Differential wing thrust for turning |
| Pitch (Right, vertical) | Pitch | Forward/backward tilt |
| Roll (Right, horizontal) | Roll | Left/right banking |

## Flight Modes

| Mode | Stick Behavior |
|------|---------------|
| **ACRO** | Sticks control angular rate — no auto level |
| **ANGLE** | Sticks control angle — auto-level when released |
| **HORIZON** | ANGLE near center, ACRO at full deflection |

ACRO is recommended for experienced pilots. ANGLE is good for first flights and thermal soaring.

## Ornithopter-Specific Controls

### INDEPENDENT Mode

When INDEPENDENT mode is active, each wing servo responds independently:
- **Left stick** → left wing servos
- **Right stick** → right wing servos
- Enables asymmetric flapping for aggressive maneuvers

### GLIDE Mode

GLIDE mode locks both wings in horizontal position. The ornithopter becomes a glider:
- **Throttle** has no effect on wing position
- **Pitch/Roll/Yaw** still influence tail control surfaces (if equipped)

### Profile Switching

In-flight profile switching via AUX channel allows changing PID/ONDAS parameters mid-flight:
- **Profile 1**: Standard cruise settings
- **Profile 2**: High-agility settings
- **Profile 3**: Efficiency/glide settings

## Rates

Configure rates in the **PID Tuning** tab. For ornithopters, start with conservative rates — flapping dynamics amplify control inputs:
- RC Rate: 0.80–1.00
- Super Rate: 0.60–0.70
- Expo: 0.20–0.40