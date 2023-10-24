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
    void *sensorClass;
    float sensorValue;
    uint8_t sensorPin;
    uint32_t sensorTimer;

    /*optional object*/
    void (*sensorCallbackFunc)();

public:
    VoltageSens();
    explicit VoltageSens(uint8_t _pin);
    ~VoltageSens();
    void init() override;
    void update() override;
    void getValue(float *output) override;
    float getValueVoltage() const;
    void setPins(uint8_t _pin);
};

#endif  // VOLTAGE_SENS_H