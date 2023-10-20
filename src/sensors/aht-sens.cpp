/*
 *  aht-sens.cpp
 *
 *  aht sensor c
 *  Created on: 2023. 4. 3
 */

#include "aht-sens.h"
#include "Arduino.h"

AHTSens::AHTSens()
        : sensorClass(nullptr),
          sensorValue{0, 0},
          sensorPin(A0),
          sensorTimer(0) {
}

AHTSens::AHTSens(uint8_t _pin)
        : sensorClass(nullptr),
          sensorValue{0, 0},
          sensorPin(_pin),
          sensorTimer(0) {
}

AHTSens::~AHTSens() = default;

void AHTSens::init() {
    sensorClass = new Adafruit_AHTX0;
    if (!(*sensorClass).begin())
        while (true) {
            delay(10);
            break;
        }
}

void AHTSens::update() {
    if (millis() - sensorTimer >= 500) {
        sensors_event_t dataBuffer[2];
        (*sensorClass).getEvent(&dataBuffer[1], &dataBuffer[0]);
        sensorValue[0] = dataBuffer[0].temperature;
        sensorValue[1] = dataBuffer[1].relative_humidity;
        sensorTimer = millis();
    }
}

void AHTSens::getValue(float *output) {
    output[0] = sensorValue[0];
    output[1] = sensorValue[1];
}

float AHTSens::getValueTemperature() const {
    return sensorValue[0];
}

float AHTSens::getValueHumidity() const {
    return sensorValue[1];
}

void AHTSens::setPins(uint8_t _pin) {
    sensorPin = _pin;
}