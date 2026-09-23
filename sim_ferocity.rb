#!/usr/bin/env ruby
# frozen_string_literal: true

# ╔══════════════════════════════════════════════════════════════════════════════╗
# ║  ÆtherCodex — ONDAS + Ferocity Unified Simulation                            ║
# ║  Physics: wing ODE → trapezoidal wave shaping → velocity² thrust → PID      ║
# ║  Control: stroke-synchronous feed-forward eliminates phase lag              ║
# ║  Wave: trapezoidal dwell + cos ramp (ported from GralhaAzul)               ║
# ╚══════════════════════════════════════════════════════════════════════════════╝

require 'csv'

# ─── Constants ────────────────────────────────────────────────────────────────

DT          = 0.001        # 1 kHz
TWO_PI      = 2.0 * Math::PI
FEROCITY_RANGE = 8.0       # f ∈ [0, 8]

# Wing ODE: θ̈ = k₀·T_cmd − k₂·ω  (matches firmware)
K0          = 80.0
K2          = 10.0

# Airframe
I_YY        = 0.02          # pitch moment of inertia (kg·m²)
PITCH_DAMP  = 0.3           # aerodynamic pitch damping
GLIDE_MOMENT_COEFF = 0.5    # wings-down → pitch-up: M = -coeff * sin(θ)

# Thrust from velocity²
THRUST_COEFF = 0.08         # N / (rad/s)²  — scaled for reasonable forces
THRUST_LEVER = 0.15         # m — moment arm converting thrust → pitch moment

# PID
PID_KP      = 8.0
PID_KI      = 0.5
PID_KD      = 2.0

# ONDAS
ONDAS_GAIN  = 1.0

# Ferocity
F_MIN       = 0.0
F_MAX       = 8.0

# Stroke-synchronous feed-forward
K_FF        = 0.3           # how strongly pitch error biases next stroke's ferocity

FLAP_FREQ   = 12.0
GLIDE_THRESHOLD = 0.05

# Phyllotaxis rotation: golden-angle conjugate. {k·0.618} is the canonical
# low-discrepancy sequence — deterministic uniform circle coverage with
# minimal samples, immune to lab/flap clock commensurability.
GOLDEN_CONJUGATE = (Math.sqrt(5.0) - 1.0) / 2.0

# ─── Utility ──────────────────────────────────────────────────────────────────

def param_to_f(p) = ((p.to_i - 1) * FEROCITY_RANGE / 99.0).clamp(0.0, FEROCITY_RANGE)

# Box-Muller Gaussian — for chaotic-wind phase noise
def randn(mean = 0.0, std = 1.0)
  u = Math.sqrt(-2.0 * Math.log(1.0 - rand))
  v = TWO_PI * rand
  mean + std * u * Math.cos(v)
end

# ─── Trapezoidal Wave Shaping ─────────────────────────────────────────────────
# Ported from GralhaAzul formaDoBaterDasAsas() / OrniFlight applyFerocityWaveShaping()
#
# Each half-cycle: dwell at ±1 for d/2, then cos ramp from ±1 to ∓1 over (1-d)/2.
# d = f / FEROCITY_RANGE  ∈ [0, 1]
# Shared limiar (θ reversal point) from raw ferocities — both wings reverse together.
#
# Returns [shaped_wave, dshaped_dtheta, limiar]
#   shaped_wave     = position in shaped space ∈ [-1, 1]
#   dshaped_dtheta  = derivative w.r.t. θ (0 in dwell, ∓k·sin(…) in ramp)
#   limiar          = shared reversal θ (radians, in [0, 2π))

def trapezoidal_wave_shaping(theta_raw, f_down, f_up)
  # Normalize theta to [0, 2π)
  t_norm = theta_raw % TWO_PI
  t_norm += TWO_PI if t_norm < 0

  # Shared limiar from raw ferocities
  w_d = [FEROCITY_RANGE - f_down, 0.01].max
  w_u = [FEROCITY_RANGE - f_up,   0.01].max
  limiar = TWO_PI * w_d / (w_d + w_u)

  # Fast-path: max ferocity → pure square wave
  if f_down >= FEROCITY_RANGE - 0.001 && f_up >= FEROCITY_RANGE - 0.001
    return [(t_norm < limiar) ? 1.0 : -1.0, 0.0, limiar]
  end

  descida = (t_norm < limiar)
  t, ferocity, dt_dtheta = if descida
    [t_norm / limiar, f_down, 1.0 / limiar]
  else
    [(t_norm - limiar) / (TWO_PI - limiar), f_up, 1.0 / (TWO_PI - limiar)]
  end

  d  = ferocity / FEROCITY_RANGE   # [0, 1]
  dh = d * 0.5                      # d/2 per extreme

  shaped, dshaped_dtheta = if d >= 1.0 || t < dh
    # Dwell at start of half-cycle (stroke peak)
    [descida ? 1.0 : -1.0, 0.0]
  elsif t > 1.0 - dh
    # Dwell at end of half-cycle (opposite peak)
    [descida ? -1.0 : 1.0, 0.0]
  else
    # Cos ramp: cos(π·(t-dh)/(1-d))
    k = Math::PI / (1.0 - d)
    ramp_arg = k * (t - dh)
    ramp_val = Math.cos(ramp_arg)
    shape = descida ? ramp_val : -ramp_val

    drank_dt = -k * Math.sin(ramp_arg)
    deriv = drank_dt * dt_dtheta
    deriv = -deriv unless descida
    [shape, deriv]
  end

  [shaped, dshaped_dtheta, limiar]
