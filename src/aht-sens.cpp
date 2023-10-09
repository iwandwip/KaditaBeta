/*
 *  aht-sens.cpp
 *
 *  aht sensor c
 *  Created on: 2023. 4. 3
 */

#include "aht-sens.h"
#include "Arduino.h"

AHTSens::AHTSens()
        : isCalibrate(false), sensorPin(A0) {
}

AHTSens::AHTSens(uint8_t _pin, bool enableCalibrate) {
    this->sensorPin = _pin;
    isCalibrate = enableCalibrate;
}

AHTSens::~AHTSens() = default;

void AHTSens::init() {
    thisClass = new Adafruit_AHTX0;
    if (!(*thisClass).begin())
        while (1) {
            delay(10);
            break;
        }
}

void AHTSens::update() {
    if (millis() - sensTimer[0] >= 500) {
        if (!isCalibrate) {
            sensors_event_t dataBuffer[2];
            (*thisClass).getEvent(&dataBuffer[1], &dataBuffer[0]);
            thisValue[0] = dataBuffer[0].temperature;
            thisValue[1] = dataBuffer[1].relative_humidity;
        }
        sensTimer[0] = millis();
    }
}

#if defined(EXTENDED_FUNCTION_VTABLE)
void AHTSens::debug() {
    if (millis() - sensTimer[1] >= 500) {
        if (isCalibrate) return;
        Serial.print("| thisValueRaw: ");
        Serial.print(thisValue);
        Serial.println();
        sensTimer[1] = millis();
    }
}

void AHTSens::calibrate() {
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

void AHTSens::getValue(float *output) {
    output[0] = thisValue[0];
    output[1] = thisValue[1];
}

#if defined(EXTENDED_FUNCTION_VTABLE)
void AHTSens::setCallBack(void (*callbackFunc)(void)) {
    thisCallbackFunc = callbackFunc;
}

void AHTSens::count() {
}

void AHTSens::reset() {
}
#endif

float AHTSens::getValueTemperature() const {
    return thisValue[0];
}

float AHTSens::getValueHumidity() const {
    return thisValue[1];
}

void AHTSens::setPins(uint8_t _pin) {
    this->sensorPin = _pin;
}