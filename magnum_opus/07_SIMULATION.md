# 07 — Simulation: sim_ferocity.rb Analysis & Tuning Methodology

## Overview

`sim_ferocity.rb` is a 600-line Ruby simulation harness that models the complete OrniFlight control chain:
- Wing phase ODE
- Ferocity wave shaping
- ONDAS gate
- SSFF
- PID controller
- 1st-order airframe pitch dynamics

It operates entirely offline — no hardware required. This makes it the primary tool for:
1. Understanding the control theory without a physical ornithopter
2. Tuning parameters before field testing
3. Validating code changes against known behavior
4. Exploring the parameter space systematically

## Six Simulation Modes

### 1. `wave` — Static Wave Shape Analysis
```
ruby sim_ferocity.rb wave [F]
```
Computes `tanh(F·sinθ)/tanh(F)` across a full 360° cycle (361 points). Outputs shaped wave, derivative, ONDAS gate, and velocity amplification at each phase point. Used for understanding the static wave shape at a given ferocity.

### 2. `flight` — Full Dynamic Simulation
```
ruby sim_ferocity.rb flight [F_down] [F_up]
```
Runs the complete wing ODE + airframe + PID + ONDAS + SSFF chain over simulated flight time. Outputs RMS pitch error, RMS pitch rate, and time-series data. This is the primary validation mode.

### 3. `sweep` — Parameter Space Exploration
```
ruby sim_ferocity.rb sweep
```
Runs an 11×11 grid (121 combinations) over F_down × F_up ∈ [1,10]. Measures RMS pitch error for each combination. Outputs a matrix showing which ferocity combinations produce the most stable flight.

**Key finding**: Balanced ferocity (F_down ≈ F_up ≈ 5-6) minimizes pitch amplitude. High ferocity (>7) narrows the ONDAS window but slightly increases pitch oscillation.

### 4. `compare` — Fixed vs SSFF Comparison
```
ruby sim_ferocity.rb compare [F_down] [F_up]
```
Side-by-side simulation with and without stroke-synchronous feed-forward. Demonstrates SSFF's ability to learn and cancel repetitive flap-frequency error.

### 5. `derive` — Velocity Amplification Analysis
```
ruby sim_ferocity.rb derive
```
Computes the velocity amplification factor at each phase point for the full ferocity range. Shows how `d(shapedWave)/dt` exceeds `cosθ·ω` (pure sine velocity) at stroke start.

### 6. `prize` — Full Theory Demonstration
```
ruby sim_ferocity.rb prize [F_down] [F_up]
```
Comprehensive demonstration: wing kinematics, velocity amplification, thrust estimation, and stability analysis. The most detailed single-run mode.

## Simulation Model

### Wing ODE
```
θ̈ = k₀ · T_cmd − k₂ · ω
Euler: θ(t+dt) = θ(t) + ω(t)·dt
       ω(t+dt) = ω(t) + θ̈(t)·dt
```
Default: `k₀=1.0`, `k₂=10.0`, `dt=125µs` (8 kHz equivalent)

### Airframe (1st-Order Pitch Dynamics)
```
θ̈_airframe = (M_aero + M_control) / I_YY − PITCH_DAMP · ω_pitch
```
Default: `I_YY=0.02` (pitch moment of inertia), `PITCH_DAMP=0.3`

### PID Controller
Standard Betaflight PID with ONDAS gate:
```
error_rate = setpoint − gyro_rate
P = Kp · error_rate
I = Ki · ∫error_rate · dt    (with windup limit)
D = Kd · d(error_rate)/dt    (with lowpass)
output = (P + I + D) × ondasAttenuation
```
Default: `Kp=8.0`, `Ki=0.5`, `Kd=2.0`

## Tuning Methodology

### Step 1: Baseline Ferocity
```
ruby sim_ferocity.rb wave 1.78
```
Run `wave` mode at the default ferocity (CLI value 12 = F=1.78). Verify the shaped wave looks reasonable — smooth, no discontinuities, full [-1,1] range.

### Step 2: Parameter Sweep
```
ruby sim_ferocity.rb sweep
```
Find the ferocity pair that minimizes RMS pitch. The sweep produces a heatmap — the "valley" of minimum pitch error is your target region.

### Step 3: Flight Validation
```
ruby sim_ferocity.rb flight [F_down] [F_up]
```
Run the full dynamic simulation at the sweep-optimal ferocity pair. Check:
- RMS pitch error < 0.1° (good), < 0.05° (excellent)
- No sustained oscillation (PID tuning issue)
- Smooth SSFF convergence (if enabled)

### Step 4: SSFF Tuning
```
ruby sim_ferocity.rb compare [F_down] [F_up]
```
If SSFF reduces RMS pitch significantly (>20%), enable it on the real aircraft. Start with `ssff_gain = 20` and increase gradually.

### Step 5: Three-Channel Gain Tuning
The simulation doesn't directly model three-channel gains (ondas_gain/gain2/gain3) — these are applied at runtime in `pid.c`. Tuning methodology:
1. Start with all three at default (10)
2. Fly, observe pitch behavior
3. If slow to respond → increase `ondas_gain` (P→phase, makes wing accelerate faster)
4. If overshooting/oscillating → increase `ondas_gain2` (D→ferocity, deeper breathing pause)
5. If consistently drifting (CG offset) → adjust `ondas_gain3` (I→asymmetry, persistent bias)

### Step 6: Field Validation
Simulation provides starting values. Real flight will differ due to:
- Actual airframe dynamics (I_YY, damping)
- Wing flexibility and aeroelastic effects
- Wind/gust disturbances
- Sensor noise characteristics

**Always start with simulation-derived values and tune conservatively upward.**

## Extending the Simulation

The simulation is designed to be extended. Possible enhancements:
- Add aeroelastic wing model (flexible spar dynamics)
- Add multi-axis (roll + pitch simultaneous)
- Add wind/gust disturbance model
- Add sensor noise injection
- Export blackbox-compatible log format for comparison with real flight data

## Verification Against Real Code

The simulation was verified to match `pid.c` behavior during the Coagula phase:
- All 6 modes produce identical output before and after Coagula changes
- Magic number extraction to `#define`s confirmed parameter equivalence
- Duplicate velocity block removal confirmed functional equivalence
- `ruby -c sim_ferocity.rb` passes syntax check

## Key Numerical Results

From `sweep` mode (11×11 grid, F ∈ [1,10]):
- **Best stability**: F_down=F_up=5-6, RMS pitch ~0.064°
- **Worst stability**: F_down=10, F_up=1, RMS pitch ~0.211°
- **Balanced ferocity is more important than absolute ferocity** for pitch stability

From `derive` mode:
- Peak velocity amplification at F=4.0, θ≈6° (stroke start)
- Velocity gain plateaus above F=7.0 — diminishing returns
- Recommended ferocity range for practical use: F ∈ [1.5, 6.0] (CLI 8-71)