end

# ─── Wing ODE ─────────────────────────────────────────────────────────────────

class Wing
  attr_accessor :theta, :omega, :f_down, :f_up
  attr_reader :shaped, :shaped_deriv, :ondas_attn, :sin_theta, :cos_theta, :dshaped_dtheta

  def initialize(theta: 0.0, omega: 0.0, f_down: 0.0, f_up: 0.0)
    @theta  = theta
    @omega  = omega
    @f_down = f_down
    @f_up   = f_up
    @shaped = 0.0
    @shaped_deriv = 0.0
    @ondas_attn = 0.5
    @dshaped_dtheta = 0.0
  end

  def step(throttle)
    omegadot = K0 * throttle - K2 * @omega
    @omega  += omegadot * DT
    @theta  += @omega * DT
    @theta  = @theta % TWO_PI

    @sin_theta = Math.sin(@theta)
    @cos_theta = Math.cos(@theta)

    if throttle > GLIDE_THRESHOLD
      @shaped, @dshaped_dtheta, _limiar = trapezoidal_wave_shaping(@theta, @f_down, @f_up)
      @shaped_deriv = @dshaped_dtheta * @omega        # d(shaped)/dt = d(shaped)/dθ · ω
      @ondas_attn = -@shaped.abs + 0.5
    else
      @shaped = 0.0
      @shaped_deriv = 0.0
      @ondas_attn = 0.5
      @dshaped_dtheta = 0.0
    end
  end

  # Position-dependent pitch moment (wings-down → pitch-up)
  def position_moment
    -GLIDE_MOMENT_COEFF * @sin_theta
  end

  # Thrust-derived pitch moment from wing velocity
  def thrust_pitch_moment
    v2 = @shaped_deriv * @shaped_deriv
    sign = @shaped_deriv <=> 0  # +1 up, -1 down, 0 neutral
    THRUST_COEFF * v2 * sign * THRUST_LEVER
  end
end

# ─── PID ──────────────────────────────────────────────────────────────────────

class PID
  def initialize(kp:, ki:, kd:)
    @kp, @ki, @kd = kp, ki, kd
    @integral = 0.0
    @prev_err = 0.0
  end

  def step(error)
    @integral += error * DT
    @integral = @integral.clamp(-5.0, 5.0)
    deriv = (error - @prev_err) / DT
    @prev_err = error
    @kp * error + @ki * @integral + @kd * deriv
  end

  def reset
    @integral = 0.0
    @prev_err = 0.0
  end
end

# ─── Stroke-Synchronous Feed-Forward ──────────────────────────────────────────

class StrokeFF
  attr_reader :f_down_bias, :f_up_bias

  def initialize
    @f_down_bias = 0.0
    @f_up_bias   = 0.0
    @prev_sin    = nil
    @accum_error = 0.0
    @accum_count = 0
  end

  def update(sin_theta, pitch_error, base_f_down, base_f_up)
    crossing = @prev_sin && (@prev_sin * sin_theta <= 0) && (@prev_sin != sin_theta)

    if crossing
      if @accum_count > 0
        mean_err = @accum_error / @accum_count

        if @prev_sin > 0  # just finished downstroke
          @f_up_bias = K_FF * mean_err
        else               # just finished upstroke
          @f_down_bias = -K_FF * mean_err
        end
      end

      @accum_error = 0.0
      @accum_count = 0
    end

    @accum_error += pitch_error
    @accum_count += 1
    @prev_sin = sin_theta

    fd = (base_f_down + @f_down_bias).clamp(F_MIN, F_MAX)
    fu = (base_f_up   + @f_up_bias).clamp(F_MIN, F_MAX)
    [fd, fu]
  end
end

# ─── Vold–Kalman Order Tracker ───────────────────────────────────────────────
# 1st-generation VK bandpass: extracts the component at order k of the
# *instantaneous* frequency omega(t). Bandwidth 2ζ·kω, zero phase at center.
# "Transient clock re-organization": the filter center follows the flap clock
# instead of a fixed lab frequency.  (Firmware port: 2 biquads, coefficients
# updated once per cycle from ornithopterFlapping.omega.)

class OrderTracker
  def initialize(order: 1, zeta: 0.06)
    @k    = order
    @zeta = zeta
    @x    = 0.0
    @v    = 0.0
  end

  def step(sample, omega)
    w  = @k * omega
    bw = 2.0 * @zeta * w
    @v += (-w * w * @x - 2.0 * @zeta * w * @v + bw * sample) * DT
    @x += @v * DT
    @x
  end
end

class FixedBandpass
  def initialize(center_omega:, zeta: 0.06)
    @w    = center_omega
    @zeta = zeta
    @x    = 0.0
    @v    = 0.0
  end

  def step(sample, _omega)
    w  = @w
    bw = 2.0 * @zeta * w
    @v += (-w * w * @x - 2.0 * @zeta * w * @v + bw * sample) * DT
    @x += @v * DT
    @x
  end
end

# ─── Airframe ─────────────────────────────────────────────────────────────────

