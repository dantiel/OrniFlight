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
#include <stdlib.h>
#include <limits.h>

#include "platform.h"

#include "blackbox/blackbox.h"

#include "build/build_config.h"
#include "build/debug.h"
#include "build/version.h"

#include "common/axis.h"
#include "common/bitarray.h"
#include "common/color.h"
#include "common/huffman.h"
#include "common/maths.h"
#include "common/streambuf.h"
#include "common/utils.h"

#include "config/config_eeprom.h"
#include "config/feature.h"

#include "drivers/accgyro/accgyro.h"
#include "drivers/bus_i2c.h"
#include "drivers/camera_control.h"
#include "drivers/compass/compass.h"
#include "drivers/flash.h"
#include "drivers/io.h"
#include "drivers/max7456.h"
#include "drivers/pwm_output.h"
#include "drivers/sdcard.h"
#include "drivers/serial.h"
#include "drivers/serial_escserial.h"
#include "drivers/system.h"
#include "drivers/transponder_ir.h"
#include "drivers/usb_msc.h"
#include "drivers/vtx_common.h"

#include "fc/board_info.h"
#include "fc/config.h"
#include "fc/controlrate_profile.h"
#include "fc/core.h"
#include "fc/rc.h"
#include "fc/rc_adjustments.h"
#include "fc/rc_controls.h"
#include "fc/rc_modes.h"
#include "fc/runtime_config.h"

#include "flight/position.h"
#include "flight/failsafe.h"
#include "flight/gps_rescue.h"
#include "flight/imu.h"
#include "flight/mixer.h"
#include "flight/pid.h"
#include "flight/servos.h"

#include "io/asyncfatfs/asyncfatfs.h"
#include "io/beeper.h"
#include "io/flashfs.h"
#include "io/gimbal.h"
#include "io/gps.h"
#include "io/ledstrip.h"
#include "io/motors.h"
#include "io/serial.h"
#include "io/serial_4way.h"
#include "io/servos.h"
#include "io/transponder_ir.h"
#include "io/usb_msc.h"
#include "io/vtx_control.h"
#include "io/vtx.h"
#include "io/vtx_string.h"

#include "msp/msp_box.h"
#include "msp/msp_protocol.h"
#include "msp/msp_serial.h"

#include "osd/osd.h"
#include "osd/osd_elements.h"

#include "pg/beeper.h"
#include "pg/board.h"
#include "pg/gyrodev.h"
#include "pg/pg.h"
#include "pg/pg_ids.h"
#include "pg/rx.h"
#include "pg/rx_spi.h"
#include "pg/usb.h"
#include "pg/vcd.h"

#include "rx/rx.h"
#include "rx/msp.h"

#include "scheduler/scheduler.h"

#include "sensors/battery.h"

#include "sensors/acceleration.h"
#include "sensors/barometer.h"
#include "sensors/boardalignment.h"
#include "sensors/esc_sensor.h"
#include "sensors/compass.h"
#include "sensors/gyro.h"
#include "sensors/rangefinder.h"
#include "sensors/sensors.h"

#include "telemetry/telemetry.h"

#ifdef USE_HARDWARE_REVISION_DETECTION
#include "hardware_revision.h"
#endif

#include "msp.h"


static const char * const flightControllerIdentifier = BETAFLIGHT_IDENTIFIER; // 4 UPPER CASE alpha numeric characters that identify the flight controller.

enum {
    MSP_REBOOT_FIRMWARE = 0,
    MSP_REBOOT_BOOTLOADER,
    MSP_REBOOT_MSC,
    MSP_REBOOT_MSC_UTC,
    MSP_REBOOT_COUNT,
};

static uint8_t rebootMode;

typedef enum {
    MSP_SDCARD_STATE_NOT_PRESENT = 0,
    MSP_SDCARD_STATE_FATAL       = 1,
    MSP_SDCARD_STATE_CARD_INIT   = 2,
    MSP_SDCARD_STATE_FS_INIT     = 3,
    MSP_SDCARD_STATE_READY       = 4
} mspSDCardState_e;

typedef enum {
    MSP_SDCARD_FLAG_SUPPORTED   = 1
} mspSDCardFlags_e;

typedef enum {
    MSP_FLASHFS_FLAG_READY       = 1,
    MSP_FLASHFS_FLAG_SUPPORTED  = 2
} mspFlashFsFlags_e;

#define RATEPROFILE_MASK (1 << 7)

#define RTC_NOT_SUPPORTED 0xff

static bool featureMaskIsCopied = false;
static uint32_t featureMaskCopy;

static uint32_t getFeatureMask(void)
{
    if (featureMaskIsCopied) {
        return featureMaskCopy;
    } else {
        return featureMask();
    }
}

#ifdef USE_SERIAL_4WAY_BLHELI_INTERFACE
#define ESC_4WAY 0xff

uint8_t escMode;
uint8_t escPortIndex;

#ifdef USE_ESCSERIAL
static void mspEscPassthroughFn(serialPort_t *serialPort)
{
    escEnablePassthrough(serialPort, &motorConfig()->dev, escPortIndex, escMode);
}
#endif

static void mspFc4waySerialCommand(sbuf_t *dst, sbuf_t *src, mspPostProcessFnPtr *mspPostProcessFn)
{
    const unsigned int dataSize = sbufBytesRemaining(src);
    if (dataSize == 0) {
        // Legacy format

        escMode = ESC_4WAY;
    } else {
        escMode = sbufReadU8(src);
        escPortIndex = sbufReadU8(src);
    }

    switch (escMode) {
    case ESC_4WAY:
        // get channel number
        // switch all motor lines HI
        // reply with the count of ESC found
        sbufWriteU8(dst, esc4wayInit());

        if (mspPostProcessFn) {
            *mspPostProcessFn = esc4wayProcess;
        }
        break;

#ifdef USE_ESCSERIAL
    case PROTOCOL_SIMONK:
    case PROTOCOL_BLHELI:
    case PROTOCOL_KISS:
    case PROTOCOL_KISSALL:
    case PROTOCOL_CASTLE:
        if (escPortIndex < getMotorCount() || (escMode == PROTOCOL_KISS && escPortIndex == ALL_MOTORS)) {
            sbufWriteU8(dst, 1);

            if (mspPostProcessFn) {
                *mspPostProcessFn = mspEscPassthroughFn;
            }

            break;
        }
        FALLTHROUGH;
#endif
    default:
        sbufWriteU8(dst, 0);
    }
}
#endif //USE_SERIAL_4WAY_BLHELI_INTERFACE

static void mspRebootFn(serialPort_t *serialPort)
{
    UNUSED(serialPort);

    stopPwmAllMotors();

    switch (rebootMode) {
    case MSP_REBOOT_FIRMWARE:
        systemReset();

        break;
    case MSP_REBOOT_BOOTLOADER:
        systemResetToBootloader();

        break;
#if defined(USE_USB_MSC)
    case MSP_REBOOT_MSC:
    case MSP_REBOOT_MSC_UTC: {
#ifdef USE_RTC_TIME
        const int16_t timezoneOffsetMinutes = (rebootMode == MSP_REBOOT_MSC) ? timeConfig()->tz_offsetMinutes : 0;
        systemResetToMsc(timezoneOffsetMinutes);
#else
        systemResetToMsc(0);
#endif
        }
        break;
#endif
    default:

        return;
    }

    // control should never return here.
    while (true) ;
}

static void serializeSDCardSummaryReply(sbuf_t *dst)
{
    uint8_t flags = 0;
    uint8_t state = 0;
    uint8_t lastError = 0;
    uint32_t freeSpace = 0;
    uint32_t totalSpace = 0;

#if defined(USE_SDCARD)
    if (sdcardConfig()->mode) {
        flags = MSP_SDCARD_FLAG_SUPPORTED;

        // Merge the card and filesystem states together
        if (!sdcard_isInserted()) {
            state = MSP_SDCARD_STATE_NOT_PRESENT;
        } else if (!sdcard_isFunctional()) {
            state = MSP_SDCARD_STATE_FATAL;
        } else {
            switch (afatfs_getFilesystemState()) {
            case AFATFS_FILESYSTEM_STATE_READY:
                state = MSP_SDCARD_STATE_READY;
                break;

            case AFATFS_FILESYSTEM_STATE_INITIALIZATION:
             if (sdcard_isInitialized()) {
                 state = MSP_SDCARD_STATE_FS_INIT;
             } else {
                 state = MSP_SDCARD_STATE_CARD_INIT;
             }
             break;

            case AFATFS_FILESYSTEM_STATE_FATAL:
            case AFATFS_FILESYSTEM_STATE_UNKNOWN:
            default:
                state = MSP_SDCARD_STATE_FATAL;
                break;
            }
        }

        lastError = afatfs_getLastError();
        // Write free space and total space in kilobytes
        if (state == MSP_SDCARD_STATE_READY) {
            freeSpace = afatfs_getContiguousFreeSpace() / 1024;
            totalSpace = sdcard_getMetadata()->numBlocks / 2;
        }
    }
#endif

    sbufWriteU8(dst, flags);
    sbufWriteU8(dst, state);
    sbufWriteU8(dst, lastError);
    sbufWriteU32(dst, freeSpace);
    sbufWriteU32(dst, totalSpace);
}

static void serializeDataflashSummaryReply(sbuf_t *dst)
{
#ifdef USE_FLASHFS
    if (flashfsIsSupported()) {
        uint8_t flags = MSP_FLASHFS_FLAG_SUPPORTED;
        flags |= (flashfsIsReady() ? MSP_FLASHFS_FLAG_READY : 0);
        const flashGeometry_t *geometry = flashfsGetGeometry();
        sbufWriteU8(dst, flags);
        sbufWriteU32(dst, geometry->sectors);
        sbufWriteU32(dst, geometry->totalSize);
        sbufWriteU32(dst, flashfsGetOffset()); // Effectively the current number of bytes stored on the volume
    } else
#endif

    // FlashFS is not configured or valid device is not detected
    {
        sbufWriteU8(dst, 0);
        sbufWriteU32(dst, 0);
        sbufWriteU32(dst, 0);
        sbufWriteU32(dst, 0);
    }
}

#ifdef USE_FLASHFS
enum compressionType_e {
    NO_COMPRESSION,
    HUFFMAN
};

static void serializeDataflashReadReply(sbuf_t *dst, uint32_t address, const uint16_t size, bool useLegacyFormat, bool allowCompression)
{
    STATIC_ASSERT(MSP_PORT_DATAFLASH_INFO_SIZE >= 16, MSP_PORT_DATAFLASH_INFO_SIZE_invalid);

    uint16_t readLen = size;
    const int bytesRemainingInBuf = sbufBytesRemaining(dst) - MSP_PORT_DATAFLASH_INFO_SIZE;
    if (readLen > bytesRemainingInBuf) {
        readLen = bytesRemainingInBuf;
    }
    // size will be lower than that requested if we reach end of volume
    const uint32_t flashfsSize = flashfsGetSize();
    if (readLen > flashfsSize - address) {
        // truncate the request
        readLen = flashfsSize - address;
    }
    sbufWriteU32(dst, address);

    // legacy format does not support compression
#ifdef USE_HUFFMAN
    const uint8_t compressionMethod = (!allowCompression || useLegacyFormat) ? NO_COMPRESSION : HUFFMAN;
#else
    const uint8_t compressionMethod = NO_COMPRESSION;
    UNUSED(allowCompression);
#endif

    if (compressionMethod == NO_COMPRESSION) {

        uint16_t *readLenPtr = (uint16_t *)sbufPtr(dst);
        if (!useLegacyFormat) {
            // new format supports variable read lengths
            sbufWriteU16(dst, readLen);
            sbufWriteU8(dst, 0); // placeholder for compression format
        }

        const int bytesRead = flashfsReadAbs(address, sbufPtr(dst), readLen);

        if (!useLegacyFormat) {
            // update the 'read length' with the actual amount read from flash.
            *readLenPtr = bytesRead;
        }

        sbufAdvance(dst, bytesRead);

        if (useLegacyFormat) {
            // pad the buffer with zeros
            for (int i = bytesRead; i < size; i++) {
                sbufWriteU8(dst, 0);
            }
        }
    } else {
#ifdef USE_HUFFMAN
        // compress in 256-byte chunks
        const uint16_t READ_BUFFER_SIZE = 256;
        uint8_t readBuffer[READ_BUFFER_SIZE];

        huffmanState_t state = {
            .bytesWritten = 0,
            .outByte = sbufPtr(dst) + sizeof(uint16_t) + sizeof(uint8_t) + HUFFMAN_INFO_SIZE,
            .outBufLen = readLen,
            .outBit = 0x80,
        };
        *state.outByte = 0;

        uint16_t bytesReadTotal = 0;
        // read until output buffer overflows or flash is exhausted
        while (state.bytesWritten < state.outBufLen && address + bytesReadTotal < flashfsSize) {
            const int bytesRead = flashfsReadAbs(address + bytesReadTotal, readBuffer,
                MIN(sizeof(readBuffer), flashfsSize - address - bytesReadTotal));

            const int status = huffmanEncodeBufStreaming(&state, readBuffer, bytesRead, huffmanTable);
            if (status == -1) {
                // overflow
                break;
            }

            bytesReadTotal += bytesRead;
        }

        if (state.outBit != 0x80) {
            ++state.bytesWritten;
        }

        // header
        sbufWriteU16(dst, HUFFMAN_INFO_SIZE + state.bytesWritten);
        sbufWriteU8(dst, compressionMethod);
        // payload
        sbufWriteU16(dst, bytesReadTotal);
        sbufAdvance(dst, state.bytesWritten);
#endif
    }
}
#endif // USE_FLASHFS

/*
 * Returns true if the command was processd, false otherwise.
 * May set mspPostProcessFunc to a function to be called once the command has been processed
 */
