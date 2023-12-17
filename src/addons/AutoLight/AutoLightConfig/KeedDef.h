/*
 *  KeedDef.h
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef KEED_DEF_H
#define KEED_DEF_H

#include "Arduino.h"
#include "KeedCustom.h"

#define TOTAL_VERSION_NUM 32
#define ADDRESS_CONFIG_PIN_NUM 5
#define IO_EXPANDER_ADDRESS_NUM 8
#define IO_EXPANDER_PIN_NUM 8

#define KEED_DEBUG_PRINT(X) Serial.print(X)
#define KEED_DEBUG_PRINTLN(X) Serial.println(X)
#define KEED_DEBUG_PRINTER(X)                       \
    Serial.print("[INFO] [");                       \
    Serial.print(random(10000000, 99999999), DEC);  \
    Serial.print(".");                              \
    Serial.print(random(10000000, 99999999), DEC);  \
    Serial.print("]: ");                            \
    Serial.println(X)

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
} cfg_error_t;

typedef enum {
    IO_EXPANDER_0,
    IO_EXPANDER_1,
    IO_EXPANDER_2,
    IO_EXPANDER_3,
    IO_EXPANDER_4,
    IO_EXPANDER_5,
    IO_EXPANDER_6,
    IO_EXPANDER_7,
    IO_EXPANDER_NUM
} io_expander_index_t;

typedef enum {
    MINSYS_V1 = 0x0009B, // version 1.0
    MINSYS_V2 = 0x000A6, // version 2.0
    MINSYS_V3 = 0x000B1, // version 3.0
    MINSYS_V1_EXT = 0x000BC, // version 1.0-ext-6
    MINSYS_V2_EXT = 0x000C7, // version 2.0-ext-8
} system_version_t;

typedef enum {
    // version 1.0
    I2CCOM_8N0 = 0x00020,
    I2CCOM_8N1 = 0x00024, // 0x00021
    // version 2.0
    I2CCOM_8N2 = 0x00022,
    I2CCOM_8N3 = 0x00023,
    // version 3.0
    I2CCOM_8N4 = 0x00024,
    I2CCOM_8N5 = 0x00025,
    I2CCOM_8N6 = 0x00026,
    I2CCOM_8N7 = 0x00027,
} i2c_address_t;

const uint8_t i2c_address_arr_t[IO_EXPANDER_ADDRESS_NUM] = {
        I2CCOM_8N0, I2CCOM_8N1, I2CCOM_8N2, I2CCOM_8N3,
        I2CCOM_8N4, I2CCOM_8N5, I2CCOM_8N6, I2CCOM_8N7
};

const uint8_t version_address_pin_t[ADDRESS_CONFIG_PIN_NUM] = {
        0x0001B, 0x0001A, 0x00019, 0x00021, 0x00020
};

const uint8_t version_address_t[TOTAL_VERSION_NUM] = {
        // version 1.0
        0x0001F, 0x0001E, 0x0001D, 0x0001C,
        0x0001B, 0x0001A, 0x00019, 0x00018,
        // version 2.0
        0x00017, 0x00016, 0x00015, 0x00014,
        0x00013, 0x00012, 0x00011, 0x00010,
        // version 3.0
        0x0000F, 0x0000E, 0x0000D, 0x0000C,
        0x0000B, 0x0000A, 0x00009, 0x00008,
        0x00007, 0x00006, 0x00005, 0x00004,
        0x00003, 0x00002, 0x00001, 0x00000,
};

const uint8_t version_channel_t[TOTAL_VERSION_NUM] = {
        // version 1.0
        0x00002, 0x00004, 0x00006, 0x00008,
        0x0000A, 0x0000C, 0x0000E, 0x00010,
        // version 2.0
        0x00012, 0x00014, 0x00016, 0x00018,
        0x0001A, 0x0001C, 0x0001E, 0x00020,
        // version 3.0
        0x00022, 0x00024, 0x00026, 0x00028,
        0x0002A, 0x0002C, 0x0002E, 0x00030,
        0x00032, 0x00034, 0x00036, 0x00038,
        0x0003A, 0x0003C, 0x0003E, 0x00040,
};

typedef enum {
    LED_RED = 14,
    LED_GREEN = 12,
    LED_BLUE = 13,
    BUZZER = 15,
    INDICATOR_NUM = 4
} indicator_pin_t;

const uint8_t indicator_pin_arr_t[INDICATOR_NUM]{
        LED_RED, LED_GREEN, LED_BLUE, BUZZER
};

#endif // KEED_DEF_H