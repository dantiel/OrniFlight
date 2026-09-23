/*
 * ONDAS metrics — λ_e(s) statistical envelope ("B" substrate).
 *
 * Terence Tao, 247A Notes 1 (rearrangement-invariant spaces): the only
 * information the interpolation theorems need about an error signal e is its
 * distribution function λ_e(s) = μ({|e| > s}) — the oscillation itself is
 * deliberately ignored. This module implements that view as two running
 * statistics of one 32-bin log-level histogram:
 *
 *  (1) raw λ_e(s) over |I-term error| per axis  →  q90 (windup/D-cutoff),
 *      weak-L² = sup_s s·√λ(s) (robust RMS), tail mass above q90.
 *
 *  (2) phase-demodulated envelope ‖⟨e⟩_θ‖∞ over 16 Poincaré bins, sampled
 *      once per stroke reversal at golden-angle strobe phases. This is the
 *      discriminator the simulator found: raw λ_e(s) cannot tell extractors
 *      apart, the phase envelope can (ratio 1.013 vs 1.000). It is the
 *      regression metric for the future Vold–Kalman order tracker ("A").
 *
 * All state is static; the update cost is a 32-entry leak per axis per loop.
 */

#ifndef ONDAS_METRICS_H
#define ONDAS_METRICS_H

#include <stdbool.h>

void  ondasMetricsInit(void);
void  ondasMetricsUpdate(int axis, float errorAbs, float dT);
float ondasMetricsQuantile(int axis, float p);
float ondasMetricsWeakL2(int axis);
float ondasMetricsTailMass(int axis);
void  ondasMetricsPhaseStrobe(float errorAbs, bool strokeReversal);
float ondasMetricsPhaseEnvelope(void);
float ondasMetricsCoverage(void);

/* B-gate for the order tracker ("A"): consensus between two independent
 * coherent extractors of the same signal — the Vold–Kalman tracker output
 * and the ×sin(θ) lock-in reference. The correlation decides, with a
 * marcinkiewicz soft-knee and slow-in/fast-out authority, how far the
 * resonance boost may rotate toward the tracker's phase-true estimate. */
void  ondasMetricsGateUpdate(float trackerOut, float sinTheta, float dT);
float ondasMetricsGateAuthority(void);

#endif // ONDAS_METRICS_H