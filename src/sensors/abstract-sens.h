/*
 *  abstract-sens.h
 *
 *  abstract sensor lib
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef ABSTRACT_SENS_H
#define ABSTRACT_SENS_H

#include "Arduino.h"
#include "base/sensor-module.h"

class Abstract : public BaseSens {
private:
    float thisValue;
#if defined(EXTENDED_FUNCTION_VTABLE)
    uint32_t sensTimer[3];
#else
    uint32_t sensTimer[1];
#endif
    uint8_t sensorPin;
#if defined(EXTENDED_FUNCTION_VTABLE)
    void (*thisCallbackFunc)() = nullptr;
#endif

public:
    Abstract();
    explicit Abstract(uint8_t _pin);
    ~Abstract();
    void init() override;
    void update() override;
#if defined(EXTENDED_FUNCTION_VTABLE)
    void debug() override;
    void calibrate() override;
#endif
    void getValue(float *output) override;
    void getValue(int *output) override;
    void getValue(char *output) override;
#if defined(EXTENDED_FUNCTION_VTABLE)
    void setCallBack(void (*callbackFunc)(void)) override;
    void count() override;
    void reset() override;
#endif
    float getValue() const;
    void setPins(uint8_t _pin);
};

#endif  // ABSTRACT_SENS_H