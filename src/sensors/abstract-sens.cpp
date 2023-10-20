/*
 *  abstract-sens.cpp
 *
 *  abstract sensor c
 *  Created on: 2023. 4. 3
 */

#include "abstract-sens.h"
#include "Arduino.h"

Abstract::Abstract()
        : sensorClass(nullptr),
          sensorValue(0.0),
          sensorPin(A0),
          sensorTimer(0),
          sensorCallbackFunc(nullptr) {
}

Abstract::Abstract(uint8_t _pin)
        : sensorClass(nullptr),
          sensorValue(0.0),
          sensorPin(_pin),
          sensorTimer(0),
          sensorCallbackFunc(nullptr) {
}

Abstract::~Abstract() = default;

void Abstract::init() {
    pinMode(sensorPin, INPUT);
}

void Abstract::update() {
    if (millis() - sensorTimer >= 500) {
        sensorValue = analogRead(sensorPin);
        sensorValue *= (5.0 / 1023.0);
        sensorTimer = millis();
    }
}

void Abstract::getValue(float *output) {
    *output = sensorValue;
}

float Abstract::getValueAbstract() const {
    return sensorValue;
}

void Abstract::setPins(uint8_t _pin) {
    sensorPin = _pin;
}