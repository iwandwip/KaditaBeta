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
#include "sensor-module.h"
#include "Adafruit_Sensor.h"
#include "DHT.h"

#define DHT_SENS_TEMPERATURE 0
#define DHT_SENS_HUMIDITY 1
#define DHT_SENS_NUM 2

class DHTSens : public BaseSens {
private:
    DHT *thisClass;
    float thisValue[DHT_SENS_NUM];
#if defined(EXTENDED_FUNCTION_VTABLE)
    uint32_t sensTimer[3];
#else
    uint32_t sensTimer[1];
#endif

    bool isCalibrate;
    uint8_t sensorPin;
    uint8_t type;
#if defined(EXTENDED_FUNCTION_VTABLE)
    void (*thisCallbackFunc)() = nullptr;
#endif

public:
    DHTSens();
    explicit DHTSens(uint8_t _pin, uint8_t _type, bool enableCalibrate = false);
    ~DHTSens();
    void init() override;
    void update() override;
#if defined(EXTENDED_FUNCTION_VTABLE)
    void debug() override;
    void calibrate() override;
#endif
    void getValue(float *output) override;
#if defined(EXTENDED_FUNCTION_VTABLE)
    void setCallBack(void (*callbackFunc)(void)) override;
    void count() override;
    void reset() override;
#endif
    float getValueTemperature() const;
    float getValueHumidity() const;
    void setPins(uint8_t _pin);
};

#endif  // DHT_SENS_H