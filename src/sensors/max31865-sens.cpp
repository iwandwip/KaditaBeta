/*
 *  max31865-sens.cpp
 *
 *  max31865 sensor c
 *  Created on: 2023. 4. 3
 */

#include "max31865-sens.h"
#include "Arduino.h"

MAX31865Sens::~MAX31865Sens() = default;

void MAX31865Sens::init() {

}

void MAX31865Sens::update() {
    if (millis() - sensTimer >= 500) {
        sensValue = this->temperature(rtdNominal, refResistor);
        sensTimer = millis();
    }
}

void MAX31865Sens::getValue(float *output) {
    *output = sensValue;
}

float MAX31865Sens::getValueTemperature() const {
    return sensValue;
}

void MAX31865Sens::setPins(uint8_t _pin) {

}