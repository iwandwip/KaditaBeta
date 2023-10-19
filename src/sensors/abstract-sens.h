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
#include "base/sensor-module.h"

class Abstract : public BaseSens {
private:
    float sensValue;
    uint8_t sensorPin;
    uint32_t sensTimer;
    void (*sensCallbackFunc)();

public:
    Abstract();
    explicit Abstract(uint8_t _pin);
    ~Abstract();
    void init() override;
    void update() override;
    void getValue(float *output) override;
    void getValue(int *output) override;
    void getValue(char *output) override;
    float getValue() const;
    void setPins(uint8_t _pin);
};

#endif  // ABSTRACT_SENS_H