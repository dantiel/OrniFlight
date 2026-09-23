/*
 * ONDAS metrics — implementation. See ondas_metrics.h.
 *
 * Histogram: 32 log-spaced levels over [0.25, 256] deg/s (10 octaves),
 * exponential leak per sample with time constant ~1 s (leak shift adapted
 * to the loop period). Quantiles are interpolated within bins.
 *
 * Phase envelope: 16 Poincaré bins strobed once per stroke reversal at
 * golden-angle rotated phases (k·0.618…·16 mod 16) — deterministic
 * quasi-uniform phase coverage, immune to lab/flap clock commensurability.
 */

#include <stdint.h>
#include <math.h>

#include "common/axis.h"
#include "flight/ondas_metrics.h"

#define OM_BINS           32
#define OM_LEVEL_MIN      0.25f   // deg/s
#define OM_LEVEL_MAX      256.0f  // deg/s
#define OM_OCTAVES        10.0f   // log2(MAX / MIN)
#define OM_TAU_S          1.0f    // histogram leak time constant
#define OM_LEAK_SHIFT_MAX 20

#define OM_PHASE_BINS 16
#define OM_PHASE_EMA  0.0625f             // 1/16 per strobe
#define OM_GOLDEN_STEP 648095U            // 0.61803398875… · 16 · 2^16

#define OM_GATE_TAU_IN   1.0f   // engage time constant (s)
#define OM_GATE_TAU_OUT  0.4f   // disengage time constant (s) — fast out
#define OM_GATE_R_MIN    0.3f   // minimum extractor consensus to engage
#define OM_GATE_KNEE     0.25f  // soft-knee width of the engagement curve

static float    omLevel[OM_BINS + 1];
static uint32_t omHist[XYZ_AXIS_COUNT][OM_BINS];
static float    omPhaseMean[OM_PHASE_BINS];
static uint32_t omPhaseAcc;
static uint16_t omPhaseMask;
static float    omGateNum;    // EMA of trackerOut · sin(θ)
static float    omGateDen;    // EMA of sin²(θ)
static float    omGatePow;    // EMA of trackerOut²
static float    omGateAlpha;  // authority ∈ [−1, +1]

void ondasMetricsInit(void)
{
    const float ratio = powf(2.0f, OM_OCTAVES / OM_BINS);

    omLevel[0] = OM_LEVEL_MIN;
    for (int i = 0; i < OM_BINS; i++) {
        omLevel[i + 1] = omLevel[i] * ratio;
    }
    omLevel[OM_BINS] = OM_LEVEL_MAX; // exact upper edge

    omPhaseAcc = 0;
    omPhaseMask = 0;
    for (int i = 0; i < OM_PHASE_BINS; i++) {
        omPhaseMean[i] = 0.0f;
    }
    omGateNum = 0.0f;
    omGateDen = 0.0f;
    omGatePow = 0.0f;
    omGateAlpha = 0.0f;
}

static int omBin(float x)
{
    int i = 0;
    while (i < OM_BINS - 1 && x > omLevel[i + 1]) {
        i++;
    }
    return i;
}

static int omLeakShift(float dT)
{
    union {
        float    f;
        uint32_t i;
    } u;

    u.f = 1.0f / (dT * OM_TAU_S);
    int shift = (int)((u.i >> 23) & 0xFF) - 127; // floor(log2(u.f))
    if (shift < 1) {
        shift = 1;
    } else if (shift > OM_LEAK_SHIFT_MAX) {
        shift = OM_LEAK_SHIFT_MAX;
    }
    return shift;
}

void ondasMetricsUpdate(int axis, float errorAbs, float dT)
{
    if (dT <= 0.0f || axis < 0 || axis >= XYZ_AXIS_COUNT) {
        return;
    }

    const int      shift = omLeakShift(dT);
    const uint32_t inc   = 1U << shift;
    uint32_t *     h     = omHist[axis];

    for (int i = 0; i < OM_BINS; i++) {
        h[i] -= h[i] >> shift;
    }
    h[omBin(errorAbs)] += inc;
}

float ondasMetricsQuantile(int axis, float p)
{
    const uint32_t *h = omHist[axis];
    uint64_t total = 0;
    for (int i = 0; i < OM_BINS; i++) {
        total += h[i];
    }
    if (total == 0) {
        return omLevel[0];
    }

    const uint64_t target = (uint64_t)(p * (float)total + 0.5f);
    uint64_t cum = 0;
    for (int i = 0; i < OM_BINS; i++) {
        const uint64_t next = cum + h[i];
        if (next >= target && h[i] > 0) {
            const float frac = (float)(target - cum) / (float)h[i];
            return omLevel[i] + (omLevel[i + 1] - omLevel[i]) * frac;
        }
        cum = next;
    }
    return omLevel[OM_BINS];
}