class Airframe
  attr_accessor :pitch, :pitch_rate

  def initialize(pitch: 0.0, rate: 0.0)
    @pitch = pitch
    @pitch_rate = rate
  end

  def step(moment, gust: 0.0)
    accel = (moment - PITCH_DAMP * @pitch_rate) / I_YY + gust
    @pitch_rate += accel * DT
    @pitch      += @pitch_rate * DT
  end
end

# ─── Simulation Runner ────────────────────────────────────────────────────────

def run_simulation(duration:, f_down_base:, f_up_base:, ff_enabled:, gust_t: 1.0, gust_mag: 8.0)
  wing   = Wing.new(f_down: f_down_base, f_up: f_up_base)
  pid    = PID.new(kp: PID_KP, ki: PID_KI, kd: PID_KD)
  frame  = Airframe.new
  ff     = StrokeFF.new if ff_enabled

  results = []
  steps = (duration / DT).to_i

  steps.times do |i|
    t = i * DT

    if ff_enabled
      pitch_err = -frame.pitch
      wing.f_down, wing.f_up = ff.update(wing.sin_theta, pitch_err, f_down_base, f_up_base)
    end

    wing.step(0.6)

    gust = (t >= gust_t && t < gust_t + 0.1) ? gust_mag : 0.0

    pitch_error = -frame.pitch
    pid_raw = pid.step(pitch_error)

    # ONDAS-gated PID
    pid_gated = pid_raw * (0.5 + ONDAS_GAIN * wing.ondas_attn * 0.1)

    total_moment = pid_gated + wing.position_moment + wing.thrust_pitch_moment

    frame.step(total_moment, gust: gust)

    results << [t, frame.pitch, frame.pitch_rate, wing.f_down, wing.f_up,
                wing.shaped, wing.ondas_attn, wing.shaped_deriv, wing.dshaped_dtheta,
                wing.thrust_pitch_moment, pid_raw, pid_gated, total_moment]
  end

  results
end

def metrics(results, skip_s: 0.5)
  skip = (skip_s / DT).to_i
  data = results[skip..]
  pitches = data.map { |r| r[1] }
  rates   = data.map { |r| r[2] }
  rms_pitch = Math.sqrt(pitches.map { |x| x**2 }.sum / pitches.size)
  rms_rate  = Math.sqrt(rates.map { |x| x**2 }.sum / rates.size)
  max_pitch = pitches.map(&:abs).max
  { rms_pitch: rms_pitch, rms_rate: rms_rate, max_pitch: max_pitch }
end

# ─── Modes ────────────────────────────────────────────────────────────────────

def mode_wave(args)
  fd = param_to_f(args[1] || 50)
  fu = param_to_f(args[2] || 50)
  puts "ferocity,angle,sin_theta,shaped,dshaped_dtheta,ondas_attn"

  wing = Wing.new(f_down: fd, f_up: fu)
  (0..360).step(2) do |deg|
    wing.theta = deg * Math::PI / 180.0
    wing.omega = 30.0  # arbitrary for static analysis
    wing.step(1.0)
    avg_f = (fd + fu) / 2.0
    puts [avg_f.round(1), deg, wing.sin_theta.round(4), wing.shaped.round(4),
          wing.dshaped_dtheta.round(4), wing.ondas_attn.round(4)].join(',')
  end
end

def mode_compare(args)
  fd = param_to_f(args[1] || 50)
  fu = param_to_f(args[2] || 50)
  dur = (args[3] || 5.0).to_f

  puts "# Stroke-Synchronous Feed-Forward vs Fixed Ferocity"
  puts "# Base: F_down=#{fd.round(2)} F_up=#{fu.round(2)}"
  puts

  r_fixed = run_simulation(duration: dur, f_down_base: fd, f_up_base: fu, ff_enabled: false)
  m_fixed = metrics(r_fixed)

  r_ssff = run_simulation(duration: dur, f_down_base: fd, f_up_base: fu, ff_enabled: true)
  m_ssff = metrics(r_ssff)

  puts "%-12s %12s %12s %12s" % ["Mode", "RMS Pitch(°)", "RMS Rate(°/s)", "Max Pitch(°)"]
  puts "%-12s %12.4f %12.4f %12.4f" % ["Fixed", m_fixed[:rms_pitch], m_fixed[:rms_rate], m_fixed[:max_pitch]]
  puts "%-12s %12.4f %12.4f %12.4f" % ["SSFF", m_ssff[:rms_pitch], m_ssff[:rms_rate], m_ssff[:max_pitch]]

  if m_ssff[:rms_pitch] < m_fixed[:rms_pitch]
    pct = ((1.0 - m_ssff[:rms_pitch] / m_fixed[:rms_pitch]) * 100).round(1)
    puts
    puts "✓ SSFF reduces pitch RMS by #{pct}%"
  end

  puts
  puts "# Detailed CSV: t, pitch_fixed, pitch_ssff, f_down_ssff, f_up_ssff, shaped, ondas_attn, thrust_moment"
  step = 10
  (0...[r_fixed.size, r_ssff.size].min).step(step) do |i|
    tf, pf, prf, _, _, _, oaf, _, _, _, _, _, _ = r_fixed[i]
    _, ps, prs, fd_s, fu_s, shaped, ondas, _, _, thrust, _, _, _ = r_ssff[i]
    puts [tf.round(4), pf.round(5), ps.round(5), fd_s.round(3), fu_s.round(3),
          shaped.round(4), ondas.round(4), thrust.round(5)].join(',')
  end
