/*
 * Ornithopter flight profile implementation.
 */

#include <stdint.h>
#include "platform.h"
#include "fc/rc_modes.h"
#include "rx/rx.h"
#include "servos.h"
#include "ornithopter_profile.h"

static uint8_t activeProfileIndex;
static uint8_t mspProfileIndex;

PG_REGISTER_ARRAY_WITH_RESET_FN(ornithopterProfile_t, ORNITHOPTER_PROFILE_COUNT,
                                ornithopterProfiles, PG_ORNITHOPTER_PROFILES, 0);

void pgResetFn_ornithopterProfiles(ornithopterProfile_t *profile)
{
    for (int i = 0; i < ORNITHOPTER_PROFILE_COUNT; i++) {
        profile[i].ferocity_downstroke  = 12;  // ~1.78 — mild shaping, near-sine
        profile[i].ferocity_upstroke    = 12;
        profile[i].glide_angle          = -30; // -30° glide position

        profile[i].cadence_gain        = 0;
        profile[i].ferocity_d_gain     = 10;
        profile[i].ferocity_p_gain     = 10;
        profile[i].balance_gain        = 10;
        profile[i].warp_gain           = 10;
        profile[i].warp_yaw_gain       = 10;
        profile[i].ferocity_roll_gain  = 10;
        profile[i].ferocity_yaw_gain   = 10;

        profile[i].anchor_gain         = 10;

        profile[i].resonance_gain      = 0;
        profile[i].prescience_gain     = 0;
        profile[i].espelho_gain        = 0;
        profile[i].saudade_gain        = 0;
        profile[i].ssff_gain           = 0;

        profile[i].aeroelastic_glide_coefficient = 20;
        profile[i].aeroelastic_flap_coefficient  = 40;
    }
}

uint8_t getOrnithopterProfileIndex(void)
{
    return activeProfileIndex;
}

const ornithopterProfile_t *currentOrnithopterProfile(void)
{
    return ornithopterProfiles(activeProfileIndex);
}

ornithopterProfile_t *currentOrnithopterProfileMutable(void)
{
    return ornithopterProfilesMutable(activeProfileIndex);
}


uint8_t getOrnithopterProfileIndexMSP(void)
{
    return mspProfileIndex;
}

void setOrnithopterProfileIndexMSP(uint8_t index)
{
    if (index < ORNITHOPTER_PROFILE_COUNT) {
        mspProfileIndex = index;
    }
}

void updateOrnithopterProfileFromBox(void)
{
    const servoConfig_t *sc = servoConfig();
    uint8_t chanIdx = sc->ornithopter_profile_channel + 4; // +4 for AUX offset
    if (chanIdx >= MAX_SUPPORTED_RC_CHANNEL_COUNT)
        chanIdx = 5; // fallback AUX2

    uint16_t rcVal = rcData[chanIdx];

    // Split AUX range 1000-2000 into ORNITHOPTER_PROFILE_COUNT segments
    uint8_t newIndex;
    if (rcVal <= 1250) {
        newIndex = 0;
    } else if (rcVal <= 1500) {
        newIndex = 1;
    } else if (rcVal <= 1750) {
        newIndex = 2;
    } else {
        newIndex = 3;
    }

    activeProfileIndex = newIndex;
}