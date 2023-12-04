/*
 *  KeedConfig.h
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef KEED_CONFIG_H
#define KEED_CONFIG_H

#include "Kadita.h"
#include "KeedDef.h"

struct configuration_t {
    uint8_t version = 0;
    uint8_t channel = 0;
    uint8_t io_size = 0;
    uint8_t *pin_ptr = nullptr;
    uint8_t pin_size = 0;
    void setPins(int size, ...);
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

#endif // KEED_CONFIG_H