float ondasMetricsWeakL2(int axis)
{
    const uint32_t *h = omHist[axis];
    uint64_t total = 0;
    for (int i = 0; i < OM_BINS; i++) {
        total += h[i];
    }
    if (total == 0) {
        return 0.0f;
    }

    float   best = 0.0f;
    uint64_t massAbove = total;
    for (int i = 0; i < OM_BINS; i++) {
        // λ(s) = P(|e| > s) at the lower edge of bin i
        const float wl2 = omLevel[i] * sqrtf((float)massAbove / (float)total);
        if (wl2 > best) {
            best = wl2;
        }
        massAbove -= h[i];
    }
    return best;
}

float ondasMetricsTailMass(int axis)
{
    const uint32_t *h = omHist[axis];
    uint64_t total = 0;
    for (int i = 0; i < OM_BINS; i++) {
        total += h[i];
    }
    if (total == 0) {
        return 0.0f;
    }

    const uint64_t target = total * 9 / 10;
    uint64_t cum = 0;
    int i;
    for (i = 0; i < OM_BINS; i++) {
        cum += h[i];
        if (cum >= target) {
            break;
        }
    }
    return (float)(total - cum) / (float)total;
}

void ondasMetricsPhaseStrobe(float errorAbs, bool strokeReversal)
{
    if (!strokeReversal) {
        return;
    }

    omPhaseAcc += OM_GOLDEN_STEP;
    const int bin = (int)((omPhaseAcc >> 16) % OM_PHASE_BINS);
    omPhaseMask |= (uint16_t)(1U << bin);

    for (int i = 0; i < OM_PHASE_BINS; i++) {
        omPhaseMean[i] *= (1.0f - OM_PHASE_EMA);
    }
    omPhaseMean[bin] += errorAbs * OM_PHASE_EMA;
}

float ondasMetricsPhaseEnvelope(void)
{
    float sup = 0.0f;
    for (int i = 0; i < OM_PHASE_BINS; i++) {
        const float m = fabsf(omPhaseMean[i]);
        if (m > sup) {
            sup = m;
        }
    }
    return sup;
}

float ondasMetricsCoverage(void)
{
    int n = 0;
    for (int i = 0; i < OM_PHASE_BINS; i++) {
        if (omPhaseMask & (1U << i)) {
            n++;
        }
    }
    return (float)n / (float)OM_PHASE_BINS;
}

void ondasMetricsGateUpdate(float trackerOut, float sinTheta, float dT)
{
    if (dT <= 0.0f) {
        return;
    }

    const float k = dT / OM_GATE_TAU_IN;
    omGateNum += (trackerOut * sinTheta - omGateNum) * k;
    omGateDen += (sinTheta * sinTheta - omGateDen) * k;
    omGatePow += (trackerOut * trackerOut - omGatePow) * k;

    // Consensus correlation r ∈ [−1, +1]: for trackerOut = A·sin(θ) the
    // three EMAs are A/2, 1/2, A²/2 → r = 1 exactly.
    const float denom = sqrtf(omGateDen * omGatePow);
    const float r = (denom > 1e-6f) ? omGateNum / denom : 0.0f;

    // Engagement: marcinkiewicz soft-knee above the consensus floor.
    const float mag = fabsf(r);
    const float eng = (mag > OM_GATE_R_MIN) ? (mag - OM_GATE_R_MIN) / (1.0f - OM_GATE_R_MIN) : 0.0f;
    const float knee = eng / sqrtf(eng * eng + OM_GATE_KNEE * OM_GATE_KNEE);
    const float target = (r < 0.0f) ? -knee : knee;

    // Authority: slow in, fast out. When the tracker loses the flap band
    // (r → 0) it is neutralized quickly; trust returns only with sustained
    // consensus.
    const float tau = (fabsf(target) > fabsf(omGateAlpha)) ? OM_GATE_TAU_IN : OM_GATE_TAU_OUT;
    omGateAlpha += (target - omGateAlpha) * (dT / tau);
}

float ondasMetricsGateAuthority(void)
{
    return omGateAlpha;
}