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
    pinMode(sensorPin, INPUT);
}

void MAX31865Sens::update() {
    if (millis() - sensTimer[0] >= 500) {
        thisValue = analogRead(sensorPin);
        thisValue *= (5.0 / 1023.0);
        sensTimer[0] = millis();
    }
}

#if defined(EXTENDED_FUNCTION_VTABLE)
void MAX31865Sens::debug() {
    if (millis() - sensTimer[1] >= 500) {
        if (isCalibrate) return;
        Serial.print("| thisValueRaw: ");
        Serial.print(thisValue);
        Serial.println();
        sensTimer[1] = millis();
    }
}

void MAX31865Sens::calibrate() {
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

void MAX31865Sens::getValue(float *output) {
    *output = thisValue;
}

void MAX31865Sens::getValue(int *output) {
}

void MAX31865Sens::getValue(char *output) {
}

#if defined(EXTENDED_FUNCTION_VTABLE)
void MAX31865Sens::setCallBack(void (*callbackFunc)(void)) {
    thisCallbackFunc = callbackFunc;
}

void MAX31865Sens::count() {
}

void MAX31865Sens::reset() {
}
#endif

float MAX31865Sens::getValue() const {
    return thisValue;
}

void MAX31865Sens::setPins(uint8_t _pin) {
    this->sensorPin = _pin;
}