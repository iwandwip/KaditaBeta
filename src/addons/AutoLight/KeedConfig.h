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

typedef struct {
    uint8_t version;
    uint8_t channel;
    uint8_t io_size;
    uint8_t *pin_ptr;
    uint8_t pin_size;
} configuration_t;

class KeedConfiguration {
private:
    configuration_t cfg;

public:
    explicit KeedConfiguration();
    cfg_error_t initialize(void (*success_cb)() = nullptr);
    cfg_error_t readChannel();
    cfg_error_t readVersion();

    void setConfig(configuration_t _cfg);
    bool isUsingExpander() const;
    configuration_t getConfig() const;
};

#endif // KEED_CONFIG_H