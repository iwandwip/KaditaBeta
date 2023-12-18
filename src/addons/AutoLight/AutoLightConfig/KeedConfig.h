/*
 *  KeedConfig.h
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef KEED_CONFIG_H
#define KEED_CONFIG_H

#include "modules/communication/wired/i2c/io-expander.h"
#include "KeedDef.h"

#include "EEPROM.h"

struct configuration_t {
    uint8_t version = 0;
    uint8_t channel = 0;
    uint8_t io_size = 0;
    bool custom = false;
    bool reverse = false;
    uint8_t pin_size = 0;
    uint8_t *pin_ptr = nullptr;
    uint8_t *i2c_ptr = nullptr;
    void setPins(int size, ...);
    void setAddress(int size, ...);
};

class KeedConfiguration {
private:
    configuration_t cfg;
    bool debug;

public:
    explicit KeedConfiguration(bool _debug = false);
    cfg_error_t initialize(void (*init_callback)() = nullptr);
    cfg_error_t readChannel();
    cfg_error_t readVersion();

    void setConfig(configuration_t _cfg);
    bool isUsingExpander() const;
    configuration_t getConfig() const;
};

#if defined(ESP32)
#define readMEM(x) EEPROM.readString(x)
#define writeMEM(x, y) EEPROM.writeString(x, y)
#else
void writeMEM(int addrOffset, const String &strToWrite);
String readMEM(int addrOffset);
String memstr(const byte* byteArray, size_t size);
#endif

#endif // KEED_CONFIG_H