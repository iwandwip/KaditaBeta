/*
 *  ultrasonic-sens.cpp
 *
 *  ultrasonic sensor c
 *  Created on: 2023. 4. 3
 */

#include "ultrasonic-sens.h"
#include "Arduino.h"

UltrasonicSens::~UltrasonicSens() = default;

void UltrasonicSens::init() {

}

void UltrasonicSens::update() {
    if (millis() - sensorTimer >= 500) {
        sensorValue = (float) this->ping_cm();
    }
}

void UltrasonicSens::getValue(float *output) {
    *output = sensorValue;
}

float UltrasonicSens::getValueCm() const {
    return sensorValue;
}

float UltrasonicSens::getValueIn() {
    return (float) this->ping_in();
}

void UltrasonicSens::setPins(uint8_t _pin) {
    sensorPin = _pin;
}