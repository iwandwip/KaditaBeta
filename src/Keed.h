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

typedef enum {
    I2C_ADDRESS_ERROR = -1,
    VERSION_ADDRESS_ERROR = -2,
    CHANNEL_NUM_ERROR = -3,
    CONFIG_ERROR = -4,
} config_error_t;

typedef enum {
    // version 1.0
    I2CCOM_8N0 = 0x20,
    I2CCOM_8N1 = 0x21,
    // version 2.0
    I2CCOM_8N2 = 0x22,
    I2CCOM_8N3 = 0x23,
    // version 3.0
    I2CCOM_8N4 = 0x24,
    I2CCOM_8N5 = 0x25,
    I2CCOM_8N6 = 0x26,
    I2CCOM_8N7 = 0x27,
} i2c_address_t;

const uint8_t version_address_t[TOTAL_VERSION_NUM] =
        {
                // version 1.0
                0x1F, 0x1E, 0x1D, 0x1C, 0x1B, 0x1A, 0x19, 0x18,
                // version 2.0
                0x17, 0x16, 0x15, 0x14,
                // version 3.0
                0x13, 0x12, 0x11, 0x10, 0x0F, 0x0E, 0x0D, 0x0C, 0x0B, 0x0A, 0x09, 0x08, 0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00,
        };

const uint8_t version_channel_t[TOTAL_VERSION_NUM] =
        {
                // version 1.0
                0x02, 0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0E, 0x10,
                // version 2.0
                0x12, 0x14, 0x16, 0x18,
                // version 3.0
                0x1A, 0x1C, 0x1E, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2A, 0x2C, 0x2E, 0x30, 0x32, 0x34, 0x36, 0x38, 0x3A, 0x3C, 0x3E, 0x40,
        };


class KeedWelcomingLight {
private:
    uint8_t channel_num;
public:
    uint8_t getChannel();
};

#endif // KEED_H