end

def mode_flight(args)
  fd = param_to_f(args[1] || 50)
  fu = param_to_f(args[2] || 50)
  dur = (args[3] || 5.0).to_f
  ff = args[4] != 'nossff'

  results = run_simulation(duration: dur, f_down_base: fd, f_up_base: fu, ff_enabled: ff)
  m = metrics(results)

  puts "# Flight: F_down=#{fd.round(2)} F_up=#{fu.round(2)} SSFF=#{ff}"
  puts "RMS Pitch: #{m[:rms_pitch].round(4)}°  RMS Rate: #{m[:rms_rate].round(4)}°/s  Max: #{m[:max_pitch].round(4)}°"
  puts
  puts "t,pitch,rate,f_down,f_up,shaped,ondas_attn,shaped_deriv,thrust_moment,pid_raw,pid_gated,total_moment"

  results.each_with_index do |r, i|
    next unless i % 10 == 0
    puts r.map { |v| v.is_a?(Float) ? v.round(5) : v }.join(',')
  end
end

def mode_sweep(args)
  puts "fd,fu,rms_pitch,rms_rate,max_pitch"

  # Sweep over param values 1..100 → float 0..8
  [1, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100].each do |fdi|
    [1, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100].each do |fui|
      fd = param_to_f(fdi)
      fu = param_to_f(fui)
      r = run_simulation(duration: 4.0, f_down_base: fd, f_up_base: fu, ff_enabled: false)
      m = metrics(r)
      puts [fdi, fui, m[:rms_pitch].round(6), m[:rms_rate].round(6), m[:max_pitch].round(6)].join(',')
    end
  end
end

def mode_derive(args)
  fd = param_to_f(args[1] || 50)
  fu = param_to_f(args[2] || 50)
  omega = (args[3] || 30.0).to_f

  puts "# Derivative analysis (trapezoidal): ω=#{omega} rad/s"
  puts "ferocity,angle,sin_theta,shaped,dshaped_dtheta,wing_velocity"

  [0.0, 1.0, 2.0, 4.0, 6.0, 8.0].each do |f|
    wing = Wing.new(f_down: f, f_up: f, theta: 0.0)
    (0..360).step(2) do |deg|
      wing.theta = deg * Math::PI / 180.0
      wing.omega = omega
      wing.step(1.0)
      wv = wing.dshaped_dtheta * omega    # actual wing angular velocity
      puts [f.round(1), deg, wing.sin_theta.round(4), wing.shaped.round(4),
            wing.dshaped_dtheta.round(4), wv.round(4)].join(',')
    end
  end
end

def mode_prize(args)
  puts "╔══════════════════════════════════════════════════════════════════╗"
  puts "║  Unified ONDAS + Ferocity Theory (Trapezoidal)                  ║"
  puts "║  ─────────────────────────────────────────                      ║"
  puts "║  1. Trapezoidal wave: dwell at ±1 for d/2, cos ramp between    ║"
  puts "║     d = f/8 ∈ [0,1].  f=0 → pure cosine, f=8 → pure square    ║"
  puts "║  2. Shared limiar from raw ferocities — stable stroke reversal ║"
  puts "║  3. Derivative: 0 in dwell, ∓k·sin(ramp)·dt/dθ in ramp        ║"
  puts "║  4. Thrust ∝ velocity² — dwell → maximum force sustained       ║"
  puts "║  5. ONDAS window: attn = -|shaped| + 0.5 — gate at stroke edge║"
  puts "║  6. SSFF: per-stroke error integration → stroke-locked bias    ║"
  puts "╚══════════════════════════════════════════════════════════════════╝"
  puts

  fd_base = param_to_f(args[1] || 60)
  fu_base = param_to_f(args[2] || 60)

  # 1. Wave shape comparison
  puts "═══ Wave Shape: F=0 vs F=#{fd_base.round(1)} ═══"
  puts "angle,sin,F0,Fhigh,F0_ondas,Fhigh_ondas"
  wing0 = Wing.new(f_down: 0.0, f_up: 0.0, theta: 0.0)
  wingH = Wing.new(f_down: fd_base, f_up: fu_base, theta: 0.0)
  (0..360).step(5) do |deg|
    wing0.theta = deg * Math::PI / 180.0
    wingH.theta = deg * Math::PI / 180.0
    wing0.omega = 30.0
    wingH.omega = 30.0
    wing0.step(1.0)
    wingH.step(1.0)
    puts [deg, wing0.sin_theta.round(4), wing0.shaped.round(4), wingH.shaped.round(4),
          wing0.ondas_attn.round(4), wingH.ondas_attn.round(4)].join(',')
  end

  # 2. Velocity amplification
  puts
  puts "═══ Velocity Amplification by Ferocity ═══"
  puts "At θ=6° (stroke start), ω=30 rad/s:"
  puts "%-8s %-10s %-14s %-10s %-14s" % ["F", "shaped", "dShaped/dθ", "wing_vel", "thrust"]
  [0.0, 1.0, 2.0, 4.0, 8.0].each do |f|
    wing = Wing.new(f_down: f, f_up: f, theta: 6.0 * Math::PI / 180.0, omega: 30.0)
    wing.step(1.0)
    wv = wing.dshaped_dtheta * wing.omega
    puts "  %-6s %-10s %-14s %-10s %-14s" % [
      f.round(1), wing.shaped.round(4), wing.dshaped_dtheta.round(3),
      "#{wv.round(1)} rad/s", "#{((wv*wv*THRUST_COEFF*THRUST_LEVER)*1000).round(1)} mN·m"
    ]
  end
  puts
  puts "  ↑ F=8 gives square-wave: velocity spikes to ∞ at transition, sustained at extremes."
  puts "  F=0 gives pure cosine: smooth transition, no dwell, velocity continuous."

  # 3. Stability comparison
  puts
  puts "═══ Stability: Fixed vs SSFF (with CG offset + gust) ═══"
  cg_offset = 0.5

  %w[fixed ssff].each do |mode|
    wing   = Wing.new(f_down: fd_base, f_up: fu_base)
    pid    = PID.new(kp: PID_KP, ki: PID_KI, kd: PID_KD)
    frame  = Airframe.new
    ff     = StrokeFF.new if mode == 'ssff'

    i_terms = []
    results = []
    steps = (5.0 / DT).to_i