static bool mspCommonProcessOutCommand(uint8_t cmdMSP, sbuf_t *dst, mspPostProcessFnPtr *mspPostProcessFn)
{
    UNUSED(mspPostProcessFn);

    switch (cmdMSP) {
    case MSP_API_VERSION:
        sbufWriteU8(dst, MSP_PROTOCOL_VERSION);
        sbufWriteU8(dst, API_VERSION_MAJOR);
        sbufWriteU8(dst, API_VERSION_MINOR);
        break;

    case MSP_FC_VARIANT:
        sbufWriteData(dst, flightControllerIdentifier, FLIGHT_CONTROLLER_IDENTIFIER_LENGTH);
        break;

    case MSP_FC_VERSION:
        sbufWriteU8(dst, FC_VERSION_MAJOR);
        sbufWriteU8(dst, FC_VERSION_MINOR);
        sbufWriteU8(dst, FC_VERSION_PATCH_LEVEL);
        break;

    case MSP_BOARD_INFO:
    {
        sbufWriteData(dst, systemConfig()->boardIdentifier, BOARD_IDENTIFIER_LENGTH);
#ifdef USE_HARDWARE_REVISION_DETECTION
        sbufWriteU16(dst, hardwareRevision);
#else
        sbufWriteU16(dst, 0); // No other build targets currently have hardware revision detection.
#endif
#if defined(USE_MAX7456)
        sbufWriteU8(dst, 2);  // 2 == FC with MAX7456
#else
        sbufWriteU8(dst, 0);  // 0 == FC
#endif
        // Target capabilities (uint8)
#define TARGET_HAS_VCP_BIT 0
#define TARGET_HAS_SOFTSERIAL_BIT 1
#define TARGET_IS_UNIFIED_BIT 2

        uint8_t targetCapabilities = 0;
#ifdef USE_VCP
        targetCapabilities |= 1 << TARGET_HAS_VCP_BIT;
#endif
#if defined(USE_SOFTSERIAL1) || defined(USE_SOFTSERIAL2)
        targetCapabilities |= 1 << TARGET_HAS_SOFTSERIAL_BIT;
#endif
#if defined(USE_UNIFIED_TARGET)
        targetCapabilities |= 1 << TARGET_IS_UNIFIED_BIT;
#endif

        sbufWriteU8(dst, targetCapabilities);

        // Target name with explicit length
        sbufWriteU8(dst, strlen(targetName));
        sbufWriteData(dst, targetName, strlen(targetName));

#if defined(USE_BOARD_INFO)
        // Board name with explicit length
        char *value = getBoardName();
        sbufWriteU8(dst, strlen(value));
        sbufWriteString(dst, value);

        // Manufacturer id with explicit length
        value = getManufacturerId();
        sbufWriteU8(dst, strlen(value));
        sbufWriteString(dst, value);
#else
        sbufWriteU8(dst, 0);
        sbufWriteU8(dst, 0);
#endif

#if defined(USE_SIGNATURE)
        // Signature
        sbufWriteData(dst, getSignature(), SIGNATURE_LENGTH);
#else
        uint8_t emptySignature[SIGNATURE_LENGTH];
        memset(emptySignature, 0, sizeof(emptySignature));
        sbufWriteData(dst, &emptySignature, sizeof(emptySignature));
#endif

        sbufWriteU8(dst, MCU_TYPE_ID);

        break;
    }

    case MSP_BUILD_INFO:
        sbufWriteData(dst, buildDate, BUILD_DATE_LENGTH);
        sbufWriteData(dst, buildTime, BUILD_TIME_LENGTH);
        sbufWriteData(dst, shortGitRevision, GIT_SHORT_REVISION_LENGTH);
        break;

    case MSP_ANALOG:
        sbufWriteU8(dst, (uint8_t)constrain(getLegacyBatteryVoltage(), 0, 255));
        sbufWriteU16(dst, (uint16_t)constrain(getMAhDrawn(), 0, 0xFFFF)); // milliamp hours drawn from battery
        sbufWriteU16(dst, getRssi());
        sbufWriteU16(dst, (int16_t)constrain(getAmperage(), -0x8000, 0x7FFF)); // send current in 0.01 A steps, range is -320A to 320A
        sbufWriteU16(dst, getBatteryVoltage());
        break;

    case MSP_DEBUG:
        for (int i = 0; i < DEBUG16_VALUE_COUNT; i++) {
            sbufWriteU16(dst, debug[i]);      // 4 variables are here for general monitoring purpose
        }
        break;

    case MSP_UID:
        sbufWriteU32(dst, U_ID_0);
        sbufWriteU32(dst, U_ID_1);
        sbufWriteU32(dst, U_ID_2);
        break;

    case MSP_FEATURE_CONFIG:
        sbufWriteU32(dst, getFeatureMask());
        break;

#ifdef USE_BEEPER
    case MSP_BEEPER_CONFIG:
        sbufWriteU32(dst, beeperConfig()->beeper_off_flags);
        sbufWriteU8(dst, beeperConfig()->dshotBeaconTone);
        sbufWriteU32(dst, beeperConfig()->dshotBeaconOffFlags);
        break;
#endif

    case MSP_BATTERY_STATE: {
        // battery characteristics
        sbufWriteU8(dst, (uint8_t)constrain(getBatteryCellCount(), 0, 255)); // 0 indicates battery not detected.
        sbufWriteU16(dst, batteryConfig()->batteryCapacity); // in mAh

        // battery state
        sbufWriteU8(dst, (uint8_t)constrain(getLegacyBatteryVoltage(), 0, 255)); // in 0.1V steps
        sbufWriteU16(dst, (uint16_t)constrain(getMAhDrawn(), 0, 0xFFFF)); // milliamp hours drawn from battery
        sbufWriteU16(dst, (int16_t)constrain(getAmperage(), -0x8000, 0x7FFF)); // send current in 0.01 A steps, range is -320A to 320A

        // battery alerts
        sbufWriteU8(dst, (uint8_t)getBatteryState());
		
        sbufWriteU16(dst, getBatteryVoltage()); // in 0.01V steps
        break;
    }

    case MSP_VOLTAGE_METERS: {
        // write out id and voltage meter values, once for each meter we support
        uint8_t count = supportedVoltageMeterCount;
#ifdef USE_ESC_SENSOR
        count -= VOLTAGE_METER_ID_ESC_COUNT - getMotorCount();
#endif

        for (int i = 0; i < count; i++) {

            voltageMeter_t meter;
            uint8_t id = (uint8_t)voltageMeterIds[i];
            voltageMeterRead(id, &meter);

            sbufWriteU8(dst, id);
            sbufWriteU8(dst, (uint8_t)constrain((meter.filtered + 5) / 10, 0, 255));
        }
        break;
    }

    case MSP_CURRENT_METERS: {
        // write out id and current meter values, once for each meter we support
        uint8_t count = supportedCurrentMeterCount;
#ifdef USE_ESC_SENSOR
        count -= VOLTAGE_METER_ID_ESC_COUNT - getMotorCount();
#endif
        for (int i = 0; i < count; i++) {

            currentMeter_t meter;
            uint8_t id = (uint8_t)currentMeterIds[i];
            currentMeterRead(id, &meter);

            sbufWriteU8(dst, id);
            sbufWriteU16(dst, (uint16_t)constrain(meter.mAhDrawn, 0, 0xFFFF)); // milliamp hours drawn from battery
            sbufWriteU16(dst, (uint16_t)constrain(meter.amperage * 10, 0, 0xFFFF)); // send amperage in 0.001 A steps (mA). Negative range is truncated to zero
        }
        break;
    }

    case MSP_VOLTAGE_METER_CONFIG:
        {
            // by using a sensor type and a sub-frame length it's possible to configure any type of voltage meter,
            // e.g. an i2c/spi/can sensor or any sensor not built directly into the FC such as ESC/RX/SPort/SBus that has
            // different configuration requirements.
            STATIC_ASSERT(VOLTAGE_SENSOR_ADC_VBAT == 0, VOLTAGE_SENSOR_ADC_VBAT_incorrect); // VOLTAGE_SENSOR_ADC_VBAT should be the first index
            sbufWriteU8(dst, MAX_VOLTAGE_SENSOR_ADC); // voltage meters in payload
            for (int i = VOLTAGE_SENSOR_ADC_VBAT; i < MAX_VOLTAGE_SENSOR_ADC; i++) {
                const uint8_t adcSensorSubframeLength = 1 + 1 + 1 + 1 + 1; // length of id, type, vbatscale, vbatresdivval, vbatresdivmultipler, in bytes
                sbufWriteU8(dst, adcSensorSubframeLength); // ADC sensor sub-frame length

                sbufWriteU8(dst, voltageMeterADCtoIDMap[i]); // id of the sensor
                sbufWriteU8(dst, VOLTAGE_SENSOR_TYPE_ADC_RESISTOR_DIVIDER); // indicate the type of sensor that the next part of the payload is for

                sbufWriteU8(dst, voltageSensorADCConfig(i)->vbatscale);
                sbufWriteU8(dst, voltageSensorADCConfig(i)->vbatresdivval);
                sbufWriteU8(dst, voltageSensorADCConfig(i)->vbatresdivmultiplier);
            }
            // if we had any other voltage sensors, this is where we would output any needed configuration
        }

        break;
    case MSP_CURRENT_METER_CONFIG: {
        // the ADC and VIRTUAL sensors have the same configuration requirements, however this API reflects
        // that this situation may change and allows us to support configuration of any current sensor with
        // specialist configuration requirements.

        int currentMeterCount = 1;

#ifdef USE_VIRTUAL_CURRENT_METER
        currentMeterCount++;
#endif
        sbufWriteU8(dst, currentMeterCount);

        const uint8_t adcSensorSubframeLength = 1 + 1 + 2 + 2; // length of id, type, scale, offset, in bytes
        sbufWriteU8(dst, adcSensorSubframeLength);
        sbufWriteU8(dst, CURRENT_METER_ID_BATTERY_1); // the id of the meter
        sbufWriteU8(dst, CURRENT_SENSOR_ADC); // indicate the type of sensor that the next part of the payload is for
        sbufWriteU16(dst, currentSensorADCConfig()->scale);
        sbufWriteU16(dst, currentSensorADCConfig()->offset);

#ifdef USE_VIRTUAL_CURRENT_METER
        const int8_t virtualSensorSubframeLength = 1 + 1 + 2 + 2; // length of id, type, scale, offset, in bytes
        sbufWriteU8(dst, virtualSensorSubframeLength);
        sbufWriteU8(dst, CURRENT_METER_ID_VIRTUAL_1); // the id of the meter
        sbufWriteU8(dst, CURRENT_SENSOR_VIRTUAL); // indicate the type of sensor that the next part of the payload is for
        sbufWriteU16(dst, currentSensorVirtualConfig()->scale);
        sbufWriteU16(dst, currentSensorVirtualConfig()->offset);
#endif

        // if we had any other current sensors, this is where we would output any needed configuration
        break;
    }

    case MSP_BATTERY_CONFIG:
        sbufWriteU8(dst, (batteryConfig()->vbatmincellvoltage + 5) / 10);
        sbufWriteU8(dst, (batteryConfig()->vbatmaxcellvoltage + 5) / 10);
        sbufWriteU8(dst, (batteryConfig()->vbatwarningcellvoltage + 5) / 10);
        sbufWriteU16(dst, batteryConfig()->batteryCapacity);
        sbufWriteU8(dst, batteryConfig()->voltageMeterSource);
        sbufWriteU8(dst, batteryConfig()->currentMeterSource);
        sbufWriteU16(dst, batteryConfig()->vbatmincellvoltage);
        sbufWriteU16(dst, batteryConfig()->vbatmaxcellvoltage);
        sbufWriteU16(dst, batteryConfig()->vbatwarningcellvoltage);
        break;

    case MSP_TRANSPONDER_CONFIG: {
#ifdef USE_TRANSPONDER
        // Backward compatibility to BFC 3.1.1 is lost for this message type
        sbufWriteU8(dst, TRANSPONDER_PROVIDER_COUNT);
        for (unsigned int i = 0; i < TRANSPONDER_PROVIDER_COUNT; i++) {
            sbufWriteU8(dst, transponderRequirements[i].provider);
            sbufWriteU8(dst, transponderRequirements[i].dataLength);
        }

        uint8_t provider = transponderConfig()->provider;
        sbufWriteU8(dst, provider);

        if (provider) {
            uint8_t requirementIndex = provider - 1;
            uint8_t providerDataLength = transponderRequirements[requirementIndex].dataLength;

            for (unsigned int i = 0; i < providerDataLength; i++) {
                sbufWriteU8(dst, transponderConfig()->data[i]);
            }
        }
#else
        sbufWriteU8(dst, 0); // no providers
#endif
        break;
    }

    case MSP_OSD_CONFIG: {
#define OSD_FLAGS_OSD_FEATURE           (1 << 0)
//#define OSD_FLAGS_OSD_SLAVE             (1 << 1)
#define OSD_FLAGS_RESERVED_1            (1 << 2)
#define OSD_FLAGS_RESERVED_2            (1 << 3)
#define OSD_FLAGS_OSD_HARDWARE_MAX_7456 (1 << 4)

        uint8_t osdFlags = 0;
#if defined(USE_OSD)
        osdFlags |= OSD_FLAGS_OSD_FEATURE;
#endif
#ifdef USE_MAX7456
        osdFlags |= OSD_FLAGS_OSD_HARDWARE_MAX_7456;
#endif

        sbufWriteU8(dst, osdFlags);

#ifdef USE_MAX7456
        // send video system (AUTO/PAL/NTSC)
        sbufWriteU8(dst, vcdProfile()->video_system);
#else
        sbufWriteU8(dst, 0);
#endif

#ifdef USE_OSD
        // OSD specific, not applicable to OSD slaves.

        // Configuration
        sbufWriteU8(dst, osdConfig()->units);

        // Alarms
        sbufWriteU8(dst, osdConfig()->rssi_alarm);
        sbufWriteU16(dst, osdConfig()->cap_alarm);

        // Reuse old timer alarm (U16) as OSD_ITEM_COUNT
        sbufWriteU8(dst, 0);
        sbufWriteU8(dst, OSD_ITEM_COUNT);

        sbufWriteU16(dst, osdConfig()->alt_alarm);

        // Element position and visibility
        for (int i = 0; i < OSD_ITEM_COUNT; i++) {
            sbufWriteU16(dst, osdConfig()->item_pos[i]);
        }

        // Post flight statistics
        sbufWriteU8(dst, OSD_STAT_COUNT);
        for (int i = 0; i < OSD_STAT_COUNT; i++ ) {
            sbufWriteU8(dst, osdStatGetState(i));
        }

        // Timers
        sbufWriteU8(dst, OSD_TIMER_COUNT);
        for (int i = 0; i < OSD_TIMER_COUNT; i++) {
            sbufWriteU16(dst, osdConfig()->timers[i]);
        }

        // Enabled warnings
        // Send low word first for backwards compatibility (API < 1.41)
        sbufWriteU16(dst, (uint16_t)(osdConfig()->enabledWarnings & 0xFFFF));
        // API >= 1.41
        // Send the warnings count and 32bit enabled warnings flags.
        // Add currently active OSD profile (0 indicates OSD profiles not available).
        // Add OSD stick overlay mode (0 indicates OSD stick overlay not available).
        sbufWriteU8(dst, OSD_WARNING_COUNT);
        sbufWriteU32(dst, osdConfig()->enabledWarnings);

#ifdef USE_OSD_PROFILES
        sbufWriteU8(dst, OSD_PROFILE_COUNT);            // available profiles
        sbufWriteU8(dst, osdConfig()->osdProfileIndex); // selected profile
#else
        // If the feature is not available there is only 1 profile and it's always selected
        sbufWriteU8(dst, 1);
        sbufWriteU8(dst, 1);
#endif // USE_OSD_PROFILES

#ifdef USE_OSD_STICK_OVERLAY
        sbufWriteU8(dst, osdConfig()->overlay_radio_mode);
#else
        sbufWriteU8(dst, 0);
#endif // USE_OSD_STICK_OVERLAY

#endif // USE_OSD
        break;
    }

    default:
        return false;
    }
    return true;
}

