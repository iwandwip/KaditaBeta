/*
 *  abstract-sens.cpp
 *
 *  abstract sensor c
 *  Created on: 2023. 4. 3
 */

#include "abstract-sens.h"
#include "Arduino.h"

Abstract::Abstract()
        : sensValue(0.0),
          sensorPin(A0),
          sensTimer(0),
          sensCallbackFunc(nullptr) {
}

Abstract::Abstract(uint8_t _pin)
        : sensValue(0.0),
          sensTimer(0),
          sensCallbackFunc(nullptr) {
    this->sensorPin = _pin;
}

Abstract::~Abstract() = default;

void Abstract::init() {
    pinMode(sensorPin, INPUT);
}

void Abstract::update() {
    if (millis() - sensTimer >= 500) {
        sensValue = analogRead(sensorPin);
        sensValue *= (5.0 / 1023.0);
        sensTimer = millis();
    }
}

void Abstract::getValue(float *output) {
    *output = sensValue;
}

void Abstract::getValue(int *output) {
}

void Abstract::getValue(char *output) {
}

float Abstract::getValue() const {
    return sensValue;
}

void Abstract::setPins(uint8_t _pin) {
    this->sensorPin = _pin;
}