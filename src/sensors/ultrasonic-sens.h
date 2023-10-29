/*
 *  ultrasonic-sens.h
 *
 *  ultrasonic sensor lib
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef ULTRASONIC_SENS_H
#define ULTRASONIC_SENS_H

#include "Arduino.h"
#include "base/sensor-module.h"
#include "NewPing.h"

class UltrasonicSens : public BaseSens, public NewPing {
private:
    /*variables*/
    float sensorValue;
    uint8_t sensorPin;
    uint32_t sensorTimer;

    using NewPing::NewPing;

public:
    ~UltrasonicSens();
    void init() override;
    void update() override;
    void getValue(float *output) override;
    float getValueCm() const;
    float getValueIn();
    void setPins(uint8_t _pin);
};

#endif  // ULTRASONIC_SENS_H