/*
 *  dht-sens.cpp
 *
 *  dht sensor c
 *  Created on: 2023. 4. 3
 */

#include "dht-sens.h"
#include "Arduino.h"

DHTSens::DHTSens()
        : sensorPin(A0) {
}

DHTSens::DHTSens(uint8_t _pin, uint8_t _type) {
    this->sensorPin = _pin;
    this->type = _type;
}

DHTSens::~DHTSens() = default;

void DHTSens::init() {
    thisClass = new DHT(sensorPin, type);
    (*thisClass).begin();
}

void DHTSens::update() {
    if (millis() - sensTimer[0] >= 500) {
        thisValue[0] = (*thisClass).readTemperature();
        thisValue[1] = (*thisClass).readHumidity();
        sensTimer[0] = millis();
    }
}

#if defined(EXTENDED_FUNCTION_VTABLE)
void DHTSens::debug() {
    if (millis() - sensTimer[1] >= 500) {
        if (isCalibrate) return;
        Serial.print("| thisValueRaw: ");
        Serial.print(sensValue);
        Serial.println();
        sensTimer[1] = millis();
    }
}

void DHTSens::calibrate() {
    if (millis() - sensTimer[2] >= 500) {
        if (!isCalibrate) return;
        Serial.print("| arrTemplateValueRaw: ");
        Serial.print(arrTemplateValue[SENS_RET_RAW_DATA]);
        Serial.print("| arrTemplateValueAct: ");
        Serial.print(arrTemplateValue[SENS_RET_ACT_DATA]);
        Serial.print("| arrTemplateValueAvg: ");
        Serial.print(arrTemplateValue[SENS_RET_AVG_DATA]);
        Serial.print("| arrTemplateValueFiltered: ");
        Serial.print(arrTemplateValue[SENS_RET_FILTERED_DATA]);
        Serial.println();
        sensTimer[2] = millis();
    }
}
#endif

void DHTSens::getValue(float *output) {
    output[0] = thisValue[0];
    output[1] = thisValue[1];
}

#if defined(EXTENDED_FUNCTION_VTABLE)
void DHTSens::setCallBack(void (*callbackFunc)(void)) {
    thisCallbackFunc = callbackFunc;
}

void DHTSens::count() {
}

void DHTSens::reset() {
}
#endif

float DHTSens::getValueTemperature() const {
    return thisValue[0];
}

float DHTSens::getValueHumidity() const {
    return thisValue[1];
}

void DHTSens::setPins(uint8_t _pin) {
    this->sensorPin = _pin;
}