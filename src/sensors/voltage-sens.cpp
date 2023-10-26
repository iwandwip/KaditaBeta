/*
 *  voltage-sens.cpp
 *
 *  voltage sensor c
 *  Created on: 2023. 4. 3
 */

#include "voltage-sens.h"
#include "Arduino.h"

VoltageSens::VoltageSens()
        : sensorValue(0.0),
          sensorPin(A0),
          sensorTimer(0),
          sensorRes1(30000.0),
          sensorRes2(7500.0),
          sensorRefVoltage(5.0),
          sensorResolution(1024.0) {
}

VoltageSens::VoltageSens(uint8_t _pin, float _res1, float _res2, float _ref_voltage, float _resolution)
        : sensorValue(0.0),
          sensorPin(_pin),
          sensorTimer(0),
          sensorRes1(_res1),
          sensorRes2(_res2),
          sensorRefVoltage(_ref_voltage),
          sensorResolution(_resolution) {
}

VoltageSens::~VoltageSens() = default;

void VoltageSens::init() {
    pinMode(sensorPin, INPUT);
}

void VoltageSens::update() {
    if (millis() - sensorTimer >= 500) {
        sensorValue = analogRead(sensorPin);
        sensorValue = (sensorValue * sensorRefVoltage) / sensorResolution;
        sensorValue = sensorValue / (sensorRes2 / (sensorRes1 + sensorRes2));
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