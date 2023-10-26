/*
 *  ds18b20-sens.cpp
 *
 *  ds18b20 sensor c
 *  Created on: 2023. 4. 3
 */

#include "ds18b20-sens.h"
#include "Arduino.h"

DS18B20Sens::DS18B20Sens()
        : sensorValue(0.0),
          sensorPin(2),
          sensorTimer(0) {
}

DS18B20Sens::DS18B20Sens(uint8_t _pin)
        : DallasTemperature(new OneWire(_pin)),
          sensorValue(0.0),
          sensorPin(_pin),
          sensorTimer(0) {
}

DS18B20Sens::DS18B20Sens(OneWire *_wire)
        : DallasTemperature(_wire),
          sensorValue(0.0),
          sensorPin(2),
          sensorTimer(0) {
}

DS18B20Sens::~DS18B20Sens() = default;

void DS18B20Sens::init() {
    DallasTemperature::begin();
}

void DS18B20Sens::update() {
    if (millis() - sensorTimer >= 3000) {
        sensorValue = DallasTemperature::getTempCByIndex(0);
        sensorTimer = millis();
    }
}

void DS18B20Sens::getValue(float *output) {
    *output = sensorValue;
}

float DS18B20Sens::getValueTemperature() const {
    return sensorValue;
}

void DS18B20Sens::setPins(uint8_t _pin) {
    sensorPin = _pin;
}