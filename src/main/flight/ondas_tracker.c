/*
 * ONDAS order tracker — implementation. See ondas_tracker.h.
 *
 * State: x (output), v (derivative). Coefficients are recomputed per sample
 * from the instantaneous ω, so the resonator rides the transient clock.
 */

#include <math.h>

#include "flight/ondas_tracker.h"

#define OT_ZETA      0.06f   // damping ratio — Q ≈ 8.3, sim-validated
#define OT_OMEGA_MIN 0.1f    // rad/s — below: no flapping, states idle

void ondasTrackerReset(ondasTrackerState_t *t)
{
    t->x = 0.0f;
    t->v = 0.0f;
}

float ondasTrackerStep(ondasTrackerState_t *t, float sample, float omega, float dT)
{
    if (omega < OT_OMEGA_MIN || dT <= 0.0f) {
        // No flapping: zero states. (With w = 0 the damping term vanishes and
        // x would drift linearly on the stale v — never let that happen.)
        ondasTrackerReset(t);
        return 0.0f;
    }

    const float w  = omega;                  // order = 1
    const float bw = 2.0f * OT_ZETA * w;     // unity gain at center

    t->v += (-w * w * t->x - bw * t->v + bw * sample) * dT;
    t->x += t->v * dT;
    return t->x;
}
