/*
 *  KeedBase.h
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef KEED_BASE_H
#define KEED_BASE_H

#include "KeedConfig.h"

struct interrupt_t {
    uint8_t pin = 0;
    volatile uint32_t num = 0;
    volatile bool pressed = false;
    void (*isrCallback)() = nullptr;

    void attachInterrupt(uint8_t _pin, void (*_callback)()) {
        pin = _pin;
        isrCallback = _callback;
    }
};

class KeedBase {
public:
    // pure virtual function
    virtual void init() = 0;
    virtual void update() = 0;
    virtual void run(IOExpander **ioBase, uint8_t ioNum, configuration_t _cfg) = 0;

    virtual void setInterruptConfig(interrupt_t _cfg) {
        /*not implemented yet*/
    }

    virtual void changeModes() {
        /*not implemented yet*/
    }

    virtual void setBaseDelay(uint32_t _time) {
        /*not implemented yet*/
    }

    KeedBase &operator=(const KeedBase &) = default;
    KeedBase &operator=(KeedBase &&) = default;
};

#endif // KEED_BASE_H