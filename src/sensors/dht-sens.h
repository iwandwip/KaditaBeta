/*
 *  dht-sens.h
 *
 *  dht sensor lib
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef DHT_SENS_H
#define DHT_SENS_H

#include "Arduino.h"
#include "base/sensor-module.h"
#include "Adafruit_Sensor.h"
#include "DHT.h"

#define DHT_SENS_TEMPERATURE 0
#define DHT_SENS_HUMIDITY 1
#define DHT_SENS_NUM 2

class DHTSens : public BaseSens {
private:
    DHT *sensorClass;
    float sensorValue[DHT_SENS_NUM];
    uint32_t sensorTimer;
    uint8_t sensorPin;
    uint8_t sensorType;

public:
    DHTSens();
    explicit DHTSens(uint8_t _pin, uint8_t _type);
    ~DHTSens();
    void init() override;
    void update() override;
    void getValue(float *output) override;
    float getValueTemperature() const;
    float getValueHumidity() const;
    void setPins(uint8_t _pin);
};

#endif  // DHT_SENS_H