steps.times do |i|
  t = i * DT

  if mode == 'ssff'
    pitch_err = -frame.pitch
    wing.f_down, wing.f_up = ff.update(wing.sin_theta, pitch_err, fd_base, fu_base)
  end

      wing.step(0.6)

      gust = (t >= 1.0 && t < 1.15) ? 15.0 : 0.0

      pitch_error = -frame.pitch
      pid_raw = pid.step(pitch_error)
      pid_gated = pid_raw * (0.5 + ONDAS_GAIN * wing.ondas_attn * 0.1)
      total_moment = pid_gated + wing.position_moment + wing.thrust_pitch_moment + cg_offset
      frame.step(total_moment, gust: gust)

      i_terms << pid.instance_variable_get(:@integral)
      results << [t, frame.pitch, frame.pitch_rate, wing.f_down, wing.f_up,
                  wing.shaped, wing.ondas_attn, pid_raw, pid_gated]
    end

    m = metrics(results)
    i_final = i_terms.last
    i_abs_mean = i_terms.map(&:abs).sum / i_terms.size
    puts "%-10s  RMS pitch: %8.4f°  RMS rate: %8.4f°/s  Max: %8.4f°  |I|: %8.4f  I_final: %8.4f" % [
      mode == 'ssff' ? "SSFF" : "Fixed", m[:rms_pitch], m[:rms_rate], m[:max_pitch], i_abs_mean, i_final
    ]

    if mode == 'ssff'
      @ssff_results = results
      @ssff_i_terms = i_terms
    else
      @fixed_results = results
      @fixed_i_terms = i_terms
    end
  end

  puts
  puts "═══ I-term Windup Comparison ═══"
  puts "t,i_fixed,i_ssff"
  (0...[@fixed_i_terms.size, @ssff_i_terms.size].min).step(20) do |i|
    puts [@fixed_results[i][0].round(3), @fixed_i_terms[i].round(5), @ssff_i_terms[i].round(5)].join(',')
  end

  puts
  puts "═══ SSFF Ferocity Modulation ═══"
  puts "t,f_down,f_up,pitch"
  @ssff_results[0..3000].each_with_index do |r, i|
    next unless i % 20 == 0
    puts [r[0].round(3), r[3].round(3), r[4].round(3), r[1].round(4)].join(',')
  end
end

# ─── Harmonize: Vold–Kalman order tracking vs fixed bandpass ─────────────────
# Throttle chirp makes the flap frequency wander; the lab clock (1 kHz) and the
# flap clock are incommensurate → Poincaré histogram covers the phase circle
# ergodically ("serendipity constellation" — free phase coverage, no dither).

