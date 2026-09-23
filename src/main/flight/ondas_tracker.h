/*
 * ONDAS order tracker ("A") — Vold–Kalman tracking bandpass.
 *
 * A 2nd-order resonator whose center frequency follows the instantaneous
 * flapping rate ω(t). Under frequency sweeps (throttle transients) a fixed
 * bandpass loses the flap band, while the order tracker keeps unity gain and
 * zero phase at the moving center — it extracts the flap-coherent signal
 * component with its true amplitude and phase, not just the in-phase part a
 * ×sin(θ) lock-in sees.
 *
 * Sim-validated in sim_ferocity.rb mode "harmonize": 2.5× extraction vs a
 * fixed bandpass under a 2.4→7.2 rad/s chirp, ρ preserved (−0.504 vs 0.001),
 * sanity 1.000 at constant ω. ζ = 0.06 (Q ≈ 8.3), order = 1 (w = ω).
 *
 * Discretization is explicit Euler — unconditionally stable at PID loop
 * rates for any flap frequency a wing can reach (w·dT ≪ √2).
 */

#ifndef ONDAS_TRACKER_H
#define ONDAS_TRACKER_H

typedef struct {
    float x;    // bandpass output — flap-coherent estimate
    float v;    // derivative state
} ondasTrackerState_t;

void  ondasTrackerReset(ondasTrackerState_t *t);
float ondasTrackerStep(ondasTrackerState_t *t, float sample, float omega, float dT);

#endif // ONDAS_TRACKER_H
