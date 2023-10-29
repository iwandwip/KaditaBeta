/*
 *  max6675-sens.cpp
 *
 *  max6675 sensor c
 *  Created on: 2023. 4. 3
 */

#include "max6675-sens.h"
#include "Arduino.h"

MAX6675Sens::~MAX6675Sens() = default;

void MAX6675Sens::init() {

}

void MAX6675Sens::update() {
    if (millis() - sensorTimer >= 500) {
        sensorValue = (float) this->readCelsius();
    }
}

void MAX6675Sens::getValue(float *output) {
    *output = sensorValue;
}

float MAX6675Sens::getValueTemperature() const {
    return sensorValue;
}

void MAX6675Sens::setPins(uint8_t _pin) {
    sensorPin = _pin;
}