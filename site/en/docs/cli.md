# CLI Reference

> *OrniFlight-specific CLI commands beyond standard Betaflight.*

## ONDAS Parameters

```
set cadence_gain = 50              # 0-100, timing modulation window
set ferocity_d_gain = 30           # 0-100, D-term stabilization
set ferocity_p_gain = 20           # 0-100, P-term response
set ferocity_roll_gain = 20        # 0-100, roll axis specific
set ferocity_yaw_gain = 0          # 0-100, yaw axis specific
set balance_gain = 0               # -100 to +100, stroke asymmetry
set warp_gain = 50                 # 0-100, modulation window width
set warp_yaw_gain = 0              # -100 to +100, yaw warp
set anchor_gain = 70               # 0-100, raw PID mix
set resonance_gain = 30            # 0-100, cycle memory
```

## Phase 2 Parameters

```
set prescience_gain = 10           # 0-100, timing advance
set espelho_gain = 20              # 0-100, differential coupling
set saudade_gain = 15              # 0-100, hysteresis memory
set ssff_gain = 0                  # 0-100, stroke-sync feed-forward
```

## Wing Dynamics

```
set glide_angle = 30               # degrees, glide lock angle
set servo_speed = 100              # 0-100, servo speed limit
set max_amplitude = 80             # 0-100, max flap amplitude
set flap_magnitude = 100           # 0-100, flap force scaling
set wing_origin_offset = 50        # 0-100, wing root offset
```

## Frequency

```
set freq_channel = 6               # 0-18, RC channel for frequency control
set freq_min_hz = 2                # Hz at minimum channel value
set freq_max_hz = 8                # Hz at maximum channel value
```

## Aeroelastic

```
set aeroelastic_glide_coefficient = 0    # -100 to +100
set aeroelastic_flap_coefficient = 0     # -100 to +100
```

## Profile & Mode

```
set ornithopter_profile_index = 0        # 0-3, profile slot
set ornithopter_flight_mode = 0          # 0=GLIDE, 1=INDEPENDENT
```

## Useful Commands

```
status                    # Show system status including ONDAS state
diff all                  # Show all non-default settings
dump ornithopter          # Dump all ornithopter-related settings
```

---

*Also available via MSP in the Configurator under Advanced → ONDAS.*
