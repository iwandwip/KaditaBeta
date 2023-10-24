/*
 *  ds18b20-sens.h
 *
 *  ds18b20 sensor lib
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef DS18B20_SENS_H
#define DS18B20_SENS_H

#include "Arduino.h"
#include "base/sensor-module.h"
#include "DallasTemperature.h"

class DS18B20Sens : public BaseSens, public DallasTemperature {
private:
    /*variables*/
    float sensorValue;
    uint8_t sensorPin;
    uint32_t sensorTimer;

    /*optional object*/
    using DallasTemperature::DallasTemperature;

public:
    DS18B20Sens();
    explicit DS18B20Sens(uint8_t _pin);
    explicit DS18B20Sens(OneWire* _wire);
    ~DS18B20Sens();
    void init() override;
    void update() override;
    void getValue(float *output) override;
    float getValueTemperature() const;
    void setPins(uint8_t _pin);
};

#endif  // DS18B20_SENS_H