# Failsafe

OrniFlight has a two-stage failsafe system to protect your ornithopter in case of receiver signal loss.

## Two-Stage System

### Stage 1 — Signal Loss Detected

Triggered when:
- Any flight channel has invalid pulse length
- Receiver reports failsafe mode
- No signal from receiver for a configured duration

**Action**: All channels switch to fallback values (configured via `rxfail`). A short recovery window begins — if signal returns, normal flight resumes.

### Stage 2 — Guard Time Expired

Entered when Stage 1 persists longer than `failsafe_delay` (default: 400ms) AND the craft is armed.

**Procedures** (configurable via `failsafe_procedure`):

| Procedure | Behavior |
|-----------|----------|
| **DROP** | Disarm immediately — wings stop, aircraft descends |
| **LAND** | Glide mode — wings locked horizontal, controlled descent |

**LAND** is the recommended procedure for ornithopters — it holds wings in a neutral position for a gliding descent, giving time for signal recovery.

## CLI Settings

```
set failsafe_delay = 4         # Guard time in 0.1s (4 = 400ms)
set failsafe_procedure = LAND  # DROP or LAND
set failsafe_throttle = 1000   # Fallback throttle (low)
set failsafe_switch_mode = STAGE1  # Transmitter switch behavior
```

## Receiver Failsafe

Also configure your receiver's fail-safe to output **no pulses** on signal loss. This allows the flight controller to detect the loss and activate Stage 1.

## Testing

Test failsafe **without propellers/motors** on the bench:
1. Assign FAILSAFE mode to a switch
2. Arm the craft
3. Toggle the switch → observe failsafe procedure
4. Verify servo behavior matches expectations
