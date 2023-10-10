/*
 *  ldr-sens.h
 *
 *  ldr sensor lib
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef LDR_SENS_H
#define LDR_SENS_H

#include "Arduino.h"
#include "base/sensor-module.h"

class LDRSens : public BaseSens {
private:
    float thisValue;
#if defined(EXTENDED_FUNCTION_VTABLE)
    uint32_t sensTimer[3];
#else
    uint32_t sensTimer[1];
#endif
    uint8_t sensorPin;
    uint8_t vref;
    uint8_t resolution;
#if defined(EXTENDED_FUNCTION_VTABLE)
    void (*thisCallbackFunc)() = nullptr;
#endif

public:
    LDRSens();
    explicit LDRSens(uint8_t _pin, uint8_t _vref = 5, uint8_t _resolution = 10);
    ~LDRSens();
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

#endif  // LDR_SENS_H