def mode_harmonize(args)
  dur           = (args[1] || 10.0).to_f
  throttle_base = (args[2] || 0.6).to_f
  sweep_amp     = (args[3] || 0.3).to_f
  sweep_period  = (args[4] || 6.0).to_f
  zeta          = (args[5] || 0.06).to_f
  f_base        = (args[6] || 0.2424).to_f

  wing  = Wing.new(f_down: f_base, f_up: f_base)
  frame = Airframe.new
  pid   = PID.new(kp: PID_KP, ki: PID_KI, kd: PID_KD)

  mean_w = K0 / K2 * throttle_base

  vk    = OrderTracker.new(order: 1, zeta: zeta)
  fixed = FixedBandpass.new(center_omega: mean_w, zeta: zeta)

  nbins = 16
  hist_count = Array.new(nbins, 0)
  hist_err   = Array.new(nbins, 0.0)
  histg_count = Array.new(nbins, 0)
  histg_err   = Array.new(nbins, 0.0)
  hist_err_vk    = Array.new(nbins, 0.0)
  hist_err_fixed = Array.new(nbins, 0.0)
  prev_sin = nil
  golden_idx = 0

  rms_vk = rms_fixed = 0.0
  amp_vk = amp_fixed = amp_true = 0.0
  corr_vk = corr_fixed = var_sig = 0.0
  n = 0

  # λ_e(s) rearrangement histogram (Tao 247A Notes 1): 32 log-spaced level
  # bins over |residual| — the distribution function λ(s) = #{|e| > s}/N,
  # from which the weak-L² norm ‖e‖₂,∞ = sup s·√λ(s) follows (tail-sensitive,
  # unlike RMS which is blind to detuning spikes)
  r_nb   = 32
  r_min  = 0.0005   # rad (0.03°)
  r_max  = 2.0      # rad (115°)
  r_lgr  = Math.log(r_max / r_min) / (r_nb - 1)
  hist_lam_vk    = Array.new(r_nb, 0)
  hist_lam_fixed = Array.new(r_nb, 0)
  max_resid_vk = max_resid_fixed = 0.0

  # warm-up: wing spins up from ω=0 (real flap never does) and the
  # extractors (Q=1/2ζ) need ~1/(ζω) to settle — skip both in the metrics
  warmup = (3.0 / DT).to_i

  steps = (dur / DT).to_i
  steps.times do |i|
    t = i * DT
    # triangle chirp (constant dω/dt) — sine dwells at the extremes and
    # biases the Poincaré histogram toward the low-ω phase bins
    phase_frac = (t / sweep_period) % 1.0
    tri = 4.0 * (phase_frac < 0.5 ? phase_frac : 1.0 - phase_frac) - 1.0
    throttle = (throttle_base + sweep_amp * tri).clamp(0.1, 1.0)

    wing.step(throttle)

    pitch_error = -frame.pitch
    pid_raw = pid.step(pitch_error)
    pid_gated = pid_raw * (0.5 + ONDAS_GAIN * wing.ondas_attn * 0.1)
    total_moment = pid_gated + wing.position_moment + wing.thrust_pitch_moment
    frame.step(total_moment)

    w = wing.omega
    e_vk    = vk.step(pitch_error, w)
    e_fixed = fixed.step(pitch_error, w)

    if i >= warmup
      proxy   = wing.shaped  # flap-synchronous disturbance proxy

      rms_vk    += (pitch_error - e_vk)**2
      rms_fixed += (pitch_error - e_fixed)**2
      amp_vk    += e_vk**2
      amp_fixed += e_fixed**2
      amp_true  += proxy**2
      corr_vk    += e_vk * proxy
      corr_fixed += e_fixed * proxy
      var_sig    += proxy**2
      n += 1

      resid_vk    = (pitch_error - e_vk).abs
      resid_fixed = (pitch_error - e_fixed).abs
      b = resid_vk >= r_min ? [(Math.log(resid_vk / r_min) / r_lgr).floor + 1, r_nb - 1].min : 0
      hist_lam_vk[b] += 1
      b = resid_fixed >= r_min ? [(Math.log(resid_fixed / r_min) / r_lgr).floor + 1, r_nb - 1].min : 0
      hist_lam_fixed[b] += 1
      max_resid_vk    = resid_vk    if resid_vk    > max_resid_vk
      max_resid_fixed = resid_fixed if resid_fixed > max_resid_fixed

      bin = ((wing.theta % TWO_PI) / TWO_PI * nbins).floor % nbins
      hist_count[bin] += 1
      hist_err[bin]   += pitch_error
      hist_err_vk[bin]    += pitch_error - e_vk
      hist_err_fixed[bin] += pitch_error - e_fixed

      # golden-angle stroboscope: one sample per stroke reversal, bin index
      # rotates by the phyllotaxis constant each cycle — uniform phase
      # coverage even when the lab/flap clocks are near-commensurate
      if prev_sin && (prev_sin * wing.sin_theta < 0)
        golden_idx += 1
        bin_g = (golden_idx * GOLDEN_CONJUGATE % 1.0 * nbins).floor % nbins
        histg_count[bin_g] += 1
        histg_err[bin_g]   += pitch_error
      end
      prev_sin = wing.sin_theta
    end
  end

  rms_vk    = Math.sqrt(rms_vk / n)
  rms_fixed = Math.sqrt(rms_fixed / n)

  # weak-L² norm from the survival function: walk bins from the top,
  # c = #{|e| ≥ s_b}, candidate = s_b·√(c/n) — sup over all levels
  lam = ->(hist) do
    c = 0
    best = 0.0
    (r_nb - 1).downto(1) do |b|
      c += hist[b]
      cand = r_min * Math.exp(r_lgr * b) * Math.sqrt(c.to_f / n)
      best = cand if cand > best
    end
    best
  end
  q90 = ->(hist) do
    c = 0
    (r_nb - 1).downto(1) do |b|
      c += hist[b]
      return r_min * Math.exp(r_lgr * b) if c.to_f / n >= 0.10
    end
    0.0
  end
  tail_frac = ->(hist, thr) do
    c = 0
    (r_nb - 1).downto(1) do |b|
      break if r_min * Math.exp(r_lgr * b) < thr
      c += hist[b]
    end
    c.to_f / n
  end

  wl2_vk    = lam.call(hist_lam_vk)
  wl2_fixed = lam.call(hist_lam_fixed)
  q90_vk    = q90.call(hist_lam_vk)
  q90_fixed = q90.call(hist_lam_fixed)

  # phase-demodulated error envelope: rearrange the 16 phase-bin means —
  # this is the flap-SYNCHRONOUS residual, the quantity that actually
  # discriminates extractors (the raw residual λ(s) is broadband-dominated)
  phase_env = ->(err_sum) do
    means = nbins.times.map { |b| (err_sum[b] / [hist_count[b], 1].max).abs }.sort.reverse
    best = 0.0
    means.each_with_index do |m, k|
      cand = m * Math.sqrt((k + 1).to_f / nbins)
      best = cand if cand > best
    end
    best
  end
  pe_vk    = phase_env.call(hist_err_vk)
  pe_fixed = phase_env.call(hist_err_fixed)

  puts "═══ Oscillation Harmonization: Vold–Kalman vs fixed bandpass ═══"
  puts "throttle base #{throttle_base}, sweep ±#{sweep_amp} / #{sweep_period}s, dur #{dur}s"
  w_lo = K0 / K2 * (throttle_base - sweep_amp)
  w_hi = K0 / K2 * (throttle_base + sweep_amp)
  puts "flap ω #{format('%.2f', w_lo)}–#{format('%.2f', w_hi)} rad/s (fixed BP centered at #{format('%.2f', mean_w)}), ζ = #{zeta}"
  puts
  puts format("%-14s %18s %16s %18s %20s", "extractor", "amplitude fidelity", "corr ρ (shaped)", "residual RMS (°)", "rel. extraction")
  puts format("%-14s %18.3f %16.3f %18.3f %20.1f",
              "Vold–Kalman",
              Math.sqrt(amp_vk / amp_true),
              corr_vk / Math.sqrt(var_sig * amp_vk),
              rms_vk * 180.0 / Math::PI,
              Math.sqrt(amp_vk / amp_fixed))
  puts format("%-14s %18.3f %16.3f %18.3f %20.1f",
              "fixed BP",
              Math.sqrt(amp_fixed / amp_true),
              corr_fixed / Math.sqrt(var_sig * amp_fixed),
              rms_fixed * 180.0 / Math::PI,
              1.0)
  puts
  puts "(residual includes extractor ringing transients — amplitude fidelity and corr ρ are the discrimination metrics)"

  puts
  puts "─── λ_e(s) rearrangement analysis (Tao 247A Notes 1) ───"
  puts "#{r_nb} log-spaced level bins over |residual|, [#{format('%.4f', r_min)}..#{r_max}] rad"
  puts
  puts format("%-14s %16s %12s %12s %14s", "extractor", "‖e‖₂,∞ (°)", "q90 (°)", "max (°)", "tail > 0.2 rad")
  puts format("%-14s %16.3f %12.3f %12.3f %13.1f%%",
              "Vold–Kalman", wl2_vk * 180.0 / Math::PI, q90_vk * 180.0 / Math::PI,
              max_resid_vk * 180.0 / Math::PI, tail_frac.call(hist_lam_vk, 0.2) * 100)
  puts format("%-14s %16.3f %12.3f %12.3f %13.1f%%",
              "fixed BP", wl2_fixed * 180.0 / Math::PI, q90_fixed * 180.0 / Math::PI,
              max_resid_fixed * 180.0 / Math::PI, tail_frac.call(hist_lam_fixed, 0.2) * 100)
  puts
  puts "discrimination: weak-L² ratio VK/fixed = #{format('%.3f', wl2_vk / wl2_fixed)} (RMS ratio = #{format('%.3f', rms_vk / rms_fixed)})"
  puts "(weak-L² weights rare tail events; RMS averages them away — the metric B will use in-flight)"
  puts
  puts "phase-envelope ‖⟨e⟩_θ‖₂,∞ (flap-synchronous residual, the real discriminator):"
  puts format("  Vold–Kalman %8.3f°   fixed BP %8.3f°   → ratio %6.3f",
              pe_vk * 180.0 / Math::PI, pe_fixed * 180.0 / Math::PI, pe_vk / pe_fixed)
  puts "(smaller = better harmonization: less flap-locked error left in the residual)"

  puts
  puts "─── Poincaré phase histogram (16 bins, phase mod 2π) ───"
  puts "bin  count  mean_err(°)"
  nbins.times do |b|
    mean_b = hist_err[b] / [hist_count[b], 1].max * 180.0 / Math::PI
    puts format("%3d %6d %12.4f", b, hist_count[b], mean_b)
  end
  cmin = hist_count.min
  cmax = hist_count.max
  puts
  puts "phase coverage (serendipity check): bins #{cmin}–#{cmax} → uniformity #{format('%.3f', cmin.to_f / cmax)}"
  puts "(coverage limited by the clock beat: full uniformity needs ~1/|fractional detuning| cycles)"
  cg_min = histg_count.min
  cg_max = histg_count.max
  puts
  puts "golden-angle stroboscope (1 sample per stroke reversal, {k·0.618} rotation):"
  puts "bins #{cg_min}–#{cg_max} → uniformity #{format('%.3f', cg_min.to_f / cg_max)} over #{golden_idx} strokes"
  puts "(phyllotaxis constellation — deterministic coverage, immune to clock commensurability)"
