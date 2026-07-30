# OrniFlight Configurator — Three-Channel ONDAS Update

The firmware now uses a three-channel breathing-pause architecture for flapping-wing stabilization. PID terms modulate wing trajectory parameters instead of servo offset.

## Background

The three `ondas_gain*` fields in `servoConfig_t` (`int8_t`, range `-100..100`, `PG_SERVO_CONFIG` version 0) have been repurposed:

| MSP Field | New Label | New Tooltip | New Default |
|-----------|-----------|-------------|-------------|
| `ondas_gain` *(already in MSP_PID_ADVANCED)* | **Phase Advance Gain** | P-term → flapping phase acceleration. Higher values make the wing respond more aggressively to pitch error by varying k₀ (phase drive strength). "Push harder now." | 20 |
| `ondas_gain2` *(needs MSP exposure)* | **Breathing Pause Depth** | D-term → ferocity modulation depth. Higher values deepen the breathing pause at stroke extremes when error is accelerating, delaying the next opposite stroke. Stabilizes by redistributing rhythm. | 20 |
| `ondas_gain3` *(needs MSP exposure)* | **Asymmetry Bias** | I-term → upstroke/downstroke ferocity bias. Persistent asymmetry shifts thrust balance between half-cycles. Positive = harder upstrokes (pitch-down bias). | 10 |

## MSP Changes Required

### 1. `MSP_PID_ADVANCED` (msg 94 out / 95 in)

Append `ondas_gain2` and `ondas_gain3` after the existing `ondas_gain`:

**Out (msg 94)** — add after `sbufWriteU8(dst, servoConfigMutable()->ondas_gain)`:
```c
sbufWriteU8(dst, servoConfigMutable()->ondas_gain2);
sbufWriteU8(dst, servoConfigMutable()->ondas_gain3);
```

**In (msg 95)** — add after `servoConfigMutable()->ondas_gain = sbufReadU8(src)`:
```c
servoConfigMutable()->ondas_gain2 = sbufReadU8(src);
servoConfigMutable()->ondas_gain3 = sbufReadU8(src);
```

### 2. `MSP_SERVO_CONFIGURATIONS` (msg 120 out)

Add all three gains after `ornithopter_glide_deg`:
```c
sbufWriteU8(dst, servoConfigMutable()->ondas_gain);
sbufWriteU8(dst, servoConfigMutable()->ondas_gain2);
sbufWriteU8(dst, servoConfigMutable()->ondas_gain3);
```

### 3. `MSP_SET_SERVO_CONFIGURATION` (msg 212 in)

Accept the extended format:
```c
servoConfigMutable()->ondas_gain = sbufReadU8(src);
servoConfigMutable()->ondas_gain2 = sbufReadU8(src);
servoConfigMutable()->ondas_gain3 = sbufReadU8(src);
```

## UI Changes Required

- Rename **"ONDAS Gain"** → **"Phase Advance Gain"**
- Add two new sliders: **"Breathing Pause Depth"** and **"Asymmetry Bias"**
- Defaults: `20`, `20`, `10`
- Range: `-100` to `100` for all three
- Consider grouping them under a header: **"Wing Trajectory Modulation"** or **"Breathing Pause"**

## Firmware Reference

| File | Lines | Content |
|------|-------|---------|
| `src/main/flight/pid.c` | ~90–104 | Three modulation globals |
| `src/main/flight/pid.c` | ~640–710 | `applyFerocityWaveShaping(dMod, iBias)`, `calculateFlappingFromThrottle` k₀ modulation |
| `src/main/flight/pid.c` | ~1590–1640 | Three-channel computation from `pidData[FD_PITCH]` |
| `src/main/flight/servos.h` | 141–146 | `ondas_gain` / `ondas_gain2` / `ondas_gain3` struct fields |
| `src/main/cli/settings.c` | 1429–1431 | CLI table entries |
| `src/main/flight/servos.c` | 71–73 | Default values |
