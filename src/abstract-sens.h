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
#include "sensor-module.h"
#include "stdint.h"

class Abstract : public BaseSens {
private:
    float arrTemplateValue[6];
    float templateValue;
    uint32_t sensTimer[3];

    bool isCalibrate;
    uint8_t sensorPin;

    void (*thisCallbackFunc)(void) = nullptr;

public:
    Abstract();
    Abstract(uint8_t __pin, bool enableCalibrate = false);
    ~Abstract();
    void init() override;
    void update() override;
    void debug() override;
    void calibrate() override;
    void getValue(float *output) override;
    void getValue(int *output) override;
    void getValue(char *output) override;
    void setCallBack(void (*callbackFunc)(void)) override;
    void count() override;
    void reset() override;
    float getValue(sens_ret_index_t c = SENS_RET_ACT_DATA);
    void setPins(uint8_t __pin);
};

#endif  // ABSTRACT_SENS_H