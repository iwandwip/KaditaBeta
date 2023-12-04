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

class KeedConfiguration {
private:
    uint8_t version_num;
    uint8_t channel_num;
    uint8_t *pin_ptr;
    void (*_success)();

public:
    explicit KeedConfiguration(uint8_t *_pin = nullptr);
    cfg_error_t initialize(void (*success)() = nullptr);
    cfg_error_t readChannel();
    cfg_error_t readVersion();

    uint8_t getVersion() const;
    uint8_t getChannel() const;
    uint8_t getVersionInfo() const;
    uint8_t getIoExpanderNum() const;
    uint8_t* getPins() const;
    bool isUsingExpander() const;
};

#endif // KEED_CONFIG_H