static bool mspProcessOutCommand(uint8_t cmdMSP, sbuf_t *dst)
{
    bool unsupportedCommand = false;

    switch (cmdMSP) {
    case MSP_STATUS_EX:
    case MSP_STATUS:
        {
            boxBitmask_t flightModeFlags;
            const int flagBits = packFlightModeFlags(&flightModeFlags);

            sbufWriteU16(dst, getTaskDeltaTime(TASK_GYROPID));
#ifdef USE_I2C
            sbufWriteU16(dst, i2cGetErrorCounter());
#else
            sbufWriteU16(dst, 0);
#endif
            sbufWriteU16(dst, sensors(SENSOR_ACC) | sensors(SENSOR_BARO) << 1 | sensors(SENSOR_MAG) << 2 | sensors(SENSOR_GPS) << 3 | sensors(SENSOR_RANGEFINDER) << 4 | sensors(SENSOR_GYRO) << 5);
            sbufWriteData(dst, &flightModeFlags, 4);        // unconditional part of flags, first 32 bits
            sbufWriteU8(dst, getCurrentPidProfileIndex());
            sbufWriteU16(dst, constrain(averageSystemLoadPercent, 0, 100));
            if (cmdMSP == MSP_STATUS_EX) {
                sbufWriteU8(dst, PID_PROFILE_COUNT);
                sbufWriteU8(dst, getCurrentControlRateProfileIndex());
            } else {  // MSP_STATUS
                sbufWriteU16(dst, 0); // gyro cycle time
            }

            // write flightModeFlags header. Lowest 4 bits contain number of bytes that follow
            // header is emited even when all bits fit into 32 bits to allow future extension
            int byteCount = (flagBits - 32 + 7) / 8;        // 32 already stored, round up
            byteCount = constrain(byteCount, 0, 15);        // limit to 16 bytes (128 bits)
            sbufWriteU8(dst, byteCount);
            sbufWriteData(dst, ((uint8_t*)&flightModeFlags) + 4, byteCount);

            // Write arming disable flags
            // 1 byte, flag count
            sbufWriteU8(dst, ARMING_DISABLE_FLAGS_COUNT);
            // 4 bytes, flags
            const uint32_t armingDisableFlags = getArmingDisableFlags();
            sbufWriteU32(dst, armingDisableFlags);
        }
        break;

    case MSP_RAW_IMU:
        {
#if defined(USE_ACC)
            // Hack scale due to choice of units for sensor data in multiwii

            uint8_t scale;
            if (acc.dev.acc_1G > 512 * 4) {
                scale = 8;
            } else if (acc.dev.acc_1G > 512 * 2) {
                scale = 4;
            } else if (acc.dev.acc_1G >= 512) {
                scale = 2;
            } else {
                scale = 1;
            }
#endif

            for (int i = 0; i < 3; i++) {
#if defined(USE_ACC)
                sbufWriteU16(dst, lrintf(acc.accADC[i] / scale));
#else
                sbufWriteU16(dst, 0);
#endif
            }
            for (int i = 0; i < 3; i++) {
                sbufWriteU16(dst, gyroRateDps(i));
            }
            for (int i = 0; i < 3; i++) {
                sbufWriteU16(dst, lrintf(mag.magADC[i]));
            }
        }
        break;

    case MSP_NAME:
        {
            const int nameLen = strlen(pilotConfig()->name);
            for (int i = 0; i < nameLen; i++) {
                sbufWriteU8(dst, pilotConfig()->name[i]);
            }
        }
        break;

#ifdef USE_SERVOS
    case MSP_SERVO:
        sbufWriteData(dst, &servo, MAX_SUPPORTED_SERVOS * 2);
        break;
    case MSP_SERVO_CONFIGURATIONS:
        for (int i = 0; i < MAX_SUPPORTED_SERVOS; i++) {
            sbufWriteU16(dst, servoParams(i)->min);
            sbufWriteU16(dst, servoParams(i)->max);
            sbufWriteU16(dst, servoParams(i)->middle);
            sbufWriteU8(dst, servoParams(i)->rate);
            sbufWriteU8(dst, servoParams(i)->forwardFromChannel);
            sbufWriteU32(dst, servoParams(i)->reversedSources);
        }
        break;

    case MSP_SERVO_MIX_RULES:
        for (int i = 0; i < MAX_SERVO_RULES; i++) {
            sbufWriteU8(dst, customServoMixers(i)->targetChannel);
            sbufWriteU8(dst, customServoMixers(i)->inputSource);
            sbufWriteU8(dst, customServoMixers(i)->rate);
            sbufWriteU8(dst, customServoMixers(i)->speed);
            sbufWriteU8(dst, customServoMixers(i)->min);
            sbufWriteU8(dst, customServoMixers(i)->max);
            sbufWriteU8(dst, customServoMixers(i)->box);
        }
        break;
#endif

    case MSP_MOTOR:
        for (unsigned i = 0; i < 8; i++) {
            if (i >= MAX_SUPPORTED_MOTORS || !pwmGetMotors()[i].enabled) {
                sbufWriteU16(dst, 0);
                continue;
            }

            sbufWriteU16(dst, convertMotorToExternal(motor[i]));
        }
        break;

    case MSP_RC:
        for (int i = 0; i < rxRuntimeConfig.channelCount; i++) {
            sbufWriteU16(dst, rcData[i]);
        }
        break;

    case MSP_ATTITUDE:
        sbufWriteU16(dst, attitude.values.roll);
        sbufWriteU16(dst, attitude.values.pitch);
        sbufWriteU16(dst, DECIDEGREES_TO_DEGREES(attitude.values.yaw));
        break;

    case MSP_ALTITUDE:
#if defined(USE_BARO) || defined(USE_RANGEFINDER)
        sbufWriteU32(dst, getEstimatedAltitudeCm());
#else
        sbufWriteU32(dst, 0);
#endif
#ifdef USE_VARIO
        sbufWriteU16(dst, getEstimatedVario());
#else
        sbufWriteU16(dst, 0);
#endif
        break;

    case MSP_SONAR_ALTITUDE:
#if defined(USE_RANGEFINDER)
        sbufWriteU32(dst, rangefinderGetLatestAltitude());
#else
        sbufWriteU32(dst, 0);
#endif
        break;

    case MSP_BOARD_ALIGNMENT_CONFIG:
        sbufWriteU16(dst, boardAlignment()->rollDegrees);
        sbufWriteU16(dst, boardAlignment()->pitchDegrees);
        sbufWriteU16(dst, boardAlignment()->yawDegrees);
        break;

    case MSP_ARMING_CONFIG:
        sbufWriteU8(dst, armingConfig()->auto_disarm_delay);
        sbufWriteU8(dst, 0);
        sbufWriteU8(dst, imuConfig()->small_angle);
        break;

    case MSP_RC_TUNING:
        sbufWriteU8(dst, currentControlRateProfile->rcRates[FD_ROLL]);
        sbufWriteU8(dst, currentControlRateProfile->rcExpo[FD_ROLL]);
        for (int i = 0 ; i < 3; i++) {
            sbufWriteU8(dst, currentControlRateProfile->rates[i]); // R,P,Y see flight_dynamics_index_t
        }
        sbufWriteU8(dst, currentControlRateProfile->dynThrPID);
        sbufWriteU8(dst, currentControlRateProfile->thrMid8);
        sbufWriteU8(dst, currentControlRateProfile->thrExpo8);
        sbufWriteU16(dst, currentControlRateProfile->tpa_breakpoint);
        sbufWriteU8(dst, currentControlRateProfile->rcExpo[FD_YAW]);
        sbufWriteU8(dst, currentControlRateProfile->rcRates[FD_YAW]);
        sbufWriteU8(dst, currentControlRateProfile->rcRates[FD_PITCH]);
        sbufWriteU8(dst, currentControlRateProfile->rcExpo[FD_PITCH]);

        // added in 1.41
        sbufWriteU8(dst, currentControlRateProfile->throttle_limit_type);
        sbufWriteU8(dst, currentControlRateProfile->throttle_limit_percent);
        
        break;

    case MSP_PID:
        for (int i = 0; i < PID_ITEM_COUNT; i++) {
            sbufWriteU8(dst, currentPidProfile->pid[i].P);
            sbufWriteU8(dst, currentPidProfile->pid[i].I);
            sbufWriteU8(dst, currentPidProfile->pid[i].D);
        }
        break;

    case MSP_PIDNAMES:
        for (const char *c = pidNames; *c; c++) {
            sbufWriteU8(dst, *c);
        }
        break;

    case MSP_PID_CONTROLLER:
        sbufWriteU8(dst, PID_CONTROLLER_BETAFLIGHT);
        break;

    case MSP_MODE_RANGES:
        for (int i = 0; i < MAX_MODE_ACTIVATION_CONDITION_COUNT; i++) {
            const modeActivationCondition_t *mac = modeActivationConditions(i);
            const box_t *box = findBoxByBoxId(mac->modeId);
            sbufWriteU8(dst, box->permanentId);
            sbufWriteU8(dst, mac->auxChannelIndex);
            sbufWriteU8(dst, mac->range.startStep);
            sbufWriteU8(dst, mac->range.endStep);
        }
        break;

    case MSP_MODE_RANGES_EXTRA:
        sbufWriteU8(dst, MAX_MODE_ACTIVATION_CONDITION_COUNT);          // prepend number of EXTRAs array elements

        for (int i = 0; i < MAX_MODE_ACTIVATION_CONDITION_COUNT; i++) {
            const modeActivationCondition_t *mac = modeActivationConditions(i);
            const box_t *box = findBoxByBoxId(mac->modeId);
            const box_t *linkedBox = findBoxByBoxId(mac->linkedTo);
            sbufWriteU8(dst, box->permanentId);     // each element is aligned with MODE_RANGES by the permanentId
            sbufWriteU8(dst, mac->modeLogic);
            sbufWriteU8(dst, linkedBox->permanentId);
        }
        break;

    case MSP_ADJUSTMENT_RANGES:
        for (int i = 0; i < MAX_ADJUSTMENT_RANGE_COUNT; i++) {
            const adjustmentRange_t *adjRange = adjustmentRanges(i);
            sbufWriteU8(dst, adjRange->adjustmentIndex);
            sbufWriteU8(dst, adjRange->auxChannelIndex);
            sbufWriteU8(dst, adjRange->range.startStep);
            sbufWriteU8(dst, adjRange->range.endStep);
            sbufWriteU8(dst, adjRange->adjustmentConfig);
            sbufWriteU8(dst, adjRange->auxSwitchChannelIndex);
        }
        break;

    case MSP_MOTOR_CONFIG:
        sbufWriteU16(dst, motorConfig()->minthrottle);
        sbufWriteU16(dst, motorConfig()->maxthrottle);
        sbufWriteU16(dst, motorConfig()->mincommand);
        break;

#ifdef USE_MAG
    case MSP_COMPASS_CONFIG:
        sbufWriteU16(dst, compassConfig()->mag_declination / 10);
        break;
#endif

#if defined(USE_ESC_SENSOR)
    case MSP_ESC_SENSOR_DATA:
        if (featureIsEnabled(FEATURE_ESC_SENSOR)) {
            sbufWriteU8(dst, getMotorCount());
            for (int i = 0; i < getMotorCount(); i++) {
                const escSensorData_t *escData = getEscSensorData(i);
                sbufWriteU8(dst, escData->temperature);
                sbufWriteU16(dst, escData->rpm);
            }
        } else {
            unsupportedCommand = true;
        }

        break;
#endif

#ifdef USE_GPS
    case MSP_GPS_CONFIG:
        sbufWriteU8(dst, gpsConfig()->provider);
        sbufWriteU8(dst, gpsConfig()->sbasMode);
        sbufWriteU8(dst, gpsConfig()->autoConfig);
        sbufWriteU8(dst, gpsConfig()->autoBaud);
        break;

    case MSP_RAW_GPS:
        sbufWriteU8(dst, STATE(GPS_FIX));
        sbufWriteU8(dst, gpsSol.numSat);
        sbufWriteU32(dst, gpsSol.llh.lat);
        sbufWriteU32(dst, gpsSol.llh.lon);
        sbufWriteU16(dst, (uint16_t)constrain(gpsSol.llh.altCm / 100, 0, UINT16_MAX)); // alt changed from 1m to 0.01m per lsb since MSP API 1.39 by RTH. To maintain backwards compatibility compensate to 1m per lsb in MSP again.
        sbufWriteU16(dst, gpsSol.groundSpeed);
        sbufWriteU16(dst, gpsSol.groundCourse);
        break;

    case MSP_COMP_GPS:
        sbufWriteU16(dst, GPS_distanceToHome);
        sbufWriteU16(dst, GPS_directionToHome);
        sbufWriteU8(dst, GPS_update & 1);
        break;

    case MSP_GPSSVINFO:
        sbufWriteU8(dst, GPS_numCh);
       for (int i = 0; i < GPS_numCh; i++) {
           sbufWriteU8(dst, GPS_svinfo_chn[i]);
           sbufWriteU8(dst, GPS_svinfo_svid[i]);
           sbufWriteU8(dst, GPS_svinfo_quality[i]);
           sbufWriteU8(dst, GPS_svinfo_cno[i]);
       }
        break;

#ifdef USE_GPS_RESCUE
    case MSP_GPS_RESCUE:
        sbufWriteU16(dst, gpsRescueConfig()->angle);
        sbufWriteU16(dst, gpsRescueConfig()->initialAltitudeM);
        sbufWriteU16(dst, gpsRescueConfig()->descentDistanceM);
        sbufWriteU16(dst, gpsRescueConfig()->rescueGroundspeed);
        sbufWriteU16(dst, gpsRescueConfig()->throttleMin);
        sbufWriteU16(dst, gpsRescueConfig()->throttleMax);
        sbufWriteU16(dst, gpsRescueConfig()->throttleHover);
        sbufWriteU8(dst,  gpsRescueConfig()->sanityChecks);
        sbufWriteU8(dst,  gpsRescueConfig()->minSats);
        break;

    case MSP_GPS_RESCUE_PIDS:
        sbufWriteU16(dst, gpsRescueConfig()->throttleP);
        sbufWriteU16(dst, gpsRescueConfig()->throttleI);
        sbufWriteU16(dst, gpsRescueConfig()->throttleD);
        sbufWriteU16(dst, gpsRescueConfig()->velP);
        sbufWriteU16(dst, gpsRescueConfig()->velI);
        sbufWriteU16(dst, gpsRescueConfig()->velD);
        sbufWriteU16(dst, gpsRescueConfig()->yawP);
        break;
#endif
#endif

#if defined(USE_ACC)
    case MSP_ACC_TRIM:
        sbufWriteU16(dst, accelerometerConfig()->accelerometerTrims.values.pitch);
        sbufWriteU16(dst, accelerometerConfig()->accelerometerTrims.values.roll);

        break;
#endif
    case MSP_MIXER_CONFIG:
        sbufWriteU8(dst, mixerConfig()->mixerMode);
        sbufWriteU8(dst, mixerConfig()->yaw_motors_reversed);
        break;

    case MSP_RX_CONFIG:
        sbufWriteU8(dst, rxConfig()->serialrx_provider);
        sbufWriteU16(dst, rxConfig()->maxcheck);
        sbufWriteU16(dst, rxConfig()->midrc);
        sbufWriteU16(dst, rxConfig()->mincheck);
        sbufWriteU8(dst, rxConfig()->spektrum_sat_bind);
        sbufWriteU16(dst, rxConfig()->rx_min_usec);
        sbufWriteU16(dst, rxConfig()->rx_max_usec);
        sbufWriteU8(dst, rxConfig()->rcInterpolation);
        sbufWriteU8(dst, rxConfig()->rcInterpolationInterval);
        sbufWriteU16(dst, rxConfig()->airModeActivateThreshold * 10 + 1000);
#ifdef USE_RX_SPI
        sbufWriteU8(dst, rxSpiConfig()->rx_spi_protocol);
        sbufWriteU32(dst, rxSpiConfig()->rx_spi_id);
        sbufWriteU8(dst, rxSpiConfig()->rx_spi_rf_channel_count);
#else
        sbufWriteU8(dst, 0);
        sbufWriteU32(dst, 0);
        sbufWriteU8(dst, 0);
#endif
        sbufWriteU8(dst, rxConfig()->fpvCamAngleDegrees);
        sbufWriteU8(dst, rxConfig()->rcInterpolationChannels);
#if defined(USE_RC_SMOOTHING_FILTER)
        sbufWriteU8(dst, rxConfig()->rc_smoothing_type);
        sbufWriteU8(dst, rxConfig()->rc_smoothing_input_cutoff);
        sbufWriteU8(dst, rxConfig()->rc_smoothing_derivative_cutoff);
        sbufWriteU8(dst, rxConfig()->rc_smoothing_input_type);
        sbufWriteU8(dst, rxConfig()->rc_smoothing_derivative_type);
#else
        sbufWriteU8(dst, 0);
        sbufWriteU8(dst, 0);
        sbufWriteU8(dst, 0);
        sbufWriteU8(dst, 0);
        sbufWriteU8(dst, 0);
#endif
#if defined(USE_USB_CDC_HID)
        sbufWriteU8(dst, usbDevConfig()->type);
#else
        sbufWriteU8(dst, 0);
#endif

        break;
    case MSP_FAILSAFE_CONFIG:
        sbufWriteU8(dst, failsafeConfig()->failsafe_delay);
        sbufWriteU8(dst, failsafeConfig()->failsafe_off_delay);
        sbufWriteU16(dst, failsafeConfig()->failsafe_throttle);
        sbufWriteU8(dst, failsafeConfig()->failsafe_switch_mode);
        sbufWriteU16(dst, failsafeConfig()->failsafe_throttle_low_delay);
        sbufWriteU8(dst, failsafeConfig()->failsafe_procedure);
        break;

    case MSP_RXFAIL_CONFIG:
        for (int i = 0; i < rxRuntimeConfig.channelCount; i++) {
            sbufWriteU8(dst, rxFailsafeChannelConfigs(i)->mode);
            sbufWriteU16(dst, RXFAIL_STEP_TO_CHANNEL_VALUE(rxFailsafeChannelConfigs(i)->step));
        }
        break;

    case MSP_RSSI_CONFIG:
        sbufWriteU8(dst, rxConfig()->rssi_channel);
        break;

    case MSP_RX_MAP:
        sbufWriteData(dst, rxConfig()->rcmap, RX_MAPPABLE_CHANNEL_COUNT);
        break;

    case MSP_CF_SERIAL_CONFIG:
        for (int i = 0; i < SERIAL_PORT_COUNT; i++) {
            if (!serialIsPortAvailable(serialConfig()->portConfigs[i].identifier)) {
                continue;
            };
            sbufWriteU8(dst, serialConfig()->portConfigs[i].identifier);
            sbufWriteU16(dst, serialConfig()->portConfigs[i].functionMask);
            sbufWriteU8(dst, serialConfig()->portConfigs[i].msp_baudrateIndex);
            sbufWriteU8(dst, serialConfig()->portConfigs[i].gps_baudrateIndex);
            sbufWriteU8(dst, serialConfig()->portConfigs[i].telemetry_baudrateIndex);
            sbufWriteU8(dst, serialConfig()->portConfigs[i].blackbox_baudrateIndex);
        }
        break;

#ifdef USE_LED_STRIP_STATUS_MODE
    case MSP_LED_COLORS:
        for (int i = 0; i < LED_CONFIGURABLE_COLOR_COUNT; i++) {
            const hsvColor_t *color = &ledStripStatusModeConfig()->colors[i];
            sbufWriteU16(dst, color->h);
            sbufWriteU8(dst, color->s);
            sbufWriteU8(dst, color->v);
        }
        break;
#endif

#ifdef USE_LED_STRIP
    case MSP_LED_STRIP_CONFIG:
        for (int i = 0; i < LED_MAX_STRIP_LENGTH; i++) {
#ifdef USE_LED_STRIP_STATUS_MODE
            const ledConfig_t *ledConfig = &ledStripStatusModeConfig()->ledConfigs[i];
            sbufWriteU32(dst, *ledConfig);
#else
            sbufWriteU32(dst, 0);
#endif
        }

        // API 1.41 - add indicator for advanced profile support and the current profile selection
        // 0 = basic ledstrip available
        // 1 = advanced ledstrip available
#ifdef USE_LED_STRIP_STATUS_MODE
        sbufWriteU8(dst, 1);   // advanced ledstrip available
#else
        sbufWriteU8(dst, 0);   // only simple ledstrip available
#endif
        sbufWriteU8(dst, ledStripConfig()->ledstrip_profile);
        break;
#endif

#ifdef USE_LED_STRIP_STATUS_MODE
    case MSP_LED_STRIP_MODECOLOR:
        for (int i = 0; i < LED_MODE_COUNT; i++) {
            for (int j = 0; j < LED_DIRECTION_COUNT; j++) {
                sbufWriteU8(dst, i);
                sbufWriteU8(dst, j);
                sbufWriteU8(dst, ledStripStatusModeConfig()->modeColors[i].color[j]);
            }
        }

        for (int j = 0; j < LED_SPECIAL_COLOR_COUNT; j++) {
            sbufWriteU8(dst, LED_MODE_COUNT);
            sbufWriteU8(dst, j);
            sbufWriteU8(dst, ledStripStatusModeConfig()->specialColors.color[j]);
        }

        sbufWriteU8(dst, LED_AUX_CHANNEL);
        sbufWriteU8(dst, 0);
        sbufWriteU8(dst, ledStripStatusModeConfig()->ledstrip_aux_channel);
        break;
#endif

    case MSP_DATAFLASH_SUMMARY:
        serializeDataflashSummaryReply(dst);
        break;

    case MSP_BLACKBOX_CONFIG:
#ifdef USE_BLACKBOX
        sbufWriteU8(dst, 1); //Blackbox supported
        sbufWriteU8(dst, blackboxConfig()->device);
        sbufWriteU8(dst, 1); // Rate numerator, not used anymore
        sbufWriteU8(dst, blackboxGetRateDenom());
        sbufWriteU16(dst, blackboxConfig()->p_ratio);
#else
        sbufWriteU8(dst, 0); // Blackbox not supported
        sbufWriteU8(dst, 0);
        sbufWriteU8(dst, 0);
        sbufWriteU8(dst, 0);
        sbufWriteU16(dst, 0);
#endif
        break;

    case MSP_SDCARD_SUMMARY:
        serializeSDCardSummaryReply(dst);
        break;

    case MSP_MOTOR_3D_CONFIG:
        sbufWriteU16(dst, flight3DConfig()->deadband3d_low);
        sbufWriteU16(dst, flight3DConfig()->deadband3d_high);
        sbufWriteU16(dst, flight3DConfig()->neutral3d);
        break;

    case MSP_RC_DEADBAND:
        sbufWriteU8(dst, rcControlsConfig()->deadband);
        sbufWriteU8(dst, rcControlsConfig()->yaw_deadband);
        sbufWriteU8(dst, rcControlsConfig()->alt_hold_deadband);
        sbufWriteU16(dst, flight3DConfig()->deadband3d_throttle);
        break;

    case MSP_SENSOR_ALIGNMENT: {
        uint8_t gyroAlignment;
#ifdef USE_MULTI_GYRO
        switch (gyroConfig()->gyro_to_use) {
        case GYRO_CONFIG_USE_GYRO_2:
            gyroAlignment = gyroDeviceConfig(1)->align;
            break;
        case GYRO_CONFIG_USE_GYRO_BOTH:
            // for dual-gyro in "BOTH" mode we only read/write gyro 0
        default:
            gyroAlignment = gyroDeviceConfig(0)->align;
            break;
        }
#else
        gyroAlignment = gyroDeviceConfig(0)->align;
#endif
        sbufWriteU8(dst, gyroAlignment);
        sbufWriteU8(dst, gyroAlignment);  // Starting with 4.0 gyro and acc alignment are the same 
        sbufWriteU8(dst, compassConfig()->mag_align);

        // API 1.41 - Add multi-gyro indicator, selected gyro, and support for separate gyro 1 & 2 alignment
        sbufWriteU8(dst, getGyroDetectionFlags());
#ifdef USE_MULTI_GYRO
        sbufWriteU8(dst, gyroConfig()->gyro_to_use);
        sbufWriteU8(dst, gyroDeviceConfig(0)->align);
        sbufWriteU8(dst, gyroDeviceConfig(1)->align);
#else
        sbufWriteU8(dst, GYRO_CONFIG_USE_GYRO_1);
        sbufWriteU8(dst, gyroDeviceConfig(0)->align);
        sbufWriteU8(dst, ALIGN_DEFAULT);
#endif

        break;
    }

    case MSP_ADVANCED_CONFIG:
        sbufWriteU8(dst, gyroConfig()->gyro_sync_denom);
        sbufWriteU8(dst, pidConfig()->pid_process_denom);
        sbufWriteU8(dst, motorConfig()->dev.useUnsyncedPwm);
        sbufWriteU8(dst, motorConfig()->dev.motorPwmProtocol);
        sbufWriteU16(dst, motorConfig()->dev.motorPwmRate);
        sbufWriteU16(dst, motorConfig()->digitalIdleOffsetValue);
        sbufWriteU8(dst, 0); // DEPRECATED: gyro_use_32kHz
        sbufWriteU8(dst, motorConfig()->dev.motorPwmInversion);
        sbufWriteU8(dst, gyroConfig()->gyro_to_use);
        sbufWriteU8(dst, gyroConfig()->gyro_high_fsr);
        sbufWriteU8(dst, gyroConfig()->gyroMovementCalibrationThreshold);
        sbufWriteU16(dst, gyroConfig()->gyroCalibrationDuration);
        sbufWriteU16(dst, gyroConfig()->gyro_offset_yaw);
        sbufWriteU8(dst, gyroConfig()->checkOverflow);

        break;
    case MSP_FILTER_CONFIG :
        sbufWriteU8(dst, gyroConfig()->gyro_lowpass_hz);
        sbufWriteU16(dst, currentPidProfile->dterm_lowpass_hz);
        sbufWriteU16(dst, currentPidProfile->yaw_lowpass_hz);
        sbufWriteU16(dst, gyroConfig()->gyro_soft_notch_hz_1);
        sbufWriteU16(dst, gyroConfig()->gyro_soft_notch_cutoff_1);
        sbufWriteU16(dst, currentPidProfile->dterm_notch_hz);
        sbufWriteU16(dst, currentPidProfile->dterm_notch_cutoff);
        sbufWriteU16(dst, gyroConfig()->gyro_soft_notch_hz_2);
        sbufWriteU16(dst, gyroConfig()->gyro_soft_notch_cutoff_2);
        sbufWriteU8(dst, currentPidProfile->dterm_filter_type);
        sbufWriteU8(dst, gyroConfig()->gyro_hardware_lpf);
        sbufWriteU8(dst, 0); // DEPRECATED: gyro_32khz_hardware_lpf
        sbufWriteU16(dst, gyroConfig()->gyro_lowpass_hz);
        sbufWriteU16(dst, gyroConfig()->gyro_lowpass2_hz);
        sbufWriteU8(dst, gyroConfig()->gyro_lowpass_type);
        sbufWriteU8(dst, gyroConfig()->gyro_lowpass2_type);
        sbufWriteU16(dst, currentPidProfile->dterm_lowpass2_hz);
        // Added in MSP API 1.41
        sbufWriteU8(dst, currentPidProfile->dterm_filter2_type);
#if defined(USE_DYN_LPF)
        sbufWriteU16(dst, gyroConfig()->dyn_lpf_gyro_min_hz);
        sbufWriteU16(dst, gyroConfig()->dyn_lpf_gyro_max_hz);
        sbufWriteU16(dst, currentPidProfile->dyn_lpf_dterm_min_hz);
        sbufWriteU16(dst, currentPidProfile->dyn_lpf_dterm_max_hz);
#else
        sbufWriteU16(dst, 0);
        sbufWriteU16(dst, 0);
        sbufWriteU16(dst, 0);
        sbufWriteU16(dst, 0);
#endif

        break;
    case MSP_PID_ADVANCED:
        sbufWriteU16(dst, 0);
        sbufWriteU16(dst, 0);
        sbufWriteU16(dst, 0); // was pidProfile.yaw_p_limit
        sbufWriteU8(dst, 0); // reserved
        sbufWriteU8(dst, currentPidProfile->vbatPidCompensation);
        sbufWriteU8(dst, currentPidProfile->feedForwardTransition);
        sbufWriteU8(dst, 0); // was low byte of currentPidProfile->dtermSetpointWeight
        sbufWriteU8(dst, 0); // reserved
        sbufWriteU8(dst, 0); // reserved
        sbufWriteU8(dst, 0); // reserved
        sbufWriteU16(dst, currentPidProfile->rateAccelLimit);
        sbufWriteU16(dst, currentPidProfile->yawRateAccelLimit);
        sbufWriteU8(dst, currentPidProfile->levelAngleLimit);
        sbufWriteU8(dst, 0); // was pidProfile.levelSensitivity
        sbufWriteU16(dst, currentPidProfile->itermThrottleThreshold);
        sbufWriteU16(dst, currentPidProfile->itermAcceleratorGain);
        sbufWriteU16(dst, 0); // was currentPidProfile->dtermSetpointWeight
        sbufWriteU8(dst, currentPidProfile->iterm_rotation);
#if defined(USE_SMART_FEEDFORWARD)
        sbufWriteU8(dst, currentPidProfile->smart_feedforward);
#else
        sbufWriteU8(dst, 0);
#endif
#if defined(USE_ITERM_RELAX)
        sbufWriteU8(dst, currentPidProfile->iterm_relax);
        sbufWriteU8(dst, currentPidProfile->iterm_relax_type);
#else
        sbufWriteU8(dst, 0);
        sbufWriteU8(dst, 0);
#endif
#if defined(USE_ABSOLUTE_CONTROL)
        sbufWriteU8(dst, currentPidProfile->abs_control_gain);
#else
        sbufWriteU8(dst, 0);
#endif
#if defined(USE_THROTTLE_BOOST)
        sbufWriteU8(dst, currentPidProfile->throttle_boost);
#else
        sbufWriteU8(dst, 0);
#endif
#if defined(USE_ACRO_TRAINER)
        sbufWriteU8(dst, currentPidProfile->acro_trainer_angle_limit);
#else
        sbufWriteU8(dst, 0);
#endif
        sbufWriteU16(dst, currentPidProfile->pid[PID_ROLL].F);
        sbufWriteU16(dst, currentPidProfile->pid[PID_PITCH].F);
        sbufWriteU16(dst, currentPidProfile->pid[PID_YAW].F);

        sbufWriteU8(dst, currentPidProfile->antiGravityMode);
#if defined(USE_D_MIN)
        sbufWriteU8(dst, currentPidProfile->d_min[PID_ROLL]);
        sbufWriteU8(dst, currentPidProfile->d_min[PID_PITCH]);
        sbufWriteU8(dst, currentPidProfile->d_min[PID_YAW]);
        sbufWriteU8(dst, currentPidProfile->d_min_gain);
        sbufWriteU8(dst, currentPidProfile->d_min_advance);
#else
        sbufWriteU8(dst, 0);
        sbufWriteU8(dst, 0);
        sbufWriteU8(dst, 0);
        sbufWriteU8(dst, 0);
        sbufWriteU8(dst, 0);
#endif
#if defined(USE_INTEGRATED_YAW_CONTROL)
        sbufWriteU8(dst, currentPidProfile->use_integrated_yaw);
        sbufWriteU8(dst, currentPidProfile->integrated_yaw_relax);
#else
        sbufWriteU8(dst, 0);
        sbufWriteU8(dst, 0);
#endif

        break;
    case MSP_SENSOR_CONFIG:
#if defined(USE_ACC)
        sbufWriteU8(dst, accelerometerConfig()->acc_hardware);
#else
        sbufWriteU8(dst, 0);
#endif
#ifdef USE_BARO
        sbufWriteU8(dst, barometerConfig()->baro_hardware);
#else
        sbufWriteU8(dst, BARO_NONE);
#endif
#ifdef USE_MAG
        sbufWriteU8(dst, compassConfig()->mag_hardware);
#else
        sbufWriteU8(dst, MAG_NONE);
#endif
        break;

#if defined(USE_VTX_COMMON)
    case MSP_VTX_CONFIG:
        {
            const vtxDevice_t *vtxDevice = vtxCommonDevice();
            uint8_t pitmode = 0;
            vtxDevType_e vtxType = VTXDEV_UNKNOWN;
            uint8_t deviceIsReady = 0;
            if (vtxDevice) {
                vtxCommonGetPitMode(vtxDevice, &pitmode);
                vtxType = vtxCommonGetDeviceType(vtxDevice);
                deviceIsReady = vtxCommonDeviceIsReady(vtxDevice) ? 1 : 0;
            }
            sbufWriteU8(dst, vtxType);
            sbufWriteU8(dst, vtxSettingsConfig()->band);
            sbufWriteU8(dst, vtxSettingsConfig()->channel);
            sbufWriteU8(dst, vtxSettingsConfig()->power);
            sbufWriteU8(dst, pitmode);
            sbufWriteU16(dst, vtxSettingsConfig()->freq);
            sbufWriteU8(dst, deviceIsReady);
            sbufWriteU8(dst, vtxSettingsConfig()->lowPowerDisarm);
            // future extensions here...
        }
        break;
#endif

    case MSP_TX_INFO:
        sbufWriteU8(dst, rssiSource);
        uint8_t rtcDateTimeIsSet = 0;
#ifdef USE_RTC_TIME
        dateTime_t dt;
        if (rtcGetDateTime(&dt)) {
            rtcDateTimeIsSet = 1;
        }
#else
        rtcDateTimeIsSet = RTC_NOT_SUPPORTED;
#endif
        sbufWriteU8(dst, rtcDateTimeIsSet);

        break;
#ifdef USE_RTC_TIME
    case MSP_RTC:
        {
            dateTime_t dt;
            if (rtcGetDateTime(&dt)) {
                sbufWriteU16(dst, dt.year);
                sbufWriteU8(dst, dt.month);
                sbufWriteU8(dst, dt.day);
                sbufWriteU8(dst, dt.hours);
                sbufWriteU8(dst, dt.minutes);
                sbufWriteU8(dst, dt.seconds);
                sbufWriteU16(dst, dt.millis);
            }
        }

        break;
#endif
    default:
        unsupportedCommand = true;
    }
    return !unsupportedCommand;
}

