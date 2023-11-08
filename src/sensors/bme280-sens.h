/*
 *  bme280-sens.h
 *
 *  bme280 sensor lib
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef BME280_SENS_H
#define BME280_SENS_H

#include "Arduino.h"
#include "base/sensor-module.h"
#include "Adafruit_BME280.h"

#define BME_SENS_TEMPERATURE 0
#define BME_SENS_PRESSURE 1
#define BME_SENS_ALTITUDE 2
#define BME_SENS_HUMIDITY 3
#define BME_SENS_VALUE_NUM 4

#define SEALEVELPRESSURE_HPA (1013.25)

class BME280Sens : public BaseSens, public Adafruit_BME280 {
private:
    /*variables*/
    float sensorValue[BME_SENS_VALUE_NUM];
    uint32_t sensorTimer;
    using Adafruit_BME280::Adafruit_BME280;

public:
    explicit BME280Sens();
    explicit BME280Sens(int8_t _cs);
    explicit BME280Sens(int8_t _cs, int8_t _mosi, int8_t _miso, int8_t _sck);
    ~BME280Sens();
    void init() override;
    void update() override;
    void getValue(float *output) override;
    float getValueTemperature() const;
    float getValuePressure() const;
    float getValueAltitude() const;
    float getValueHumidity() const;
    void setPins(uint8_t _pin);
};

#endif  // BME280_SENS_H