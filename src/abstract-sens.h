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
#include "sensor-module.h"

class Abstract : public BaseSens {
private:
    float templateValue;
#if defined(EXTENDED_FUNCTION_VTABLE)
    uint32_t sensTimer[3];
#else
    uint32_t sensTimer[1];
#endif

    bool isCalibrate;
    uint8_t sensorPin;

    void (*thisCallbackFunc)() = nullptr;

public:
    Abstract();
    explicit Abstract(uint8_t _pin, bool enableCalibrate = false);
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
    float getValue(sens_ret_index_t c = SENS_RET_ACT_DATA) const;
    void setPins(uint8_t _pin);
};

#endif  // ABSTRACT_SENS_H