static mspResult_e mspFcProcessOutCommandWithArg(uint8_t cmdMSP, sbuf_t *src, sbuf_t *dst, mspPostProcessFnPtr *mspPostProcessFn)
{

    switch (cmdMSP) {
    case MSP_BOXNAMES:
        {
            const int page = sbufBytesRemaining(src) ? sbufReadU8(src) : 0;
            serializeBoxReply(dst, page, &serializeBoxNameFn);
        }
        break;
    case MSP_BOXIDS:
        {
            const int page = sbufBytesRemaining(src) ? sbufReadU8(src) : 0;
            serializeBoxReply(dst, page, &serializeBoxPermanentIdFn);
        }
        break;
    case MSP_REBOOT:
        if (sbufBytesRemaining(src)) {
            rebootMode = sbufReadU8(src);

            if (rebootMode >= MSP_REBOOT_COUNT
#if !defined(USE_USB_MSC)
                || rebootMode == MSP_REBOOT_MSC || rebootMode == MSP_REBOOT_MSC_UTC
#endif
                ) {
                return MSP_RESULT_ERROR;
            }
        } else {
            rebootMode = MSP_REBOOT_FIRMWARE;
        }

        sbufWriteU8(dst, rebootMode);

#if defined(USE_USB_MSC)
        if (rebootMode == MSP_REBOOT_MSC) {
            if (mscCheckFilesystemReady()) {
                sbufWriteU8(dst, 1);
            } else {
                sbufWriteU8(dst, 0);

                return MSP_RESULT_ACK;
            }
        }
#endif

        if (mspPostProcessFn) {
            *mspPostProcessFn = mspRebootFn;
        }

        break;
    case MSP_MULTIPLE_MSP:
        {
            uint8_t maxMSPs = 0;
            if (sbufBytesRemaining(src) == 0) {
                return MSP_RESULT_ERROR;
            }
            int bytesRemaining = sbufBytesRemaining(dst) - 1; // need to keep one byte for checksum
            mspPacket_t packetIn, packetOut;
            sbufInit(&packetIn.buf, src->end, src->end);
            uint8_t* resetInputPtr = src->ptr;
            while (sbufBytesRemaining(src) && bytesRemaining > 0) {
                uint8_t newMSP = sbufReadU8(src);
                sbufInit(&packetOut.buf, dst->ptr, dst->end);
                packetIn.cmd = newMSP;
                mspFcProcessCommand(&packetIn, &packetOut, NULL);
                uint8_t mspSize = sbufPtr(&packetOut.buf) - dst->ptr;
                mspSize++; // need to add length information for each MSP
                bytesRemaining -= mspSize;
                if (bytesRemaining >= 0) {
                    maxMSPs++;
                }
            }
            src->ptr = resetInputPtr;
            sbufInit(&packetOut.buf, dst->ptr, dst->end);
            for (int i = 0; i < maxMSPs; i++) {
                uint8_t* sizePtr = sbufPtr(&packetOut.buf);
                sbufWriteU8(&packetOut.buf, 0); // dummy
                packetIn.cmd = sbufReadU8(src);
                mspFcProcessCommand(&packetIn, &packetOut, NULL);
                (*sizePtr) = sbufPtr(&packetOut.buf) - (sizePtr + 1);
            }
            dst->ptr = packetOut.buf.ptr;
        }
        break;
    default:
        return MSP_RESULT_CMD_UNKNOWN;
    }
    return MSP_RESULT_ACK;
}

