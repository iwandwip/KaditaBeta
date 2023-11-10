/*
 *  ina219-sens.h
 *
 *  ina219 sensor lib
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef INA219_SENS_H
#define INA219_SENS_H

#include "Arduino.h"
#include "base/sensor-module.h"
#include "Adafruit_INA219.h"

#define INA219_SHUNT_VOLTAGE_MV 0
#define INA219_BUS_VOLTAGE_V 1
#define INA219_CURRENT_MA 2
#define INA219_POWER_MW 3
#define INA219_VALUE_NUM 4

class INA219Sens : public BaseSens, Adafruit_INA219 {
private:
    /*variables*/
    float sensorValue[INA219_VALUE_NUM];
    uint8_t sensorAddr;
    uint32_t sensorTimer;
    using Adafruit_INA219::Adafruit_INA219;

public:
    explicit INA219Sens(uint8_t addr = INA219_ADDRESS);
    ~INA219Sens();
    void init() override;
    void update() override;
    void getValue(float *output) override;
    float getValueShuntVoltage_mV() const;
    float getValueBusVoltage_V() const;
    float getValueCurrent_mA() const;
    float getValuePower_mW() const;
    void setPins(uint8_t _pin);
};

#endif  // INA219_SENS_H