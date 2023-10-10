/*
 *  ldr-sens.cpp
 *
 *  ldr sensor c
 *  Created on: 2023. 4. 3
 */

#include "ldr-sens.h"
#include "Arduino.h"

LDRSens::LDRSens()
        : sensorPin(A0), vref(5), resolution(10) {
}

LDRSens::LDRSens(uint8_t _pin, uint8_t _vref, uint8_t _resolution) {
    this->sensorPin = _pin;
    this->vref = _vref;
    this->resolution = _resolution;
}

LDRSens::~LDRSens() = default;

void LDRSens::init() {
    pinMode(sensorPin, INPUT);
}

void LDRSens::update() {
    if (millis() - sensTimer[0] >= 500) {
        thisValue = analogRead(sensorPin);
        thisValue *= (vref / (pow(2, resolution) - 1));
        sensTimer[0] = millis();
    }
}

#if defined(EXTENDED_FUNCTION_VTABLE)
void LDRSens::debug() {
    if (millis() - sensTimer[1] >= 500) {
        if (isCalibrate) return;
        Serial.print("| thisValueRaw: ");
        Serial.print(thisValue);
        Serial.println();
        sensTimer[1] = millis();
    }
}

void LDRSens::calibrate() {
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

void LDRSens::getValue(float *output) {
    *output = thisValue;
}

void LDRSens::getValue(int *output) {
}

void LDRSens::getValue(char *output) {
}

#if defined(EXTENDED_FUNCTION_VTABLE)
void LDRSens::setCallBack(void (*callbackFunc)(void)) {
    thisCallbackFunc = callbackFunc;
}

void LDRSens::count() {
}

void LDRSens::reset() {
}
#endif

float LDRSens::getValue() const {
    return thisValue;
}

void LDRSens::setPins(uint8_t _pin) {
    this->sensorPin = _pin;
}