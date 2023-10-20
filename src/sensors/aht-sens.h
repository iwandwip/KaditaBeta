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
    Adafruit_AHTX0 *sensorClass;
    float sensorValue[AHT_SENS_NUM];
    uint8_t sensorPin;
    uint32_t sensorTimer;

public:
    AHTSens();
    explicit AHTSens(uint8_t _pin);
    ~AHTSens();
    void init() override;
    void update() override;
    void getValue(float *output) override;
    float getValueTemperature() const;
    float getValueHumidity() const;
    void setPins(uint8_t _pin);
};

#endif  // AHT_SENS_H