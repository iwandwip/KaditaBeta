/*
 *  Keed.cpp
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#include "Keed.h"

config_error_t KeedConfiguration::initialize() {
    for (int i = 0; i < ADDRESS_CONFIG_PIN_NUM; i++) {
        pinMode(version_address_pin_t[i], INPUT_PULLUP);
    }
    return INITIALIZE_OK;
}

config_error_t KeedConfiguration::readChannel() {
    // int bin_value = (value_pin[0] << 4) | (value_pin[1] << 3) | (value_pin[2] << 2) | (value_pin[3] << 1) | value_pin[4];
    int bin_value = 0;
    for (int i = 0; i < ADDRESS_CONFIG_PIN_NUM; i++) {
        bin_value = (bin_value << 1) | digitalRead(version_address_pin_t[i]);
    }
    for (int i = 0; i < TOTAL_VERSION_NUM; i++) {
        if (bin_value == version_address_t[i]) {
            channel_num = version_channel_t[i];
            return CHANNEL_NUM_OK;
        }
    }
    return CHANNEL_NUM_ERROR;
}

config_error_t KeedConfiguration::readVersion(uint8_t ch) {
    if ((ch >= 0x00002 && ch <= 0x00010) || (ch >= 0x00012 && ch <= 0x00018) || (ch >= 0x0001A && ch <= 0x00040)) {
        if (ch >= 0x00002 && ch <= 0x00010) {
            version_num = MINSYS_V1;
        } else if (ch >= 0x00012 && ch <= 0x00018) {
            version_num = MINSYS_V2;
        } else {
            version_num = MINSYS_V3;
        }
        return SYSTEM_VERSION_OK;
    }
    return SYSTEM_VERSION_ERROR;
}