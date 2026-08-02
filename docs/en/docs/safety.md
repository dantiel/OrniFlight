# Safety

## Pre-Flight Checklist

1. **Wings**: Ensure wings are securely mounted and linkage is intact
2. **Battery**: Fully charged, properly secured, correct cell count
3. **Controls**: Verify stick responses in Configurator receiver tab
4. **Failsafe**: Test on bench before flight (see [Failsafe](failsafe.html))
5. **Arm Switch**: Configure and test — never rely on stick arming alone
6. **Launch Area**: Clear of people, obstacles, and overhead obstructions

## Arm Safety

OrniFlight uses multiple safeties before arming:

- **Throttle low**: Throttle must be at minimum
- **Level**: Craft must be reasonably level
- **RX Signal**: Valid receiver signal required
- **CPU Load**: System must not be overloaded
- **Calibration**: Accelerometer and gyro must be calibrated

## In-Flight Safety

- **Fly within visual line of sight**
- Maintain safe distance from people and animals
- Monitor battery voltage — land before warning threshold
- In FPV: always fly with a spotter
- Wind: ornithopters can be wind-sensitive — know your limits

## Emergency Procedures

| Situation | Action |
|-----------|--------|
| Loss of orientation | Switch to INDEPENDENT mode, center sticks |
| Signal loss | Failsafe will auto-land (if LAND procedure configured) |
| Wing damage | Disarm immediately — wings stop |
| Bird strike | Disarm, assess damage before re-arming |
| Low battery | Land immediately — ornithopters have no autorotation |

## Ornithopter-Specific Risks

- **Pinch hazard**: Flapping wings can cause injury — keep hands clear when armed
- **Linkage failure**: Pre-flight check all pushrods and ball joints
- **Resonance**: Certain flapping frequencies may excite airframe resonances — tune ONDAS sweep to avoid
- **Glide lockout**: If wing servos fail in non-neutral position, controlled landing is impossible — test servo failsafe positions