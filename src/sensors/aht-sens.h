/*
 *  aht-sens.h
 *
 *  aht sensor lib
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef AHT_SENS_H
#define AHT_SENS_H

#include "Arduino.h"
#include "base/sensor-module.h"
#include "Adafruit_Sensor.h"
#include "Adafruit_AHTX0.h"

#define AHT_SENS_TEMPERATURE 0
#define AHT_SENS_HUMIDITY 1
#define AHT_SENS_NUM 2

class AHTSens : public BaseSens {
private:
    Adafruit_AHTX0 *thisClass;
    float thisValue[AHT_SENS_NUM];
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
    AHTSens();
    explicit AHTSens(uint8_t _pin);
    ~AHTSens();
    void init() override;
    void update() override;
#if defined(EXTENDED_FUNCTION_VTABLE)
    void debug() override;
    void calibrate() override;
#endif
    void getValue(float *output) override;
#if defined(EXTENDED_FUNCTION_VTABLE)
    void setCallBack(void (*callbackFunc)(void)) override;
    void count() override;
    void reset() override;
#endif
    float getValueTemperature() const;
    float getValueHumidity() const;
    void setPins(uint8_t _pin);
};

#endif  // AHT_SENS_H