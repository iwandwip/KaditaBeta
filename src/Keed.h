/*
 *  Keed.h
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef KEED_H
#define KEED_H

#include "Kadita.h"

#define TOTAL_VERSION_NUM 32
#define ADDRESS_CONFIG_PIN_NUM 5

typedef enum {
    I2C_ADDRESS_OK = 1,
    VERSION_ADDRESS_OK = 2,
    CHANNEL_NUM_OK = 3,
    CONFIG_OK = 4,
    SYSTEM_VERSION_OK = 5,
    INITIALIZE_OK = 6,

    I2C_ADDRESS_ERROR = 255,
    VERSION_ADDRESS_ERROR = 254,
    CHANNEL_NUM_ERROR = 253,
    CONFIG_ERROR = 252,
    SYSTEM_VERSION_ERROR = 251,
    INITIALIZE_ERROR = 250,
} config_error_t;

typedef enum {
    // version 1.0
    I2CCOM_8N0 = 0x00020,
    I2CCOM_8N1 = 0x00021,
    // version 2.0
    I2CCOM_8N2 = 0x00022,
    I2CCOM_8N3 = 0x00023,
    // version 3.0
    I2CCOM_8N4 = 0x00024,
    I2CCOM_8N5 = 0x00025,
    I2CCOM_8N6 = 0x00026,
    I2CCOM_8N7 = 0x00027,
} i2c_address_t;

typedef enum {
    MINSYS_V1 = 0x0009B, // version 1.0
    MINSYS_V2 = 0x000A6, // version 2.0
    MINSYS_V3 = 0x000B1, // version 3.0
} system_version_t;

const uint8_t version_address_pin_t[ADDRESS_CONFIG_PIN_NUM] = {0x0001B, 0x0001A, 0x00019, 0x00021, 0x00020};
const uint8_t version_address_t[TOTAL_VERSION_NUM] =
        {
                // version 1.0
                0x0001F, 0x0001E, 0x0001D, 0x0001C, 0x0001B, 0x0001A, 0x00019, 0x00018,
                // version 2.0
                0x00017, 0x00016, 0x00015, 0x00014,
                // version 3.0
                0x00013, 0x00012, 0x00011, 0x00010, 0x0000F, 0x0000E, 0x0000D, 0x0000C, 0x0000B, 0x0000A, 0x00009, 0x00008, 0x00007, 0x00006, 0x00005, 0x00004, 0x00003, 0x00002, 0x00001, 0x00000,
        };
const uint8_t version_channel_t[TOTAL_VERSION_NUM] =
        {
                // version 1.0
                0x00002, 0x00004, 0x00006, 0x00008, 0x0000A, 0x0000C, 0x0000E, 0x00010,
                // version 2.0
                0x00012, 0x00014, 0x00016, 0x00018,
                // version 3.0
                0x0001A, 0x0001C, 0x0001E, 0x00020, 0x00022, 0x00024, 0x00026, 0x00028, 0x0002A, 0x0002C, 0x0002E, 0x00030, 0x00032, 0x00034, 0x00036, 0x00038, 0x0003A, 0x0003C, 0x0003E, 0x00040,
        };


class KeedConfiguration {
private:
    uint8_t version_num;
    uint8_t channel_num;
public:
    config_error_t initialize();
    config_error_t readChannel();
    config_error_t readVersion(uint8_t ch);

    uint8_t getVersion() const {
        return version_num;
    }

    uint8_t getChannel() const {
        return channel_num;
    }
};

#endif // KEED_H