#ifdef USE_FLASHFS
static void mspFcDataFlashReadCommand(sbuf_t *dst, sbuf_t *src)
{
    const unsigned int dataSize = sbufBytesRemaining(src);
    const uint32_t readAddress = sbufReadU32(src);
    uint16_t readLength;
    bool allowCompression = false;
    bool useLegacyFormat;
    if (dataSize >= sizeof(uint32_t) + sizeof(uint16_t)) {
        readLength = sbufReadU16(src);
        if (sbufBytesRemaining(src)) {
            allowCompression = sbufReadU8(src);
        }
        useLegacyFormat = false;
    } else {
        readLength = 128;
        useLegacyFormat = true;
    }

    serializeDataflashReadReply(dst, readAddress, readLength, useLegacyFormat, allowCompression);
}
#endif

static mspResult_e mspProcessInCommand(uint8_t cmdMSP, sbuf_t *src)
{
    uint32_t i;
    uint8_t value;
    const unsigned int dataSize = sbufBytesRemaining(src);
    switch (cmdMSP) {
    case MSP_SELECT_SETTING:
        value = sbufReadU8(src);
        if ((value & RATEPROFILE_MASK) == 0) {
            if (!ARMING_FLAG(ARMED)) {
                if (value >= PID_PROFILE_COUNT) {
                    value = 0;
                }
                changePidProfile(value);
            }
        } else {
            value = value & ~RATEPROFILE_MASK;

            if (value >= CONTROL_RATE_PROFILE_COUNT) {
                value = 0;
            }
            changeControlRateProfile(value);
        }
        break;

    case MSP_COPY_PROFILE:
        value = sbufReadU8(src);        // 0 = pid profile, 1 = control rate profile
        uint8_t dstProfileIndex = sbufReadU8(src);
        uint8_t srcProfileIndex = sbufReadU8(src);
        if (value == 0) {
            pidCopyProfile(dstProfileIndex, srcProfileIndex);
        }
        else if (value == 1) {
            copyControlRateProfile(dstProfileIndex, srcProfileIndex);
        }
        break;

#if defined(USE_GPS) || defined(USE_MAG)
    case MSP_SET_HEADING:
        magHold = sbufReadU16(src);
        break;
#endif

    case MSP_SET_RAW_RC:
#ifdef USE_RX_MSP
        {
            uint8_t channelCount = dataSize / sizeof(uint16_t);
            if (channelCount > MAX_SUPPORTED_RC_CHANNEL_COUNT) {
                return MSP_RESULT_ERROR;
            } else {
                uint16_t frame[MAX_SUPPORTED_RC_CHANNEL_COUNT];
                for (int i = 0; i < channelCount; i++) {
                    frame[i] = sbufReadU16(src);
                }
                rxMspFrameReceive(frame, channelCount);
            }
        }
#endif
        break;
#if defined(USE_ACC)
    case MSP_SET_ACC_TRIM:
        accelerometerConfigMutable()->accelerometerTrims.values.pitch = sbufReadU16(src);
        accelerometerConfigMutable()->accelerometerTrims.values.roll  = sbufReadU16(src);

        break;
#endif
    case MSP_SET_ARMING_CONFIG:
        armingConfigMutable()->auto_disarm_delay = sbufReadU8(src);
        sbufReadU8(src); // reserved
        if (sbufBytesRemaining(src)) {
          imuConfigMutable()->small_angle = sbufReadU8(src);
        }
        break;

    case MSP_SET_PID_CONTROLLER:
        break;

    case MSP_SET_PID:
        for (int i = 0; i < PID_ITEM_COUNT; i++) {
            currentPidProfile->pid[i].P = sbufReadU8(src);
            currentPidProfile->pid[i].I = sbufReadU8(src);
            currentPidProfile->pid[i].D = sbufReadU8(src);
        }
        pidInitConfig(currentPidProfile);
        break;

    case MSP_SET_MODE_RANGE:
        i = sbufReadU8(src);
        if (i < MAX_MODE_ACTIVATION_CONDITION_COUNT) {
            modeActivationCondition_t *mac = modeActivationConditionsMutable(i);
            i = sbufReadU8(src);
            const box_t *box = findBoxByPermanentId(i);
            if (box) {
                mac->modeId = box->boxId;
                mac->auxChannelIndex = sbufReadU8(src);
                mac->range.startStep = sbufReadU8(src);
                mac->range.endStep = sbufReadU8(src);
                if (sbufBytesRemaining(src) != 0) {
                    mac->modeLogic = sbufReadU8(src);

                    i = sbufReadU8(src);
                    mac->linkedTo = findBoxByPermanentId(i)->boxId;
                }
                rcControlsInit();
            } else {
                return MSP_RESULT_ERROR;
            }
        } else {
            return MSP_RESULT_ERROR;
        }
        break;

    case MSP_SET_ADJUSTMENT_RANGE:
        i = sbufReadU8(src);
        if (i < MAX_ADJUSTMENT_RANGE_COUNT) {
            adjustmentRange_t *adjRange = adjustmentRangesMutable(i);
            i = sbufReadU8(src);
            if (i < MAX_SIMULTANEOUS_ADJUSTMENT_COUNT) {
                adjRange->adjustmentIndex = i;
                adjRange->auxChannelIndex = sbufReadU8(src);
                adjRange->range.startStep = sbufReadU8(src);
                adjRange->range.endStep = sbufReadU8(src);
                adjRange->adjustmentConfig = sbufReadU8(src);
                adjRange->auxSwitchChannelIndex = sbufReadU8(src);
            } else {
                return MSP_RESULT_ERROR;
            }
            activeAdjustmentRangeReset();
        } else {
            return MSP_RESULT_ERROR;
        }
        break;

    case MSP_SET_RC_TUNING:
        if (sbufBytesRemaining(src) >= 10) {
            value = sbufReadU8(src);
            if (currentControlRateProfile->rcRates[FD_PITCH] == currentControlRateProfile->rcRates[FD_ROLL]) {
                currentControlRateProfile->rcRates[FD_PITCH] = value;
            }
            currentControlRateProfile->rcRates[FD_ROLL] = value;

            value = sbufReadU8(src);
            if (currentControlRateProfile->rcExpo[FD_PITCH] == currentControlRateProfile->rcExpo[FD_ROLL]) {
                currentControlRateProfile->rcExpo[FD_PITCH] = value;
            }
            currentControlRateProfile->rcExpo[FD_ROLL] = value;

            for (int i = 0; i < 3; i++) {
                currentControlRateProfile->rates[i] = sbufReadU8(src);
            }

            value = sbufReadU8(src);
            currentControlRateProfile->dynThrPID = MIN(value, CONTROL_RATE_CONFIG_TPA_MAX);
            currentControlRateProfile->thrMid8 = sbufReadU8(src);
            currentControlRateProfile->thrExpo8 = sbufReadU8(src);
            currentControlRateProfile->tpa_breakpoint = sbufReadU16(src);

            if (sbufBytesRemaining(src) >= 1) {
                currentControlRateProfile->rcExpo[FD_YAW] = sbufReadU8(src);
            }

            if (sbufBytesRemaining(src) >= 1) {
                currentControlRateProfile->rcRates[FD_YAW] = sbufReadU8(src);
            }

            if (sbufBytesRemaining(src) >= 1) {
                currentControlRateProfile->rcRates[FD_PITCH] = sbufReadU8(src);
            }

            if (sbufBytesRemaining(src) >= 1) {
                currentControlRateProfile->rcExpo[FD_PITCH] = sbufReadU8(src);
            }
            
            // version 1.41
            if (sbufBytesRemaining(src) >= 2) {
                currentControlRateProfile->throttle_limit_type = sbufReadU8(src);
                currentControlRateProfile->throttle_limit_percent = sbufReadU8(src);
            }

            initRcProcessing();
        } else {
            return MSP_RESULT_ERROR;
        }
        break;

    case MSP_SET_MOTOR_CONFIG:
        motorConfigMutable()->minthrottle = sbufReadU16(src);
        motorConfigMutable()->maxthrottle = sbufReadU16(src);
        motorConfigMutable()->mincommand = sbufReadU16(src);
        break;

#ifdef USE_GPS
    case MSP_SET_GPS_CONFIG:
        gpsConfigMutable()->provider = sbufReadU8(src);
        gpsConfigMutable()->sbasMode = sbufReadU8(src);
        gpsConfigMutable()->autoConfig = sbufReadU8(src);
        gpsConfigMutable()->autoBaud = sbufReadU8(src);
        break;

#ifdef USE_GPS_RESCUE
        case MSP_SET_GPS_RESCUE:
        gpsRescueConfigMutable()->angle = sbufReadU16(src);
        gpsRescueConfigMutable()->initialAltitudeM = sbufReadU16(src);
        gpsRescueConfigMutable()->descentDistanceM = sbufReadU16(src);
        gpsRescueConfigMutable()->rescueGroundspeed = sbufReadU16(src);
        gpsRescueConfigMutable()->throttleMin = sbufReadU16(src);
        gpsRescueConfigMutable()->throttleMax = sbufReadU16(src);
        gpsRescueConfigMutable()->throttleHover = sbufReadU16(src);
        gpsRescueConfigMutable()->sanityChecks = sbufReadU8(src);
        gpsRescueConfigMutable()->minSats = sbufReadU8(src);
        break;

    case MSP_SET_GPS_RESCUE_PIDS:
        gpsRescueConfigMutable()->throttleP = sbufReadU16(src);
        gpsRescueConfigMutable()->throttleI = sbufReadU16(src);
        gpsRescueConfigMutable()->throttleD = sbufReadU16(src);
        gpsRescueConfigMutable()->velP = sbufReadU16(src);
        gpsRescueConfigMutable()->velI = sbufReadU16(src);
        gpsRescueConfigMutable()->velD = sbufReadU16(src);
        gpsRescueConfigMutable()->yawP = sbufReadU16(src);
        break;
#endif
#endif

#ifdef USE_MAG
    case MSP_SET_COMPASS_CONFIG:
        compassConfigMutable()->mag_declination = sbufReadU16(src) * 10;
        break;
#endif

    case MSP_SET_MOTOR:
        for (int i = 0; i < getMotorCount(); i++) {
            motor_disarmed[i] = convertExternalToMotor(sbufReadU16(src));
        }
        break;

    case MSP_SET_SERVO_CONFIGURATION:
#ifdef USE_SERVOS
        if (dataSize != 1 + 12) {
            return MSP_RESULT_ERROR;
        }
        i = sbufReadU8(src);
        if (i >= MAX_SUPPORTED_SERVOS) {
            return MSP_RESULT_ERROR;
        } else {
            servoParamsMutable(i)->min = sbufReadU16(src);
            servoParamsMutable(i)->max = sbufReadU16(src);
            servoParamsMutable(i)->middle = sbufReadU16(src);
            servoParamsMutable(i)->rate = sbufReadU8(src);
            servoParamsMutable(i)->forwardFromChannel = sbufReadU8(src);
            servoParamsMutable(i)->reversedSources = sbufReadU32(src);
        }
#endif
        break;

    case MSP_SET_SERVO_MIX_RULE:
#ifdef USE_SERVOS
        i = sbufReadU8(src);
        if (i >= MAX_SERVO_RULES) {
            return MSP_RESULT_ERROR;
        } else {
            customServoMixersMutable(i)->targetChannel = sbufReadU8(src);
            customServoMixersMutable(i)->inputSource = sbufReadU8(src);
            customServoMixersMutable(i)->rate = sbufReadU8(src);
            customServoMixersMutable(i)->speed = sbufReadU8(src);
            customServoMixersMutable(i)->min = sbufReadU8(src);
            customServoMixersMutable(i)->max = sbufReadU8(src);
            customServoMixersMutable(i)->box = sbufReadU8(src);
            loadCustomServoMixer();
        }
#endif
        break;

    case MSP_SET_MOTOR_3D_CONFIG:
        flight3DConfigMutable()->deadband3d_low = sbufReadU16(src);
        flight3DConfigMutable()->deadband3d_high = sbufReadU16(src);
        flight3DConfigMutable()->neutral3d = sbufReadU16(src);
        break;

    case MSP_SET_RC_DEADBAND:
        rcControlsConfigMutable()->deadband = sbufReadU8(src);
        rcControlsConfigMutable()->yaw_deadband = sbufReadU8(src);
        rcControlsConfigMutable()->alt_hold_deadband = sbufReadU8(src);
        flight3DConfigMutable()->deadband3d_throttle = sbufReadU16(src);
        break;

    case MSP_SET_RESET_CURR_PID:
        resetPidProfile(currentPidProfile);
        break;
    case MSP_SET_SENSOR_ALIGNMENT: {
        // maintain backwards compatibility for API < 1.41
        const uint8_t gyroAlignment = sbufReadU8(src);
        sbufReadU8(src);  // discard deprecated acc_align
        compassConfigMutable()->mag_align = sbufReadU8(src);

        if (sbufBytesRemaining(src) >= 3) {
            // API >= 1.41 - support the gyro_to_use and alignment for gyros 1 & 2
#ifdef USE_MULTI_GYRO
            gyroConfigMutable()->gyro_to_use = sbufReadU8(src);
            gyroDeviceConfigMutable(0)->align = sbufReadU8(src);
            gyroDeviceConfigMutable(1)->align = sbufReadU8(src);
#else
            sbufReadU8(src);  // unused gyro_to_use
            gyroDeviceConfigMutable(0)->align = sbufReadU8(src);
            sbufReadU8(src);  // unused gyro_2_sensor_align
#endif
        } else {
            // maintain backwards compatibility for API < 1.41
#ifdef USE_MULTI_GYRO
            switch (gyroConfig()->gyro_to_use) {
            case GYRO_CONFIG_USE_GYRO_2:
                gyroDeviceConfigMutable(1)->align = gyroAlignment;
                break;
            case GYRO_CONFIG_USE_GYRO_BOTH:
                // For dual-gyro in "BOTH" mode we'll only update gyro 0
            default:
                gyroDeviceConfigMutable(0)->align = gyroAlignment;
                break;
            }
#else
            gyroDeviceConfigMutable(0)->align = gyroAlignment;
#endif

        }
        break;
    }

    case MSP_SET_ADVANCED_CONFIG:
        gyroConfigMutable()->gyro_sync_denom = sbufReadU8(src);
        pidConfigMutable()->pid_process_denom = sbufReadU8(src);
        motorConfigMutable()->dev.useUnsyncedPwm = sbufReadU8(src);
#ifdef USE_DSHOT
        motorConfigMutable()->dev.motorPwmProtocol = constrain(sbufReadU8(src), 0, PWM_TYPE_MAX - 1);
#else
        motorConfigMutable()->dev.motorPwmProtocol = constrain(sbufReadU8(src), 0, PWM_TYPE_BRUSHED);
#endif
        motorConfigMutable()->dev.motorPwmRate = sbufReadU16(src);
        if (sbufBytesRemaining(src) >= 2) {
            motorConfigMutable()->digitalIdleOffsetValue = sbufReadU16(src);
        }
        if (sbufBytesRemaining(src)) {
            sbufReadU8(src); // DEPRECATED: gyro_use_32khz
        }
        if (sbufBytesRemaining(src)) {
            motorConfigMutable()->dev.motorPwmInversion = sbufReadU8(src);
        }
        if (sbufBytesRemaining(src) >= 8) {
            gyroConfigMutable()->gyro_to_use = sbufReadU8(src);
            gyroConfigMutable()->gyro_high_fsr = sbufReadU8(src);
            gyroConfigMutable()->gyroMovementCalibrationThreshold = sbufReadU8(src);
            gyroConfigMutable()->gyroCalibrationDuration = sbufReadU16(src);
            gyroConfigMutable()->gyro_offset_yaw = sbufReadU16(src);
            gyroConfigMutable()->checkOverflow = sbufReadU8(src);
        }

        validateAndFixGyroConfig();

        break;
    case MSP_SET_FILTER_CONFIG:
        gyroConfigMutable()->gyro_lowpass_hz = sbufReadU8(src);
        currentPidProfile->dterm_lowpass_hz = sbufReadU16(src);
        currentPidProfile->yaw_lowpass_hz = sbufReadU16(src);
        if (sbufBytesRemaining(src) >= 8) {
            gyroConfigMutable()->gyro_soft_notch_hz_1 = sbufReadU16(src);
            gyroConfigMutable()->gyro_soft_notch_cutoff_1 = sbufReadU16(src);
            currentPidProfile->dterm_notch_hz = sbufReadU16(src);
            currentPidProfile->dterm_notch_cutoff = sbufReadU16(src);
        }
        if (sbufBytesRemaining(src) >= 4) {
            gyroConfigMutable()->gyro_soft_notch_hz_2 = sbufReadU16(src);
            gyroConfigMutable()->gyro_soft_notch_cutoff_2 = sbufReadU16(src);
        }
        if (sbufBytesRemaining(src) >= 1) {
            currentPidProfile->dterm_filter_type = sbufReadU8(src);
        }
        if (sbufBytesRemaining(src) >= 10) {
            gyroConfigMutable()->gyro_hardware_lpf = sbufReadU8(src);
            sbufReadU8(src); // DEPRECATED: gyro_32khz_hardware_lpf
            gyroConfigMutable()->gyro_lowpass_hz = sbufReadU16(src);
            gyroConfigMutable()->gyro_lowpass2_hz = sbufReadU16(src);
            gyroConfigMutable()->gyro_lowpass_type = sbufReadU8(src);
            gyroConfigMutable()->gyro_lowpass2_type = sbufReadU8(src);
            currentPidProfile->dterm_lowpass2_hz = sbufReadU16(src);
        }
        if (sbufBytesRemaining(src) >= 9) {
            // Added in MSP API 1.41
            currentPidProfile->dterm_filter2_type = sbufReadU8(src);
#if defined(USE_DYN_LPF)
            gyroConfigMutable()->dyn_lpf_gyro_min_hz = sbufReadU16(src);
            gyroConfigMutable()->dyn_lpf_gyro_max_hz = sbufReadU16(src);
            currentPidProfile->dyn_lpf_dterm_min_hz = sbufReadU16(src);
            currentPidProfile->dyn_lpf_dterm_max_hz = sbufReadU16(src);
#else
            sbufReadU16(src);
            sbufReadU16(src);
            sbufReadU16(src);
            sbufReadU16(src);
#endif
        }

        // reinitialize the gyro filters with the new values
        validateAndFixGyroConfig();
        gyroInitFilters();
        // reinitialize the PID filters with the new values
        pidInitFilters(currentPidProfile);

        break;
    case MSP_SET_PID_ADVANCED:
        sbufReadU16(src);
        sbufReadU16(src);
        sbufReadU16(src); // was pidProfile.yaw_p_limit
        sbufReadU8(src); // reserved
        currentPidProfile->vbatPidCompensation = sbufReadU8(src);
        currentPidProfile->feedForwardTransition = sbufReadU8(src);
        sbufReadU8(src); // was low byte of currentPidProfile->dtermSetpointWeight
        sbufReadU8(src); // reserved
        sbufReadU8(src); // reserved
        sbufReadU8(src); // reserved
        currentPidProfile->rateAccelLimit = sbufReadU16(src);
        currentPidProfile->yawRateAccelLimit = sbufReadU16(src);
        if (sbufBytesRemaining(src) >= 2) {
            currentPidProfile->levelAngleLimit = sbufReadU8(src);
            sbufReadU8(src); // was pidProfile.levelSensitivity
        }
        if (sbufBytesRemaining(src) >= 4) {
            currentPidProfile->itermThrottleThreshold = sbufReadU16(src);
            currentPidProfile->itermAcceleratorGain = sbufReadU16(src);
        }
        if (sbufBytesRemaining(src) >= 2) {
            sbufReadU16(src); // was currentPidProfile->dtermSetpointWeight
        }
        if (sbufBytesRemaining(src) >= 14) {
            // Added in MSP API 1.40
            currentPidProfile->iterm_rotation = sbufReadU8(src);
#if defined(USE_SMART_FEEDFORWARD)
            currentPidProfile->smart_feedforward = sbufReadU8(src);
#else
            sbufReadU8(src);
#endif
#if defined(USE_ITERM_RELAX)
            currentPidProfile->iterm_relax = sbufReadU8(src);
            currentPidProfile->iterm_relax_type = sbufReadU8(src);
#else
            sbufReadU8(src);
            sbufReadU8(src);
#endif
#if defined(USE_ABSOLUTE_CONTROL)
            currentPidProfile->abs_control_gain = sbufReadU8(src);
#else
            sbufReadU8(src);
#endif
#if defined(USE_THROTTLE_BOOST)
            currentPidProfile->throttle_boost = sbufReadU8(src);
#else
            sbufReadU8(src);
#endif
#if defined(USE_ACRO_TRAINER)
            currentPidProfile->acro_trainer_angle_limit = sbufReadU8(src);
#else
            sbufReadU8(src);
#endif
            // PID controller feedforward terms
            currentPidProfile->pid[PID_ROLL].F = sbufReadU16(src);
            currentPidProfile->pid[PID_PITCH].F = sbufReadU16(src);
            currentPidProfile->pid[PID_YAW].F = sbufReadU16(src);

            currentPidProfile->antiGravityMode = sbufReadU8(src);
        }
        if (sbufBytesRemaining(src) >= 7) {
            // Added in MSP API 1.41
#if defined(USE_D_MIN)
            currentPidProfile->d_min[PID_ROLL] = sbufReadU8(src);
            currentPidProfile->d_min[PID_PITCH] = sbufReadU8(src);
            currentPidProfile->d_min[PID_YAW] = sbufReadU8(src);
            currentPidProfile->d_min_gain = sbufReadU8(src);
            currentPidProfile->d_min_advance = sbufReadU8(src);
#else
            sbufReadU8(src);
            sbufReadU8(src);
            sbufReadU8(src);
            sbufReadU8(src);
            sbufReadU8(src);
#endif
#if defined(USE_INTEGRATED_YAW_CONTROL)
            currentPidProfile->use_integrated_yaw = sbufReadU8(src);
            currentPidProfile->integrated_yaw_relax = sbufReadU8(src);
#else
            sbufReadU8(src);
            sbufReadU8(src);
#endif
        }
        pidInitConfig(currentPidProfile);

        break;
    case MSP_SET_SENSOR_CONFIG:
#if defined(USE_ACC)
        accelerometerConfigMutable()->acc_hardware = sbufReadU8(src);
#else
        sbufReadU8(src);
#endif
#if defined(USE_BARO)
        barometerConfigMutable()->baro_hardware = sbufReadU8(src);
#else
        sbufReadU8(src);
#endif
#if defined(USE_MAG)
        compassConfigMutable()->mag_hardware = sbufReadU8(src);
#else
        sbufReadU8(src);
#endif
        break;

    case MSP_RESET_CONF:
        if (!ARMING_FLAG(ARMED)) {
            resetEEPROM();
            readEEPROM();
        }
        break;

#ifdef USE_ACC
    case MSP_ACC_CALIBRATION:
        if (!ARMING_FLAG(ARMED))
            accSetCalibrationCycles(CALIBRATING_ACC_CYCLES);
        break;
#endif

    case MSP_MAG_CALIBRATION:
        if (!ARMING_FLAG(ARMED))
            ENABLE_STATE(CALIBRATE_MAG);
        break;

    case MSP_EEPROM_WRITE:
        if (ARMING_FLAG(ARMED)) {
            return MSP_RESULT_ERROR;
        }

        if (featureMaskIsCopied) {
            writeEEPROMWithFeatures(featureMaskCopy);
        } else {
            writeEEPROM();
        }
        readEEPROM();
        break;

#ifdef USE_BLACKBOX
    case MSP_SET_BLACKBOX_CONFIG:
        // Don't allow config to be updated while Blackbox is logging
        if (blackboxMayEditConfig()) {
            blackboxConfigMutable()->device = sbufReadU8(src);
            const int rateNum = sbufReadU8(src); // was rate_num
            const int rateDenom = sbufReadU8(src); // was rate_denom
            if (sbufBytesRemaining(src) >= 2) {
                // p_ratio specified, so use it directly
                blackboxConfigMutable()->p_ratio = sbufReadU16(src);
            } else {
                // p_ratio not specified in MSP, so calculate it from old rateNum and rateDenom
                blackboxConfigMutable()->p_ratio = blackboxCalculatePDenom(rateNum, rateDenom);
            }
        }
        break;
#endif

#ifdef USE_VTX_COMMON
    case MSP_SET_VTX_CONFIG:
        {
            vtxDevice_t *vtxDevice = vtxCommonDevice();
            vtxDevType_e vtxType = VTXDEV_UNKNOWN;
            if (vtxDevice) {
                vtxType = vtxCommonGetDeviceType(vtxDevice);
            }
            uint16_t newFrequency = sbufReadU16(src);
            if (newFrequency <= VTXCOMMON_MSP_BANDCHAN_CHKVAL) {  // Value is band and channel
                const uint8_t newBand = (newFrequency / 8) + 1;
                const uint8_t newChannel = (newFrequency % 8) + 1;
                vtxSettingsConfigMutable()->band = newBand;
                vtxSettingsConfigMutable()->channel = newChannel;
                vtxSettingsConfigMutable()->freq = vtxCommonLookupFrequency(vtxDevice, newBand, newChannel);
            } else if (newFrequency <= VTX_SETTINGS_MAX_FREQUENCY_MHZ) { // Value is frequency in MHz
                vtxSettingsConfigMutable()->band = 0;
                vtxSettingsConfigMutable()->freq = newFrequency;
            }

            if (sbufBytesRemaining(src) >= 2) {
                vtxSettingsConfigMutable()->power = sbufReadU8(src);
                if (vtxType != VTXDEV_UNKNOWN) {
                    // Delegate pitmode to vtx directly
                    const uint8_t newPitmode = sbufReadU8(src);
                    uint8_t currentPitmode = 0;
                    vtxCommonGetPitMode(vtxDevice, &currentPitmode);
                    if (currentPitmode != newPitmode) {
                        vtxCommonSetPitMode(vtxDevice, newPitmode);
                    }

                    if (sbufBytesRemaining(src)) {
                        vtxSettingsConfigMutable()->lowPowerDisarm = sbufReadU8(src);
                    }
                }
            }
        }
        break;
#endif

#ifdef USE_CAMERA_CONTROL
    case MSP_CAMERA_CONTROL:
        {
            if (ARMING_FLAG(ARMED)) {
                return MSP_RESULT_ERROR;
            }

            const uint8_t key = sbufReadU8(src);
            cameraControlKeyPress(key, 0);
        }
        break;
#endif

    case MSP_SET_ARMING_DISABLED:
        {
//             const uint8_t command = sbufReadU8(src);
//             uint8_t disableRunawayTakeoff = 0;
// #ifndef USE_RUNAWAY_TAKEOFF
//             UNUSED(disableRunawayTakeoff);
// #endif
//             if (sbufBytesRemaining(src)) {
//                 disableRunawayTakeoff = sbufReadU8(src);
//             }
//             if (command) {
//                 setArmingDisabled(ARMING_DISABLED_MSP);
//                 if (ARMING_FLAG(ARMED)) {
//                     disarm();
//                 }
// #ifdef USE_RUNAWAY_TAKEOFF
//                 runawayTakeoffTemporaryDisable(false);
// #endif
//             } else {
//                 unsetArmingDisabled(ARMING_DISABLED_MSP);
// #ifdef USE_RUNAWAY_TAKEOFF
//                 runawayTakeoffTemporaryDisable(disableRunawayTakeoff);
// #endif
//             }
        }
        break;

#ifdef USE_FLASHFS
    case MSP_DATAFLASH_ERASE:
        flashfsEraseCompletely();

        break;
#endif

#ifdef USE_GPS
    case MSP_SET_RAW_GPS:
        if (sbufReadU8(src)) {
            ENABLE_STATE(GPS_FIX);
        } else {
            DISABLE_STATE(GPS_FIX);
        }
        gpsSol.numSat = sbufReadU8(src);
        gpsSol.llh.lat = sbufReadU32(src);
        gpsSol.llh.lon = sbufReadU32(src);
        gpsSol.llh.altCm = sbufReadU16(src) * 100; // alt changed from 1m to 0.01m per lsb since MSP API 1.39 by RTH. Received MSP altitudes in 1m per lsb have to upscaled.
        gpsSol.groundSpeed = sbufReadU16(src);
        GPS_update |= GPS_MSP_UPDATE;        // MSP data signalisation to GPS functions
        break;
#endif // USE_GPS
    case MSP_SET_FEATURE_CONFIG:
        featureMaskCopy = sbufReadU32(src);
        if (!featureMaskIsCopied) {
            featureMaskIsCopied = true;
        }

        break;

#ifdef USE_BEEPER
    case MSP_SET_BEEPER_CONFIG:
        beeperConfigMutable()->beeper_off_flags = sbufReadU32(src);
        if (sbufBytesRemaining(src) >= 1) {
            beeperConfigMutable()->dshotBeaconTone = sbufReadU8(src);
        }
        if (sbufBytesRemaining(src) >= 4) {
            beeperConfigMutable()->dshotBeaconOffFlags = sbufReadU32(src);
        }
        break;
#endif

    case MSP_SET_BOARD_ALIGNMENT_CONFIG:
        boardAlignmentMutable()->rollDegrees = sbufReadU16(src);
        boardAlignmentMutable()->pitchDegrees = sbufReadU16(src);
        boardAlignmentMutable()->yawDegrees = sbufReadU16(src);
        break;

    case MSP_SET_MIXER_CONFIG:
#ifndef USE_QUAD_MIXER_ONLY
        mixerConfigMutable()->mixerMode = sbufReadU8(src);
#else
        sbufReadU8(src);
#endif
        if (sbufBytesRemaining(src) >= 1) {
            mixerConfigMutable()->yaw_motors_reversed = sbufReadU8(src);
        }
        break;

    case MSP_SET_RX_CONFIG:
        rxConfigMutable()->serialrx_provider = sbufReadU8(src);
        rxConfigMutable()->maxcheck = sbufReadU16(src);
        rxConfigMutable()->midrc = sbufReadU16(src);
        rxConfigMutable()->mincheck = sbufReadU16(src);
        rxConfigMutable()->spektrum_sat_bind = sbufReadU8(src);
        if (sbufBytesRemaining(src) >= 4) {
            rxConfigMutable()->rx_min_usec = sbufReadU16(src);
            rxConfigMutable()->rx_max_usec = sbufReadU16(src);
        }
        if (sbufBytesRemaining(src) >= 4) {
            rxConfigMutable()->rcInterpolation = sbufReadU8(src);
            rxConfigMutable()->rcInterpolationInterval = sbufReadU8(src);
            rxConfigMutable()->airModeActivateThreshold = (sbufReadU16(src) - 1000) / 10;
        }
        if (sbufBytesRemaining(src) >= 6) {
#ifdef USE_RX_SPI
            rxSpiConfigMutable()->rx_spi_protocol = sbufReadU8(src);
            rxSpiConfigMutable()->rx_spi_id = sbufReadU32(src);
            rxSpiConfigMutable()->rx_spi_rf_channel_count = sbufReadU8(src);
#else
            sbufReadU8(src);
            sbufReadU32(src);
            sbufReadU8(src);
#endif
        }
        if (sbufBytesRemaining(src) >= 1) {
            rxConfigMutable()->fpvCamAngleDegrees = sbufReadU8(src);
        }
        if (sbufBytesRemaining(src) >= 6) {
            // Added in MSP API 1.40
            rxConfigMutable()->rcInterpolationChannels = sbufReadU8(src);
#if defined(USE_RC_SMOOTHING_FILTER)
            rxConfigMutable()->rc_smoothing_type = sbufReadU8(src);
            rxConfigMutable()->rc_smoothing_input_cutoff = sbufReadU8(src);
            rxConfigMutable()->rc_smoothing_derivative_cutoff = sbufReadU8(src);
            rxConfigMutable()->rc_smoothing_input_type = sbufReadU8(src);
            rxConfigMutable()->rc_smoothing_derivative_type = sbufReadU8(src);
#else
            sbufReadU8(src);
            sbufReadU8(src);
            sbufReadU8(src);
            sbufReadU8(src);
            sbufReadU8(src);
#endif
        }
        if (sbufBytesRemaining(src) >= 1) {
            // Added in MSP API 1.40
            // Kept separate from the section above to work around missing Configurator support in version < 10.4.2
#if defined(USE_USB_CDC_HID)
            usbDevConfigMutable()->type = sbufReadU8(src);
#else
            sbufReadU8(src);
#endif
        }

        break;
    case MSP_SET_FAILSAFE_CONFIG:
        failsafeConfigMutable()->failsafe_delay = sbufReadU8(src);
        failsafeConfigMutable()->failsafe_off_delay = sbufReadU8(src);
        failsafeConfigMutable()->failsafe_throttle = sbufReadU16(src);
        failsafeConfigMutable()->failsafe_switch_mode = sbufReadU8(src);
        failsafeConfigMutable()->failsafe_throttle_low_delay = sbufReadU16(src);
        failsafeConfigMutable()->failsafe_procedure = sbufReadU8(src);
        break;

    case MSP_SET_RXFAIL_CONFIG:
        i = sbufReadU8(src);
        if (i < MAX_SUPPORTED_RC_CHANNEL_COUNT) {
            rxFailsafeChannelConfigsMutable(i)->mode = sbufReadU8(src);
            rxFailsafeChannelConfigsMutable(i)->step = CHANNEL_VALUE_TO_RXFAIL_STEP(sbufReadU16(src));
        } else {
            return MSP_RESULT_ERROR;
        }
        break;

    case MSP_SET_RSSI_CONFIG:
        rxConfigMutable()->rssi_channel = sbufReadU8(src);
        break;

    case MSP_SET_RX_MAP:
        for (int i = 0; i < RX_MAPPABLE_CHANNEL_COUNT; i++) {
            rxConfigMutable()->rcmap[i] = sbufReadU8(src);
        }
        break;

    case MSP_SET_CF_SERIAL_CONFIG:
        {
            uint8_t portConfigSize = sizeof(uint8_t) + sizeof(uint16_t) + (sizeof(uint8_t) * 4);

            if (dataSize % portConfigSize != 0) {
                return MSP_RESULT_ERROR;
            }

            uint8_t remainingPortsInPacket = dataSize / portConfigSize;

            while (remainingPortsInPacket--) {
                uint8_t identifier = sbufReadU8(src);

                serialPortConfig_t *portConfig = serialFindPortConfiguration(identifier);
                if (!portConfig) {
                    return MSP_RESULT_ERROR;
                }

                portConfig->identifier = identifier;
                portConfig->functionMask = sbufReadU16(src);
                portConfig->msp_baudrateIndex = sbufReadU8(src);
                portConfig->gps_baudrateIndex = sbufReadU8(src);
                portConfig->telemetry_baudrateIndex = sbufReadU8(src);
                portConfig->blackbox_baudrateIndex = sbufReadU8(src);
            }
        }
        break;

#ifdef USE_LED_STRIP_STATUS_MODE
    case MSP_SET_LED_COLORS:
        for (int i = 0; i < LED_CONFIGURABLE_COLOR_COUNT; i++) {
            hsvColor_t *color = &ledStripStatusModeConfigMutable()->colors[i];
            color->h = sbufReadU16(src);
            color->s = sbufReadU8(src);
            color->v = sbufReadU8(src);
        }
        break;
#endif

#ifdef USE_LED_STRIP
    case MSP_SET_LED_STRIP_CONFIG:
        {
            i = sbufReadU8(src);
            if (i >= LED_MAX_STRIP_LENGTH || dataSize != (1 + 4)) {
                return MSP_RESULT_ERROR;
            }
#ifdef USE_LED_STRIP_STATUS_MODE
            ledConfig_t *ledConfig = &ledStripStatusModeConfigMutable()->ledConfigs[i];
            *ledConfig = sbufReadU32(src);
            reevaluateLedConfig();
#else
            sbufReadU32(src);
#endif
            // API 1.41 - selected ledstrip_profile
            if (sbufBytesRemaining(src) >= 1) {
                ledStripConfigMutable()->ledstrip_profile = sbufReadU8(src);
            }
        }
        break;
#endif

#ifdef USE_LED_STRIP_STATUS_MODE
    case MSP_SET_LED_STRIP_MODECOLOR:
        {
            ledModeIndex_e modeIdx = sbufReadU8(src);
            int funIdx = sbufReadU8(src);
            int color = sbufReadU8(src);

            if (!setModeColor(modeIdx, funIdx, color)) {
                return MSP_RESULT_ERROR;
            }
        }
        break;
#endif

    case MSP_SET_NAME:
        memset(pilotConfigMutable()->name, 0, ARRAYLEN(pilotConfig()->name));
        for (unsigned int i = 0; i < MIN(MAX_NAME_LENGTH, dataSize); i++) {
            pilotConfigMutable()->name[i] = sbufReadU8(src);
        }
        break;

#ifdef USE_RTC_TIME
    case MSP_SET_RTC:
        {
            // Use seconds and milliseconds to make senders
            // easier to implement. Generating a 64 bit value
            // might not be trivial in some platforms.
            int32_t secs = (int32_t)sbufReadU32(src);
            uint16_t millis = sbufReadU16(src);
            rtcTime_t t = rtcTimeMake(secs, millis);
            rtcSet(&t);
        }

        break;
#endif

    case MSP_SET_TX_INFO:
        setRssiMsp(sbufReadU8(src));

        break;

#if defined(USE_BOARD_INFO)
    case MSP_SET_BOARD_INFO:
        if (!boardInformationIsSet()) {
            uint8_t length = sbufReadU8(src);
            char boardName[MAX_BOARD_NAME_LENGTH + 1];
            sbufReadData(src, boardName, MIN(length, MAX_BOARD_NAME_LENGTH));
            if (length > MAX_BOARD_NAME_LENGTH) {
                sbufAdvance(src, length - MAX_BOARD_NAME_LENGTH);
            }
            boardName[length] = '\0';
            length = sbufReadU8(src);
            char manufacturerId[MAX_MANUFACTURER_ID_LENGTH + 1];
            sbufReadData(src, manufacturerId, MIN(length, MAX_MANUFACTURER_ID_LENGTH));
            if (length > MAX_MANUFACTURER_ID_LENGTH) {
                sbufAdvance(src, length - MAX_MANUFACTURER_ID_LENGTH);
            }
            manufacturerId[length] = '\0';

            setBoardName(boardName);
            setManufacturerId(manufacturerId);
            persistBoardInformation();
        } else {
            return MSP_RESULT_ERROR;
        }

        break;
#if defined(USE_SIGNATURE)
    case MSP_SET_SIGNATURE:
        if (!signatureIsSet()) {
            uint8_t signature[SIGNATURE_LENGTH];
            sbufReadData(src, signature, SIGNATURE_LENGTH);
            setSignature(signature);
            persistSignature();
        } else {
            return MSP_RESULT_ERROR;
        }

        break;
#endif
#endif // USE_BOARD_INFO
    default:
        // we do not know how to handle the (valid) message, indicate error MSP $M!
        return MSP_RESULT_ERROR;
    }
    return MSP_RESULT_ACK;
}

