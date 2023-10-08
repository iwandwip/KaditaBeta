/*
 *  abstract-sens.cpp
 *
 *  abstract sensor c
 *  Created on: 2023. 4. 3
 */

#include "abstract-sens.h"
#include "Arduino.h"

#define SENSOR_FILTER_KF 8

Abstract::Abstract()
        : isCalibrate(false), sensorPin(A0) {
}

Abstract::Abstract(uint8_t __pin, bool enableCalibrate) {
    this->sensorPin = __pin;
    isCalibrate = enableCalibrate;
}

Abstract::~Abstract() {

}

void Abstract::init() {
    pinMode(sensorPin, INPUT);
}

void Abstract::update() {
    if (millis() - sensTimer[0] >= 500) {
        if (!isCalibrate) {
            templateValue = analogRead(sensorPin);
            templateValue = templateValue * (5.0 / 1023.0);
            templateValue = templateValue + (templateValue * SENSOR_FILTER_KF);
            templateValue /= SENSOR_FILTER_KF + 1;
        }
        sensTimer[0] = millis();
    }
}

#if defined(EXTENDED_FUNCTION_VTABLE)
void Abstract::debug() {
    if (millis() - sensTimer[1] >= 500) {
        if (isCalibrate) return;
        Serial.print("| templateValueRaw: ");
        Serial.print(templateValue);
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
    *output = templateValue;
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

float Abstract::getValue(sens_ret_index_t c) {
    if (!isCalibrate) return templateValue;
    return arrTemplateValue[c];
}

void Abstract::setPins(uint8_t __pin) {
    this->sensorPin = __pin;
}