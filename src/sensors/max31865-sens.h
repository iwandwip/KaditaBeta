/*
 *  max31865-sens.h
 *
 *  max31865 sensor lib
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef MAX31865_SENS_H
#define MAX31865_SENS_H

#include "Arduino.h"
#include "base/sensor-module.h"
#include "Adafruit_MAX31865.h"

class MAX31865Sens : public BaseSens, public Adafruit_MAX31865 {
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
    using Adafruit_MAX31865::Adafruit_MAX31865;

public:
//    MAX31865Sens();
//    explicit MAX31865Sens(uint8_t _pin);
    ~MAX31865Sens();
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

#endif  // MAX31865_SENS_H