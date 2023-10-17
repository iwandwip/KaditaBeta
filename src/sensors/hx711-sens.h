/*
 *  hx711-sens.h
 *
 *  hx711 sensor lib
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef HX711_SENS_H
#define HX711_SENS_H

#include "Arduino.h"
#include "base/sensor-module.h"
#include "HX711.h"

class HX711Sens : public BaseSens, public HX711 {
private:
    float thisValue;
    bool sleep;
#if defined(EXTENDED_FUNCTION_VTABLE)
    uint32_t sensTimer[3];
#else
    uint32_t sensTimer[2];
#endif
    uint8_t sensorDOUTPin;
    uint8_t sensorSCKPin;
#if defined(EXTENDED_FUNCTION_VTABLE)
    void (*thisCallbackFunc)() = nullptr;
#endif
    using HX711::HX711;

public:
    HX711Sens();
    explicit HX711Sens(uint8_t _sensorDOUTPin, uint8_t _sensorSCKPin);
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
    void setPins(uint8_t _sensorDOUTPin, uint8_t _sensorSCKPin);
};

#endif  // HX711_SENS_H