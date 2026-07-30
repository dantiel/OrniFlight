/*
 * This file is part of Cleanflight and Betaflight.
 *
 * Cleanflight and Betaflight are free software. You can redistribute
 * this software and/or modify this software under the terms of the
 * GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * Cleanflight and Betaflight are distributed in the hope that they
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "platform.h"

#include "build/build_config.h"
#include "build/debug.h"

#include "common/axis.h"
#include "common/filter.h"
#include "common/maths.h"

#include "config/feature.h"
#include "pg/pg.h"
#include "pg/pg_ids.h"
#include "pg/rx.h"

#include "drivers/pwm_output.h"
#include "drivers/pwm_esc_detect.h"
#include "drivers/time.h"
#include "drivers/io.h"

#include "io/motors.h"

#include "fc/config.h"
#include "fc/controlrate_profile.h"
#include "fc/rc_controls.h"
#include "fc/rc_modes.h"
#include "fc/runtime_config.h"
#include "fc/core.h"
#include "fc/rc.h"

#include "flight/failsafe.h"
#include "flight/imu.h"
#include "flight/gps_rescue.h"
#include "flight/mixer.h"
#include "flight/mixer_tricopter.h"
#include "flight/pid.h"

#include "rx/rx.h"

#include "sensors/battery.h"
#include "sensors/gyro.h"

PG_REGISTER_WITH_RESET_TEMPLATE(mixerConfig_t, mixerConfig, PG_MIXER_CONFIG, 0);

#define DYN_LPF_THROTTLE_STEPS           100
#define DYN_LPF_THROTTLE_UPDATE_DELAY_US 5000 // minimum of 5ms between updates

PG_RESET_TEMPLATE(mixerConfig_t, mixerConfig,
    .mixerMode = DEFAULT_MIXER,
    .yaw_motors_reversed = false,
    .crashflip_motor_percent = 0,
);

PG_REGISTER_WITH_RESET_FN(motorConfig_t, motorConfig, PG_MOTOR_CONFIG, 1);

void pgResetFn_motorConfig(motorConfig_t *motorConfig)
{
#ifdef BRUSHED_MOTORS
    motorConfig->minthrottle = 1000;
    motorConfig->dev.motorPwmRate = BRUSHED_MOTORS_PWM_RATE;
    motorConfig->dev.motorPwmProtocol = PWM_TYPE_BRUSHED;
    motorConfig->dev.useUnsyncedPwm = true;
#else
#ifdef USE_BRUSHED_ESC_AUTODETECT
    if (getDetectedMotorType() == MOTOR_BRUSHED) {
        motorConfig->minthrottle = 1000;
        motorConfig->dev.motorPwmRate = BRUSHED_MOTORS_PWM_RATE;
        motorConfig->dev.motorPwmProtocol = PWM_TYPE_BRUSHED;
        motorConfig->dev.useUnsyncedPwm = true;
    } else
#endif
    {
        motorConfig->minthrottle = 1070;
        motorConfig->dev.motorPwmRate = BRUSHLESS_MOTORS_PWM_RATE;
        motorConfig->dev.motorPwmProtocol = PWM_TYPE_ONESHOT125;
    }
#endif
    motorConfig->maxthrottle = 2000;
    motorConfig->mincommand = 1000;
    motorConfig->digitalIdleOffsetValue = 550;
#ifdef USE_DSHOT_DMAR
    motorConfig->dev.useBurstDshot = ENABLE_DSHOT_DMAR;
#endif

    for (int motorIndex = 0; motorIndex < MAX_SUPPORTED_MOTORS; motorIndex++) {
        motorConfig->dev.ioTags[motorIndex] = timerioTagGetByUsage(TIM_USE_MOTOR, motorIndex);
    }

    motorConfig->motorPoleCount = 14;   // Most brushes motors that we use are 14 poles
}

PG_REGISTER_ARRAY(motorMixer_t, MAX_SUPPORTED_MOTORS, customMotorMixer, PG_MOTOR_MIXER, 0);

#define PWM_RANGE_MID 1500

static FAST_RAM_ZERO_INIT uint8_t motorCount;
static FAST_RAM_ZERO_INIT float motorMixRange;

float FAST_RAM_ZERO_INIT motor[MAX_SUPPORTED_MOTORS];
float motor_disarmed[MAX_SUPPORTED_MOTORS];

mixerMode_e currentMixerMode;
static motorMixer_t currentMixer[MAX_SUPPORTED_MOTORS];

#ifdef USE_LAUNCH_CONTROL
static motorMixer_t launchControlMixer[MAX_SUPPORTED_MOTORS];
#endif

static FAST_RAM_ZERO_INIT int throttleAngleCorrection;


static const motorMixer_t mixerOrnithopter[] = {
    { 1.0f,  1.0f, -1.0f, -1.0f },          // FRONT_L
    { 1.0f, -1.0f, -1.0f,  1.0f },          // FRONT_R
    { 1.0f, -1.0f,  1.0f, -1.0f },          // REAR_R
    { 1.0f,  1.0f,  1.0f,  1.0f },          // REAR_L
};


FAST_RAM_ZERO_INIT float motorOutputHigh, motorOutputLow;

static FAST_RAM_ZERO_INIT float disarmMotorOutput, deadbandMotor3dHigh, deadbandMotor3dLow;
static FAST_RAM_ZERO_INIT float rcCommandThrottleRange;

uint8_t getMotorCount(void)
{
    return motorCount;
}

float getMotorMixRange(void)
{
    return motorMixRange;
}

bool areMotorsRunning(void)
{
    bool motorsRunning = false;
    if (ARMING_FLAG(ARMED)) {
        motorsRunning = true;
    } else {
        for (int i = 0; i < motorCount; i++) {
            if (motor_disarmed[i] != disarmMotorOutput) {
                motorsRunning = true;

                break;
            }
        }
    }

    return motorsRunning;
}

#ifdef USE_SERVOS
bool mixerIsTricopter(void)
{
    return (currentMixerMode == MIXER_TRI || currentMixerMode == MIXER_CUSTOM_TRI);
}
#endif

// All PWM motor scaling is done to standard PWM range of 1000-2000 for easier tick conversion with legacy code / configurator
// DSHOT scaling is done to the actual dshot range
void initEscEndpoints(void)
{
    float motorOutputLimit = 1.0f;
    if (currentPidProfile->motor_output_limit < 100) {
        motorOutputLimit = currentPidProfile->motor_output_limit / 100.0f;
    }

    // Can't use 'isMotorProtocolDshot()' here since motors haven't been initialised yet
    switch (motorConfig()->dev.motorPwmProtocol) {
#ifdef USE_DSHOT
    case PWM_TYPE_PROSHOT1000:
    case PWM_TYPE_DSHOT1200:
    case PWM_TYPE_DSHOT600:
    case PWM_TYPE_DSHOT300:
    case PWM_TYPE_DSHOT150:
        {
            float outputLimitOffset = (DSHOT_MAX_THROTTLE - DSHOT_MIN_THROTTLE) * (1 - motorOutputLimit);
            disarmMotorOutput = DSHOT_CMD_MOTOR_STOP;
            if (featureIsEnabled(FEATURE_3D)) {
                motorOutputLow = DSHOT_MIN_THROTTLE + ((DSHOT_3D_FORWARD_MIN_THROTTLE - 1 - DSHOT_MIN_THROTTLE) / 100.0f) * CONVERT_PARAMETER_TO_PERCENT(motorConfig()->digitalIdleOffsetValue);
                motorOutputHigh = DSHOT_MAX_THROTTLE - outputLimitOffset / 2;
                deadbandMotor3dHigh = DSHOT_3D_FORWARD_MIN_THROTTLE + ((DSHOT_MAX_THROTTLE - DSHOT_3D_FORWARD_MIN_THROTTLE) / 100.0f) * CONVERT_PARAMETER_TO_PERCENT(motorConfig()->digitalIdleOffsetValue);
                deadbandMotor3dLow = DSHOT_3D_FORWARD_MIN_THROTTLE - 1 - outputLimitOffset / 2;
            } else {
                motorOutputLow = DSHOT_MIN_THROTTLE + ((DSHOT_MAX_THROTTLE - DSHOT_MIN_THROTTLE) / 100.0f) * CONVERT_PARAMETER_TO_PERCENT(motorConfig()->digitalIdleOffsetValue);
                motorOutputHigh = DSHOT_MAX_THROTTLE - outputLimitOffset;
            }
        }

        break;
#endif
    default:
        if (featureIsEnabled(FEATURE_3D)) {
            float outputLimitOffset = (flight3DConfig()->limit3d_high - flight3DConfig()->limit3d_low) * (1 - motorOutputLimit) / 2;
            disarmMotorOutput = flight3DConfig()->neutral3d;
            motorOutputLow = flight3DConfig()->limit3d_low + outputLimitOffset;
            motorOutputHigh = flight3DConfig()->limit3d_high - outputLimitOffset;
            deadbandMotor3dHigh = flight3DConfig()->deadband3d_high;
            deadbandMotor3dLow = flight3DConfig()->deadband3d_low;
        } else {
            disarmMotorOutput = motorConfig()->mincommand;
            motorOutputLow = motorConfig()->minthrottle;
            motorOutputHigh = motorConfig()->maxthrottle - ((motorConfig()->maxthrottle - motorConfig()->minthrottle) * (1 - motorOutputLimit));
        }
        break;
    }

    rcCommandThrottleRange = PWM_RANGE_MAX - PWM_RANGE_MIN;
}

void mixerInit(mixerMode_e mixerMode)
{
    currentMixerMode = mixerMode;

    initEscEndpoints();
#ifdef USE_SERVOS
    if (mixerIsTricopter()) {
        mixerTricopterInit();
    }
#endif
}

#ifdef USE_LAUNCH_CONTROL
// Create a custom mixer for launch control based on the current settings
// but disable the front motors. We don't care about roll or yaw because they
// are limited in the PID controller.
void loadLaunchControlMixer(void)
{
    for (int i = 0; i < MAX_SUPPORTED_MOTORS; i++) {
        launchControlMixer[i] = currentMixer[i];
        // limit the front motors to minimum output
        if (launchControlMixer[i].pitch < 0.0f) {
            launchControlMixer[i].pitch = 0.0f;
            launchControlMixer[i].throttle = 0.0f;
        }
    }
}
#endif

// OrniFlight: ornithopter-only mixer
void mixerConfigureOutput(void)
{
    motorCount = ORNI_MOTOR_COUNT;
    for (int i = 0; i < motorCount; i++) {
        currentMixer[i] = mixerOrnithopter[i];
    }
    mixerResetDisarmedMotors();
}

void mixerLoadMix(int index, motorMixer_t *customMixers)
{
    UNUSED(index);
    // Ornithopter does not support custom motor mixers
    for (int i = 0; i < MAX_SUPPORTED_MOTORS; i++) {
        customMixers[i].throttle = 0.0f;
    }
}

void mixerResetDisarmedMotors(void)
{
    // set disarmed motor values
    for (int i = 0; i < MAX_SUPPORTED_MOTORS; i++) {
        motor_disarmed[i] = disarmMotorOutput;
    }
}

// OrniFlight: no physical motors — servos only
void writeMotors(void) {}
static void writeAllMotors(int16_t mc) { UNUSED(mc); }
void stopMotors(void) {}
void stopPwmAllMotors(void) {}

static FAST_RAM_ZERO_INIT float throttle = 0;
static FAST_RAM_ZERO_INIT float loggingThrottle = 0;
static FAST_RAM_ZERO_INIT float motorOutputMin;
static FAST_RAM_ZERO_INIT float motorRangeMin;
static FAST_RAM_ZERO_INIT float motorRangeMax;
static FAST_RAM_ZERO_INIT float motorOutputRange;
static FAST_RAM_ZERO_INIT int8_t motorOutputMixSign;

static void calculateThrottleAndCurrentMotorEndpoints(timeUs_t currentTimeUs)
{
    float currentThrottleInputRange = 0;

    {
        throttle = rcCommand[THROTTLE] - PWM_RANGE_MIN + throttleAngleCorrection;
        currentThrottleInputRange = rcCommandThrottleRange;
        motorRangeMin = motorOutputLow;
        motorRangeMax = motorOutputHigh;
        motorOutputMin = motorOutputLow;
        motorOutputRange = motorOutputHigh - motorOutputLow;
        motorOutputMixSign = 1;
    }

    throttle = constrainf(throttle / currentThrottleInputRange, 0.0f, 1.0f);
}

#define CRASH_FLIP_DEADBAND 20
#define CRASH_FLIP_STICK_MINF 0.15f

static void applyFlipOverAfterCrashModeToMotors(void) {}

static void applyMixToMotors(float motorMix[MAX_SUPPORTED_MOTORS], motorMixer_t *activeMixer)
{
    // Now add in the desired throttle, but keep in a range that doesn't clip adjusted
    // roll/pitch/yaw. This could move throttle down, but also up for those low throttle flips.
    for (int i = 0; i < motorCount; i++) {
        float motorOutput = motorOutputMixSign * motorMix[i] + throttle * activeMixer[i].throttle;
#ifdef USE_THRUST_LINEARIZATION
        motorOutput = pidApplyThrustLinearization(motorOutput);
#endif
        motorOutput = motorOutputMin + motorOutputRange * motorOutput;

#ifdef USE_SERVOS
        if (mixerIsTricopter()) {
            motorOutput += mixerTricopterMotorCorrection(i);
        }
#endif
        if (failsafeIsActive()) {
            if (isMotorProtocolDshot()) {
                motorOutput = (motorOutput < motorRangeMin) ? disarmMotorOutput : motorOutput; // Prevent getting into special reserved range
            }
            motorOutput = constrain(motorOutput, disarmMotorOutput, motorRangeMax);
        } else {
            motorOutput = constrain(motorOutput, motorRangeMin, motorRangeMax);
        }
        motor[i] = motorOutput;
    }

    // Disarmed mode
    if (!ARMING_FLAG(ARMED)) {
        for (int i = 0; i < motorCount; i++) {
            motor[i] = motor_disarmed[i];
        }
    }
}

float applyThrottleLimit(float throttle)
{
    if (currentControlRateProfile->throttle_limit_percent < 100) {
        const float throttleLimitFactor = currentControlRateProfile->throttle_limit_percent / 100.0f;
        switch (currentControlRateProfile->throttle_limit_type) {
            case THROTTLE_LIMIT_TYPE_SCALE:
                return throttle * throttleLimitFactor;
            case THROTTLE_LIMIT_TYPE_CLIP:
                return MIN(throttle, throttleLimitFactor);
        }
    }

    return throttle;
}

void applyMotorStop(void) {}

#ifdef USE_DYN_LPF
void updateDynLpfCutoffs(timeUs_t currentTimeUs, float throttle)
{
    static timeUs_t lastDynLpfUpdateUs = 0;
    static int dynLpfPreviousQuantizedThrottle = -1;  // to allow an initial zero throttle to set the filter cutoff

    if (cmpTimeUs(currentTimeUs, lastDynLpfUpdateUs) >= DYN_LPF_THROTTLE_UPDATE_DELAY_US) {
        const int quantizedThrottle = lrintf(throttle * DYN_LPF_THROTTLE_STEPS); // quantize the throttle reduce the number of filter updates
        if (quantizedThrottle != dynLpfPreviousQuantizedThrottle) {
            // scale the quantized value back to the throttle range so the filter cutoff steps are repeatable
            const float dynLpfThrottle = (float)quantizedThrottle / DYN_LPF_THROTTLE_STEPS;
            dynLpfGyroUpdate(dynLpfThrottle);
            dynLpfDTermUpdate(dynLpfThrottle);
            dynLpfPreviousQuantizedThrottle = quantizedThrottle;
            lastDynLpfUpdateUs = currentTimeUs;
        }
    }
}
#endif

FAST_CODE_NOINLINE void mixTable(timeUs_t currentTimeUs, uint8_t vbatPidCompensation)
{
    // Find min and max throttle based on conditions. Throttle has to be known before mixing
    calculateThrottleAndCurrentMotorEndpoints(currentTimeUs);

    if (isFlipOverAfterCrashActive()) {
        applyFlipOverAfterCrashModeToMotors();

        return;
    }

    const bool launchControlActive = isLaunchControlActive();

    motorMixer_t * activeMixer = &currentMixer[0];
#ifdef USE_LAUNCH_CONTROL
    if (launchControlActive && (currentPidProfile->launchControlMode == LAUNCH_CONTROL_MODE_PITCHONLY)) {
        activeMixer = &launchControlMixer[0];
    }
#endif
    
    // Calculate and Limit the PID sum
    const float scaledAxisPidRoll =
        constrainf(pidData[FD_ROLL].Sum, -currentPidProfile->pidSumLimit, currentPidProfile->pidSumLimit) / PID_MIXER_SCALING;
    const float scaledAxisPidPitch =
        constrainf(pidData[FD_PITCH].Sum, -currentPidProfile->pidSumLimit, currentPidProfile->pidSumLimit) / PID_MIXER_SCALING;

    uint16_t yawPidSumLimit = currentPidProfile->pidSumLimitYaw;

#ifdef USE_YAW_SPIN_RECOVERY
    const bool yawSpinDetected = gyroYawSpinDetected();
    if (yawSpinDetected) {
        yawPidSumLimit = PIDSUM_LIMIT_MAX;   // Set to the maximum limit during yaw spin recovery to prevent limiting motor authority
    }
#endif // USE_YAW_SPIN_RECOVERY

    float scaledAxisPidYaw =
        constrainf(pidData[FD_YAW].Sum, -yawPidSumLimit, yawPidSumLimit) / PID_MIXER_SCALING;

    if (!mixerConfig()->yaw_motors_reversed) {
        scaledAxisPidYaw = -scaledAxisPidYaw;
    }

    // Calculate voltage compensation
    const float vbatCompensationFactor = vbatPidCompensation ? calculateVbatPidCompensation() : 1.0f;

    // Apply the throttle_limit_percent to scale or limit the throttle based on throttle_limit_type
    if (currentControlRateProfile->throttle_limit_type != THROTTLE_LIMIT_TYPE_OFF) {
        throttle = applyThrottleLimit(throttle);
    }

    const bool airmodeEnabled = airmodeIsEnabled() || launchControlActive;

#ifdef USE_YAW_SPIN_RECOVERY
    // 50% throttle provides the maximum authority for yaw recovery when airmode is not active.
    // When airmode is active the throttle setting doesn't impact recovery authority.
    if (yawSpinDetected && !airmodeEnabled) {
        throttle = 0.5f;   // 
    }
#endif // USE_YAW_SPIN_RECOVERY

#ifdef USE_LAUNCH_CONTROL
    // While launch control is active keep the throttle at minimum.
    // Once the pilot triggers the launch throttle control will be reactivated.
    if (launchControlActive) {
        throttle = 0.0f;
    }
#endif

    // Find roll/pitch/yaw desired output
    float motorMix[MAX_SUPPORTED_MOTORS];
    float motorMixMax = 0, motorMixMin = 0;
    for (int i = 0; i < motorCount; i++) {

        float mix =
            scaledAxisPidRoll  * activeMixer[i].roll +
            scaledAxisPidPitch * activeMixer[i].pitch +
            scaledAxisPidYaw   * activeMixer[i].yaw;

        mix *= vbatCompensationFactor;  // Add voltage compensation

        if (mix > motorMixMax) {
            motorMixMax = mix;
        } else if (mix < motorMixMin) {
            motorMixMin = mix;
        }
        motorMix[i] = mix;
    }

    pidUpdateThrottle(throttle);

#ifdef USE_DYN_LPF
    updateDynLpfCutoffs(currentTimeUs, throttle);
#endif

#ifdef USE_THRUST_LINEARIZATION
    // reestablish old throttle stick feel by counter compensating thrust linearization
    throttle = pidCompensateThrustLinearization(throttle);
#endif

#if defined(USE_THROTTLE_BOOST)
    if (throttleBoost > 0.0f) {
        const float throttleHpf = throttle - pt1FilterApply(&throttleLpf, throttle);
        throttle = constrainf(throttle + throttleBoost * throttleHpf, 0.0f, 1.0f);
    }
#endif

#ifdef USE_GPS_RESCUE
    // If gps rescue is active then override the throttle. This prevents things
    // like throttle boost or throttle limit from negatively affecting the throttle.
    if (FLIGHT_MODE(GPS_RESCUE_MODE)) {
        throttle = gpsRescueGetThrottle();
    }
#endif

#ifdef USE_AIRMODE_LPF
    const float unadjustedThrottle = throttle;
    throttle += pidGetAirmodeThrottleOffset();
    float airmodeThrottleChange = 0;
#endif
    loggingThrottle = throttle;

    motorMixRange = motorMixMax - motorMixMin;
    if (motorMixRange > 1.0f) {
        for (int i = 0; i < motorCount; i++) {
            motorMix[i] /= motorMixRange;
        }
        // Get the maximum correction by setting offset to center when airmode enabled
        if (airmodeEnabled) {
            throttle = 0.5f;
        }
    } else {
        if (airmodeEnabled || throttle > 0.5f) {  // Only automatically adjust throttle when airmode enabled. Airmode logic is always active on high throttle
            throttle = constrainf(throttle, -motorMixMin, 1.0f - motorMixMax);
#ifdef USE_AIRMODE_LPF
            airmodeThrottleChange = constrainf(unadjustedThrottle, -motorMixMin, 1.0f - motorMixMax) - unadjustedThrottle;
#endif
        }
    }

#ifdef USE_AIRMODE_LPF
    pidUpdateAirmodeLpf(airmodeThrottleChange);
#endif

    if (featureIsEnabled(FEATURE_MOTOR_STOP)
        && ARMING_FLAG(ARMED)
        && !featureIsEnabled(FEATURE_3D)
        && !airmodeEnabled
        && !FLIGHT_MODE(GPS_RESCUE_MODE)   // disable motor_stop while GPS Rescue is active
        && (rcData[THROTTLE] < rxConfig()->mincheck)) {
        // motor_stop handling
        applyMotorStop();
    } else {
        // Apply the mix to motor endpoints
        applyMixToMotors(motorMix, activeMixer);
    }
}

float convertExternalToMotor(uint16_t externalValue)
{
    uint16_t motorValue;
    switch ((int)isMotorProtocolDshot()) {
#ifdef USE_DSHOT
    case true:
        externalValue = constrain(externalValue, PWM_RANGE_MIN, PWM_RANGE_MAX);

        if (featureIsEnabled(FEATURE_3D)) {
            if (externalValue == PWM_RANGE_MID) {
                motorValue = DSHOT_CMD_MOTOR_STOP;
            } else if (externalValue < PWM_RANGE_MID) {
                motorValue = scaleRange(externalValue, PWM_RANGE_MIN, PWM_RANGE_MID - 1, DSHOT_3D_FORWARD_MIN_THROTTLE - 1, DSHOT_MIN_THROTTLE);
            } else {
                motorValue = scaleRange(externalValue, PWM_RANGE_MID + 1, PWM_RANGE_MAX, DSHOT_3D_FORWARD_MIN_THROTTLE, DSHOT_MAX_THROTTLE);
            }
        } else {
            motorValue = (externalValue == PWM_RANGE_MIN) ? DSHOT_CMD_MOTOR_STOP : scaleRange(externalValue, PWM_RANGE_MIN + 1, PWM_RANGE_MAX, DSHOT_MIN_THROTTLE, DSHOT_MAX_THROTTLE);
        }

        break;
    case false:
#endif
    default:
        motorValue = externalValue;
        break;
    }

    return (float)motorValue;
}

uint16_t convertMotorToExternal(float motorValue)
{
    uint16_t externalValue;
    switch ((int)isMotorProtocolDshot()) {
#ifdef USE_DSHOT
    case true:
        if (featureIsEnabled(FEATURE_3D)) {
            if (motorValue == DSHOT_CMD_MOTOR_STOP || motorValue < DSHOT_MIN_THROTTLE) {
                externalValue = PWM_RANGE_MID;
            } else if (motorValue <= DSHOT_3D_FORWARD_MIN_THROTTLE - 1) {
                externalValue = scaleRange(motorValue, DSHOT_MIN_THROTTLE, DSHOT_3D_FORWARD_MIN_THROTTLE - 1, PWM_RANGE_MID - 1, PWM_RANGE_MIN);
            } else {
                externalValue = scaleRange(motorValue, DSHOT_3D_FORWARD_MIN_THROTTLE, DSHOT_MAX_THROTTLE, PWM_RANGE_MID + 1, PWM_RANGE_MAX);
            }
        } else {
            externalValue = (motorValue < DSHOT_MIN_THROTTLE) ? PWM_RANGE_MIN : scaleRange(motorValue, DSHOT_MIN_THROTTLE, DSHOT_MAX_THROTTLE, PWM_RANGE_MIN + 1, PWM_RANGE_MAX);
        }
        break;
    case false:
#endif
    default:
        externalValue = motorValue;
        break;
    }

    return externalValue;
}

void mixerSetThrottleAngleCorrection(int correctionValue)
{
    throttleAngleCorrection = correctionValue;
}

float mixerGetLoggingThrottle(void)
{
    return loggingThrottle;
}

#ifdef USE_DSHOT_TELEMETRY
bool isDshotTelemetryActive(void)
{
    for (uint8_t i = 0; i < motorCount; i++) {
        if (!isDshotMotorTelemetryActive(i)) {
            return false;
        }
    }
    return true;
}
#endif