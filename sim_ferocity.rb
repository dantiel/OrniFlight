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

# ─── Utility ──────────────────────────────────────────────────────────────────

def param_to_f(p) = ((p.to_i - 1) * FEROCITY_RANGE / 99.0).clamp(0.0, FEROCITY_RANGE)

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

# ─── Main ─────────────────────────────────────────────────────────────────────

mode = ARGV[0] || 'help'

case mode
when 'wave'   then mode_wave(ARGV)
when 'derive' then mode_derive(ARGV)
when 'flight' then mode_flight(ARGV)
when 'compare' then mode_compare(ARGV)
when 'sweep'  then mode_sweep(ARGV)
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
      ruby sim_ferocity.rb prize   [F_down] [F_up]

    MODES:
      wave    — Static wave shape + ONDAS window over one cycle (trapezoidal)
      derive  — Velocity amplification by ferocity (dwell vs cos ramp)
      flight  — Full simulation (add 'nossff' for fixed ferocity)
      compare — Side-by-side fixed vs SSFF (CSV output)
      sweep   — Parameter scan over ferocity grid
      prize   — Full demonstration: theory + velocity analysis + comparison

    Ferocity params: 1-100 → maps to float 0.0-8.0 (matching firmware)
      f=0  → pure cosine, no dwell
      f=8  → pure square wave (sign of sinθ)
  USAGE
end
