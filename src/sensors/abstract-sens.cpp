/*
 *  abstract-sens.cpp
 *
 *  abstract sensor c
 *  Created on: 2023. 4. 3
 */

#include "abstract-sens.h"
#include "Arduino.h"

Abstract::Abstract()
        : sensorPin(A0) {
}

Abstract::Abstract(uint8_t _pin) {
    this->sensorPin = _pin;
}

Abstract::~Abstract() = default;

void Abstract::init() {
    pinMode(sensorPin, INPUT);
}

void Abstract::update() {
    if (millis() - sensTimer[0] >= 500) {
        thisValue = analogRead(sensorPin);
        thisValue *= (5.0 / 1023.0);
        sensTimer[0] = millis();
    }
}

#if defined(EXTENDED_FUNCTION_VTABLE)
void Abstract::debug() {
    if (millis() - sensTimer[1] >= 500) {
        if (isCalibrate) return;
        Serial.print("| thisValueRaw: ");
        Serial.print(thisValue);
        Serial.println();
        sensTimer[1] = millis();
    }
}

void Abstract::calibrate() {
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

void Abstract::getValue(float *output) {
    *output = thisValue;
}

void Abstract::getValue(int *output) {
}

void Abstract::getValue(char *output) {
}

#if defined(EXTENDED_FUNCTION_VTABLE)
void Abstract::setCallBack(void (*callbackFunc)(void)) {
    thisCallbackFunc = callbackFunc;
}

void Abstract::count() {
}

void Abstract::reset() {
}
#endif

float Abstract::getValue() const {
    return thisValue;
}

void Abstract::setPins(uint8_t _pin) {
    this->sensorPin = _pin;
}