static mspResult_e mspCommonProcessInCommand(uint8_t cmdMSP, sbuf_t *src, mspPostProcessFnPtr *mspPostProcessFn)
{
    UNUSED(mspPostProcessFn);
    const unsigned int dataSize = sbufBytesRemaining(src);
    UNUSED(dataSize); // maybe unused due to compiler options

    switch (cmdMSP) {
#ifdef USE_TRANSPONDER
    case MSP_SET_TRANSPONDER_CONFIG: {
        // Backward compatibility to BFC 3.1.1 is lost for this message type

        uint8_t provider = sbufReadU8(src);
        uint8_t bytesRemaining = dataSize - 1;

        if (provider > TRANSPONDER_PROVIDER_COUNT) {
            return MSP_RESULT_ERROR;
        }

        const uint8_t requirementIndex = provider - 1;
        const uint8_t transponderDataSize = transponderRequirements[requirementIndex].dataLength;

        transponderConfigMutable()->provider = provider;

        if (provider == TRANSPONDER_NONE) {
            break;
        }

        if (bytesRemaining != transponderDataSize) {
            return MSP_RESULT_ERROR;
        }

        if (provider != transponderConfig()->provider) {
            transponderStopRepeating();
        }

        memset(transponderConfigMutable()->data, 0, sizeof(transponderConfig()->data));

        for (unsigned int i = 0; i < transponderDataSize; i++) {
            transponderConfigMutable()->data[i] = sbufReadU8(src);
        }
        transponderUpdateData();
        break;
    }
#endif

    case MSP_SET_VOLTAGE_METER_CONFIG: {
        int8_t id = sbufReadU8(src);

        //
        // find and configure an ADC voltage sensor
        //
        int8_t voltageSensorADCIndex;
        for (voltageSensorADCIndex = 0; voltageSensorADCIndex < MAX_VOLTAGE_SENSOR_ADC; voltageSensorADCIndex++) {
            if (id == voltageMeterADCtoIDMap[voltageSensorADCIndex]) {
                break;
            }
        }

        if (voltageSensorADCIndex < MAX_VOLTAGE_SENSOR_ADC) {
            voltageSensorADCConfigMutable(voltageSensorADCIndex)->vbatscale = sbufReadU8(src);
            voltageSensorADCConfigMutable(voltageSensorADCIndex)->vbatresdivval = sbufReadU8(src);
            voltageSensorADCConfigMutable(voltageSensorADCIndex)->vbatresdivmultiplier = sbufReadU8(src);
        } else {
            // if we had any other types of voltage sensor to configure, this is where we'd do it.
            sbufReadU8(src);
            sbufReadU8(src);
            sbufReadU8(src);
        }
        break;
    }

    case MSP_SET_CURRENT_METER_CONFIG: {
        int id = sbufReadU8(src);

        switch (id) {
            case CURRENT_METER_ID_BATTERY_1:
                currentSensorADCConfigMutable()->scale = sbufReadU16(src);
                currentSensorADCConfigMutable()->offset = sbufReadU16(src);
                break;
#ifdef USE_VIRTUAL_CURRENT_METER
            case CURRENT_METER_ID_VIRTUAL_1:
                currentSensorVirtualConfigMutable()->scale = sbufReadU16(src);
                currentSensorVirtualConfigMutable()->offset = sbufReadU16(src);
                break;
#endif
            default:
                sbufReadU16(src);
                sbufReadU16(src);
                break;
        }
        break;
    }

    case MSP_SET_BATTERY_CONFIG:
        batteryConfigMutable()->vbatmincellvoltage = sbufReadU8(src) * 10;      // vbatlevel_warn1 in MWC2.3 GUI
        batteryConfigMutable()->vbatmaxcellvoltage = sbufReadU8(src) * 10;      // vbatlevel_warn2 in MWC2.3 GUI
        batteryConfigMutable()->vbatwarningcellvoltage = sbufReadU8(src) * 10;  // vbatlevel when buzzer starts to alert
        batteryConfigMutable()->batteryCapacity = sbufReadU16(src);
        batteryConfigMutable()->voltageMeterSource = sbufReadU8(src);
        batteryConfigMutable()->currentMeterSource = sbufReadU8(src);
        if (sbufBytesRemaining(src) >= 6) {
            batteryConfigMutable()->vbatmincellvoltage = sbufReadU16(src);
            batteryConfigMutable()->vbatmaxcellvoltage = sbufReadU16(src);
            batteryConfigMutable()->vbatwarningcellvoltage = sbufReadU16(src);
        }
        break;

#if defined(USE_OSD)
    case MSP_SET_OSD_CONFIG:
        {
            const uint8_t addr = sbufReadU8(src);

            if ((int8_t)addr == -1) {
                /* Set general OSD settings */
#ifdef USE_MAX7456
                vcdProfileMutable()->video_system = sbufReadU8(src);
#else
                sbufReadU8(src); // Skip video system
#endif
#if defined(USE_OSD)
                osdConfigMutable()->units = sbufReadU8(src);

                // Alarms
                osdConfigMutable()->rssi_alarm = sbufReadU8(src);
                osdConfigMutable()->cap_alarm = sbufReadU16(src);
                sbufReadU16(src); // Skip unused (previously fly timer)
                osdConfigMutable()->alt_alarm = sbufReadU16(src);

                if (sbufBytesRemaining(src) >= 2) {
                    /* Enabled warnings */
                    // API < 1.41 supports only the low 16 bits
                    osdConfigMutable()->enabledWarnings = sbufReadU16(src);
                }
                
                if (sbufBytesRemaining(src) >= 4) {
                    // 32bit version of enabled warnings (API >= 1.41)
                    osdConfigMutable()->enabledWarnings = sbufReadU32(src);
                }

                if (sbufBytesRemaining(src) >= 1) {
                    // API >= 1.41
                    // selected OSD profile
#ifdef USE_OSD_PROFILES
                    changeOsdProfileIndex(sbufReadU8(src));
#else
                    sbufReadU8(src);
#endif // USE_OSD_PROFILES
                }

                if (sbufBytesRemaining(src) >= 1) {
                    // API >= 1.41
                    // OSD stick overlay mode

#ifdef USE_OSD_STICK_OVERLAY
                    osdConfigMutable()->overlay_radio_mode = sbufReadU8(src);
#else
                    sbufReadU8(src);
#endif // USE_OSD_STICK_OVERLAY

                }
#endif
            } else if ((int8_t)addr == -2) {
#if defined(USE_OSD)
                // Timers
                uint8_t index = sbufReadU8(src);
                if (index > OSD_TIMER_COUNT) {
                  return MSP_RESULT_ERROR;
                }
                osdConfigMutable()->timers[index] = sbufReadU16(src);
#endif
                return MSP_RESULT_ERROR;
            } else {
#if defined(USE_OSD)
                const uint16_t value = sbufReadU16(src);

                /* Get screen index, 0 is post flight statistics, 1 and above are in flight OSD screens */
                const uint8_t screen = (sbufBytesRemaining(src) >= 1) ? sbufReadU8(src) : 1;

                if (screen == 0 && addr < OSD_STAT_COUNT) {
                    /* Set statistic item enable */
                    osdStatSetState(addr, (value != 0));
                } else if (addr < OSD_ITEM_COUNT) {
                    /* Set element positions */
                    osdConfigMutable()->item_pos[addr] = value;
                    osdAnalyzeActiveElements();
                } else {
                  return MSP_RESULT_ERROR;
                }
#else
                return MSP_RESULT_ERROR;
#endif
            }
        }
        break;

    case MSP_OSD_CHAR_WRITE:
#ifdef USE_MAX7456
        {
            uint8_t font_data[64];
            const uint8_t addr = sbufReadU8(src);
            for (int i = 0; i < 54; i++) {
                font_data[i] = sbufReadU8(src);
            }
            // !!TODO - replace this with a device independent implementation
            max7456WriteNvm(addr, font_data);
        }
        break;
#else
        return MSP_RESULT_ERROR;
#endif
#endif // OSD

    default:
        return mspProcessInCommand(cmdMSP, src);
    }
    return MSP_RESULT_ACK;
}

