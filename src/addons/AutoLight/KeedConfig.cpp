/*
 *  KeedConfig.cpp
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#include "KeedConfig.h"

KeedConfiguration::KeedConfiguration()
        : version_num(0), channel_num(0), _success(nullptr) {}

cfg_error_t KeedConfiguration::initialize(void (*success)(void)) {
    for (int i = 0; i < ADDRESS_CONFIG_PIN_NUM; i++) {
        pinMode(version_address_pin_t[i], INPUT_PULLUP);
    }
    if (success != nullptr) success();
    return INITIALIZE_OK;
}

cfg_error_t KeedConfiguration::readChannel() {
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

cfg_error_t KeedConfiguration::readVersion() {
    if ((channel_num >= 0x00002 && channel_num <= 0x00010) || (channel_num >= 0x00012 && channel_num <= 0x00018) || (channel_num >= 0x0001A && channel_num <= 0x00040)) {
        version_num = (channel_num >= 0x00002 && channel_num <= 0x00010) ? MINSYS_V1 : (channel_num >= 0x00012 && channel_num <= 0x00018) ? MINSYS_V2 : MINSYS_V3;
        return SYSTEM_VERSION_OK;
    }
    return SYSTEM_VERSION_ERROR;
}

uint8_t KeedConfiguration::getVersion() const {
    return version_num;
}

uint8_t KeedConfiguration::getChannel() const {
    return channel_num;
}

uint8_t KeedConfiguration::getVersionInfo() const {
    return (version_num == MINSYS_V1)
           ? 1 : (version_num == MINSYS_V2)
                 ? 2 : (version_num == MINSYS_V3)
                       ? 3 : 0;
}

uint8_t KeedConfiguration::getIoExpanderNum() const {
    uint8_t io_expander_num = 0;
    for (int i = 0; i <= 64; i += 8) {
        if (channel_num > i && !(channel_num % 2)) {
            io_expander_num++;
        }
    }
    return io_expander_num;
}