end

# ─── Phase-Lock: ferocity dwell takes over chaotic wind ──────────────────────
# Thesis: ferocity is a LOCAL clock shift (Taktverschiebung). The dwell parks
# the wing at stroke reversal = a phase-resetting event. The reversal grid MOVES
# at the free flap rate ω, so the dwell well lives in the ERROR frame δ = θ − ωt,
# not the lab frame:
#     dδ/dt = η(t) − 2κ·d·sin(2δ)
#   δ = phase error (pendulum phase vs free-running reversal grid)
#   η = wind phase noise (chaotic detuning)
#   d = ferocity dwell fraction ∈ [0,1], κ = dwell→coupling strength
# d=0 → δ is a free random walk (wind owns the clock, unbounded over time).
# d>0 → the dwell well confines δ near a reversal (ferocity owns the clock).
# Commensurability link: wind detunes the flap clock, breaking per-sample phase
# coverage; dwell re-anchors δ, restoring a stable clock for the Poincaré sampler.

def mode_phaselock(args)
  dur    = (args[1] || 20.0).to_f
  omega  = (args[2] || 4.8).to_f
  kappa  = (args[3] || 8.0).to_f
  sigma  = (args[4] || 0.6).to_f
  dwells = (args[5] ? args[5].split(',') : %w[0 0.05 0.15 0.3 0.5 0.8]).map(&:to_f)

  puts "═══ Ferocity Phase-Lock: dwell takes over chaotic wind ═══"
  puts "pendulum phase ω #{omega} rad/s, dwell→coupling κ #{kappa}, wind σ #{sigma} rad/s, #{dur}s"
  puts "(rotating frame: δ = phase error vs free-running reversal grid)"
  puts
  puts format("%-8s %16s %16s %14s", "dwell d", "phase std δ (rad)", "max |δ| (rad)", "wind-to-lock")
  puts "-" * 56

  std0 = nil
  dwells.each do |d|
    delta = 0.0
    prev  = 0.0
    slips = 0
    offs  = []
    n = (dur / DT).to_i
    srand(1)
    n.times do
      eta = randn(0.0, sigma)
      delta += (eta - 2.0 * kappa * d * Math.sin(2.0 * delta)) * DT
      offs << delta
      slips += 1 if (delta - prev).abs > Math::PI / 2.0
      prev = delta
    end
    std = Math.sqrt(offs.map { |o| o**2 }.sum / offs.size)
    std0 ||= std
    gain = d.zero? ? "—" : format("%.1f×", std0 / std)
    puts format("%-8.2f %16.4f %16.4f %14s", d, std, offs.map(&:abs).max, gain)
  end

  puts
  puts "d=0 (pure cos) → wind owns the clock: δ random-walks, unbounded over time."
  puts "d>0 → dwell parking-well confines δ near a reversal → ferocity owns the clock."

  puts
  puts "─── ferocity = clock shift (reversal-point translation) ───"
  puts format("%-8s %8s %12s %14s", "f_down", "f_up", "limiar(°)", "reversal shift")
  [0.0, 2.0, 4.0, 8.0].each do |fd|
    [8.0, 0.0].each do |fu|
      w_d = [FEROCITY_RANGE - fd, 0.01].max
      w_u = [FEROCITY_RANGE - fu, 0.01].max
      lim = TWO_PI * w_d / (w_d + w_u)
      puts format("%-8.1f %8.1f %12.1f %14.1f°", fd, fu, lim * 180.0 / Math::PI,
                  (lim - Math::PI) * 180.0 / Math::PI)
    end
  end
  puts
  puts "ferocity asymmetry translates the reversal point limiar away from 180° — the"
  puts "local clock shift (Taktverschiebung). Its dwell well is what re-anchors the"
  puts "pendulum phase against the wind's detuning."
