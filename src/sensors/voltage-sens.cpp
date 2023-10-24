/*
 *  voltage-sens.cpp
 *
 *  voltage sensor c
 *  Created on: 2023. 4. 3
 */

#include "voltage-sens.h"
#include "Arduino.h"

VoltageSens::VoltageSens()
        : sensorClass(nullptr),
          sensorValue(0.0),
          sensorPin(A0),
          sensorTimer(0),
          sensorCallbackFunc(nullptr) {
}

VoltageSens::VoltageSens(uint8_t _pin)
        : sensorClass(nullptr),
          sensorValue(0.0),
          sensorPin(_pin),
          sensorTimer(0),
          sensorCallbackFunc(nullptr) {
}

VoltageSens::~VoltageSens() = default;

void VoltageSens::init() {
    pinMode(sensorPin, INPUT);
}

void VoltageSens::update() {
    if (millis() - sensorTimer >= 500) {
        sensorValue = analogRead(sensorPin);
        sensorValue *= (5.0 / 1023.0);
        sensorTimer = millis();
    }
}

void VoltageSens::getValue(float *output) {
    *output = sensorValue;
}

float VoltageSens::getValueVoltage() const {
    return sensorValue;
}

void VoltageSens::setPins(uint8_t _pin) {
    sensorPin = _pin;
}