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
    float sensorValue;
    uint32_t sensorTimer;
    uint8_t sensorPin;
    uint8_t sensorVRef;
    uint8_t sensorResolution;

public:
    LDRSens();
    explicit LDRSens(uint8_t _pin, uint8_t _vref = 5, uint8_t _resolution = 10);
    ~LDRSens();
    void init() override;
    void update() override;
    void getValue(float *output) override;
    float getValueAdc() const;
    void setPins(uint8_t _pin);
};

#endif  // LDR_SENS_H