end

# ─── Main ─────────────────────────────────────────────────────────────────────

mode = ARGV[0] || 'help'

case mode
when 'wave'   then mode_wave(ARGV)
when 'derive' then mode_derive(ARGV)
when 'flight' then mode_flight(ARGV)
when 'compare' then mode_compare(ARGV)
when 'sweep'  then mode_sweep(ARGV)
when 'harmonize' then mode_harmonize(ARGV)
when 'phaselock' then mode_phaselock(ARGV)
when 'prize'  then mode_prize(ARGV)
else
  puts <<~USAGE
    ╔══════════════════════════════════════════════════════════════════╗
    ║  OrniFlight Ferocity + ONDAS Unified Simulation (Trapezoidal)   ║
    ╚══════════════════════════════════════════════════════════════════╝

    USAGE:
      ruby sim_ferocity.rb wave    [F_down] [F_up]
      ruby sim_ferocity.rb derive  [F_down] [F_up] [omega_rad_s]
      ruby sim_ferocity.rb flight  [F_down] [F_up] [dur] [nossff]
      ruby sim_ferocity.rb compare [F_down] [F_up] [dur]
      ruby sim_ferocity.rb sweep
      ruby sim_ferocity.rb harmonize [dur] [throttle_base] [sweep_amp] [sweep_period] [zeta] [f]
      ruby sim_ferocity.rb phaselock [dur] [omega] [kappa] [sigma] [dwells_csv]
      ruby sim_ferocity.rb prize   [F_down] [F_up]

    MODES:
      wave    — Static wave shape + ONDAS window over one cycle (trapezoidal)
      derive  — Velocity amplification by ferocity (dwell vs cos ramp)
      flight  — Full simulation (add 'nossff' for fixed ferocity)
      compare — Side-by-side fixed vs SSFF (CSV output)
      sweep   — Parameter scan over ferocity grid
      harmonize — Vold–Kalman order tracking vs fixed bandpass under throttle chirp
      phaselock — ferocity dwell as phase-locking coupling vs chaotic wind
      prize   — Full demonstration: theory + velocity analysis + comparison

    Ferocity params: 1-100 → maps to float 0.0-8.0 (matching firmware)
      f=0  → pure cosine, no dwell
      f=8  → pure square wave (sign of sinθ)
  USAGE
end