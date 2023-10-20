/*
 *  ldr-sens.cpp
 *
 *  ldr sensor c
 *  Created on: 2023. 4. 3
 */

#include "ldr-sens.h"
#include "Arduino.h"

LDRSens::LDRSens()
        : sensorValue(0),
          sensorTimer(0),
          sensorPin(A0),
          sensorVRef(5),
          sensorResolution(10) {
}

LDRSens::LDRSens(uint8_t _pin, uint8_t _vref, uint8_t _resolution)
        : sensorValue(0),
          sensorTimer(0),
          sensorPin(_pin),
          sensorVRef(_vref),
          sensorResolution(_resolution) {
}

LDRSens::~LDRSens() = default;

void LDRSens::init() {
    pinMode(sensorPin, INPUT);
}

void LDRSens::update() {
    if (millis() - sensorTimer >= 500) {
        sensorValue = analogRead(sensorPin);
//        sensorValue *= (float) (sensorVRef / (pow(2, sensorResolution) - 1)); // toVolt
        sensorTimer = millis();
    }
}

void LDRSens::getValue(float *output) {
    *output = sensorValue;
}

float LDRSens::getValueAdc() const {
    return sensorValue;
}

void LDRSens::setPins(uint8_t _pin) {
    this->sensorPin = _pin;
}