/*
 *  dht-sens.cpp
 *
 *  dht sensor c
 *  Created on: 2023. 4. 3
 */

#include "dht-sens.h"
#include "Arduino.h"

DHTSens::DHTSens()
        : sensorClass(nullptr),
          sensorValue{0.0, 0.0},
          sensorTimer(0),
          sensorPin(3),
          sensorType(DHT22) {
}

DHTSens::DHTSens(uint8_t _pin, uint8_t _type)
        : sensorClass(nullptr),
          sensorValue{0.0, 0.0},
          sensorTimer(0),
          sensorPin(_pin),
          sensorType(_type) {
}

DHTSens::~DHTSens() = default;

void DHTSens::init() {
    sensorClass = new DHT(sensorPin, sensorType);
    (*sensorClass).begin();
}

void DHTSens::update() {
    if (millis() - sensorTimer >= 500) {
        sensorValue[0] = (*sensorClass).readTemperature();
        sensorValue[1] = (*sensorClass).readHumidity();
        sensorTimer = millis();
    }
}

void DHTSens::getValue(float *output) {
    output[0] = sensorValue[0];
    output[1] = sensorValue[1];
}

float DHTSens::getValueTemperature() const {
    return sensorValue[0];
}

float DHTSens::getValueHumidity() const {
    return sensorValue[1];
}

void DHTSens::setPins(uint8_t _pin) {
    sensorPin = _pin;
}