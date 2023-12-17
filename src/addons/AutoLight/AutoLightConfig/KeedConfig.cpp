/*
 *  KeedConfig.cpp
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#include "KeedConfig.h"

KeedConfiguration::KeedConfiguration(bool _debug)
        : debug(_debug) {
}

cfg_error_t KeedConfiguration::initialize(void (*init_callback)(void)) {
    if (init_callback != nullptr) init_callback();
    return INITIALIZE_OK;
}

cfg_error_t KeedConfiguration::readChannel() {
    if (debug) return CHANNEL_NUM_OK;
    if (isUsingExpander()) {
        for (int i = 0; i < ADDRESS_CONFIG_PIN_NUM; i++) {
            pinMode(version_address_pin_t[i], INPUT_PULLUP);
        }
        int bin_value = 0;
        for (int i = 0; i < ADDRESS_CONFIG_PIN_NUM; i++) {
            bin_value = (bin_value << 1) | digitalRead(version_address_pin_t[i]); // int bin_value = (value_pin[0] << 4) | (value_pin[1] << 3) | (value_pin[2] << 2) | (value_pin[3] << 1) | value_pin[4];
        }
        for (int i = 0; i < TOTAL_VERSION_NUM; i++) {
            if (bin_value == version_address_t[i]) {
                cfg.channel = version_channel_t[i];
            }
        }
        cfg.io_size = 0;
        for (int i = 0; i <= 64; i += 8) {
            if (cfg.channel > i && !(cfg.channel % 2)) {
                cfg.io_size++;
            }
        }
    } else {
        for (uint8_t i = 0; i < cfg.pin_size; i++) {
            pinMode(cfg.pin_ptr[i], OUTPUT);
            digitalWrite(cfg.pin_ptr[i], HIGH);
        }
    }
    if (cfg.channel == 0 && cfg.pin_ptr == nullptr) {
        return CHANNEL_NUM_ERROR;
    }
    return CHANNEL_NUM_OK;
}

cfg_error_t KeedConfiguration::readVersion() {
    if (debug) return SYSTEM_VERSION_OK;
    if (isUsingExpander()) {
        if ((cfg.channel >= 0x00002 && cfg.channel <= 0x00010)
            || (cfg.channel >= 0x00012 && cfg.channel <= 0x00018)
            || (cfg.channel >= 0x0001A && cfg.channel <= 0x00040)) {
            cfg.version = (cfg.channel >= 0x00002 && cfg.channel <= 0x00010)
                          ? MINSYS_V1 : (cfg.channel >= 0x00012 && cfg.channel <= 0x00018)
                                        ? MINSYS_V2 : MINSYS_V3;
            return SYSTEM_VERSION_OK;
        }
    } else {
        cfg.version = MINSYS_V1_EXT;
        return SYSTEM_VERSION_OK;
    }
    return SYSTEM_VERSION_ERROR;
}

void KeedConfiguration::setConfig(configuration_t _cfg) {
    cfg = _cfg;
}

bool KeedConfiguration::isUsingExpander() const {
    return cfg.pin_ptr == nullptr && cfg.pin_size == 0;
}

configuration_t KeedConfiguration::getConfig() const {
    return cfg;
}

void configuration_t::setPins(int size, ...) {
    va_list args;
    va_start(args, size);
    pin_size = size;
    pin_ptr = new uint8_t[size];
    for (int i = 0; i < size; i++) {
        pin_ptr[i] = static_cast<uint8_t>(va_arg(args, int));
    }
    va_end(args);
}

void configuration_t::setKey(const char *_key) {
    strncpy(key, _key, KEY_LEN);
    key[KEY_LEN] = '\0';
}