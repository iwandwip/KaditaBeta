/*
 *  voltage-sens.h
 *
 *  voltage sensor lib
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef VOLTAGE_SENS_H
#define VOLTAGE_SENS_H

#include "Arduino.h"
#include "base/sensor-module.h"

class VoltageSens : public BaseSens {
private:
    /*variables*/
    float sensorValue;
    uint8_t sensorPin;
    uint32_t sensorTimer;

    float sensorRes1;
    float sensorRes2;
    float sensorRefVoltage;
    float sensorResolution;

public:
    VoltageSens();
    explicit VoltageSens(uint8_t _pin, float _res1 = 30000.0, float _res2 = 7500.0, float _ref_voltage = 5.0, float _resolution = 1024.0);
    ~VoltageSens();
    void init() override;
    void update() override;
    void getValue(float *output) override;
    float getValueVoltage() const;
    void setPins(uint8_t _pin);
};

#endif  // VOLTAGE_SENS_H