/*
 * Returns MSP_RESULT_ACK, MSP_RESULT_ERROR or MSP_RESULT_NO_REPLY
 */
mspResult_e mspFcProcessCommand(mspPacket_t *cmd, mspPacket_t *reply, mspPostProcessFnPtr *mspPostProcessFn)
{
    int ret = MSP_RESULT_ACK;
    sbuf_t *dst = &reply->buf;
    sbuf_t *src = &cmd->buf;
    const uint8_t cmdMSP = cmd->cmd;
    // initialize reply by default
    reply->cmd = cmd->cmd;

    if (mspCommonProcessOutCommand(cmdMSP, dst, mspPostProcessFn)) {
        ret = MSP_RESULT_ACK;
    } else if (mspProcessOutCommand(cmdMSP, dst)) {
        ret = MSP_RESULT_ACK;
    } else if ((ret = mspFcProcessOutCommandWithArg(cmdMSP, src, dst, mspPostProcessFn)) != MSP_RESULT_CMD_UNKNOWN) {
        /* ret */;
#ifdef USE_SERIAL_4WAY_BLHELI_INTERFACE
    } else if (cmdMSP == MSP_SET_4WAY_IF) {
        mspFc4waySerialCommand(dst, src, mspPostProcessFn);
        ret = MSP_RESULT_ACK;
#endif
#ifdef USE_FLASHFS
    } else if (cmdMSP == MSP_DATAFLASH_READ) {
        mspFcDataFlashReadCommand(dst, src);
        ret = MSP_RESULT_ACK;
#endif
    } else {
        ret = mspCommonProcessInCommand(cmdMSP, src, mspPostProcessFn);
    }
    reply->result = ret;
    return ret;
}

void mspFcProcessReply(mspPacket_t *reply)
{
    sbuf_t *src = &reply->buf;
    UNUSED(src); // potentially unused depending on compile options.

    switch (reply->cmd) {
    case MSP_ANALOG:
        {
            uint8_t batteryVoltage = sbufReadU8(src);
            uint16_t mAhDrawn = sbufReadU16(src);
            uint16_t rssi = sbufReadU16(src);
            uint16_t amperage = sbufReadU16(src);

            UNUSED(rssi);
            UNUSED(batteryVoltage);
            UNUSED(amperage);
            UNUSED(mAhDrawn);

#ifdef USE_MSP_CURRENT_METER
            currentMeterMSPSet(amperage, mAhDrawn);
#endif
        }
        break;
    }
}

void mspInit(void)
{
    initActiveBoxIds();
}
