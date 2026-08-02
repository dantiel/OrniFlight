/*
 * Ornithopter flight profile — per-mode tuning parameters.
 * Activated via BOXORNITHOPTERPROFILE: splits AUX range into
 * equal segments (4 profiles with 3-pos switch).
 */

#pragma once

#include <stdint.h>
#include "pg/pg.h"

#define ORNITHOPTER_PROFILE_COUNT 4

typedef struct ornithopterProfile_s {
    // ── Base wave shape ──
    int8_t ferocity_downstroke;  // 1-100 → 1.0-8.0 ferocity on downstroke
    int8_t ferocity_upstroke;    // 1-100 → 1.0-8.0 ferocity on upstroke

    // ── Glide ──
    int8_t glide_angle;          // -90..+90°, servo angle in glide mode

    // ── ONDAS modulation gains ──
    int8_t cadence_gain;         // P-term → phase advance: "push harder now"
    int8_t ferocity_d_gain;      // D-term → ferocity: "dampen the motion" (signed)
    int8_t ferocity_p_gain;      // P-term → ferocity: "push proportionally"
    int8_t balance_gain;         // I-term → thrust symmetry: "trim the list"
    int8_t warp_gain;            // Roll P → L/R ferocity differential: "bank the wings"
    int8_t warp_yaw_gain;        // Yaw P → fore/aft ferocity differential: "turn the head"
    int8_t ferocity_roll_gain;   // Roll P → common-mode ferocity: "inertia gate for roll"
    int8_t ferocity_yaw_gain;    // Yaw P → common-mode ferocity: "inertia gate for yaw"

    // ── Wing ODE ──
    int8_t anchor_gain;          // k₂ damping coefficient: "lock the rhythm" (0=loose, 100=tight)

    // ── ONDAS advanced ──
    int8_t resonance_gain;       // phase-locked error filter: amplify flap-coherent error
    int8_t prescience_gain;      // stroke-ahead prediction: eliminate SSFF delay
    int8_t espelho_gain;         // wing-self-noise cancellation: subtract flap-coherent gyro
    int8_t saudade_gain;         // per-stroke learning: absorb persistent SSFF bias into trim
    int8_t ssff_gain;            // stroke-synchronous feed-forward

    // ── Aeroelastic PID scaling ──
    int8_t aeroelastic_glide_coefficient;
    int8_t aeroelastic_flap_coefficient;
} ornithopterProfile_t;

PG_DECLARE_ARRAY(ornithopterProfile_t, ORNITHOPTER_PROFILE_COUNT, ornithopterProfiles);

// Runtime helpers
uint8_t getOrnithopterProfileIndex(void);
const ornithopterProfile_t *currentOrnithopterProfile(void);
ornithopterProfile_t *currentOrnithopterProfileMutable(void);
void updateOrnithopterProfileFromBox(void); // called from PID loop to sync with BOX
uint8_t getOrnithopterProfileIndexMSP(void);
void setOrnithopterProfileIndexMSP(uint8_t index);
