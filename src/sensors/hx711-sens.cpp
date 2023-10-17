/*
 *  hx711-sens.cpp
 *
 *  hx711 sensor c
 *  Created on: 2023. 4. 3
 */

#include "hx711-sens.h"
#include "Arduino.h"

HX711Sens::HX711Sens()
        : thisValue(0.0),
          sensTimer{0, 0},
          sensorDOUTPin(2),
          sensorSCKPin(3) {
}

HX711Sens::HX711Sens(uint8_t _sensorDOUTPin, uint8_t _sensorSCKPin)
        : thisValue(0.0),
          sensTimer{0, 0} {
    this->sensorDOUTPin = _sensorDOUTPin;
    this->sensorSCKPin = _sensorSCKPin;
}

void HX711Sens::init() {
    this->begin(this->sensorDOUTPin, this->sensorSCKPin);
    this->read();
    this->read_average(20);
    this->get_value(5);
    this->get_units(5);
    this->set_scale(2280.f);
    this->tare();
    this->read();
    this->read_average(20);
    this->get_value(5);
    this->get_units(5);
}

void HX711Sens::update() {
    if (millis() - sensTimer[0] >= 500) {
        if (this->is_ready()) {
            thisValue = this->get_units();
        }
        sensTimer[0] = millis();
    }
    if (millis() - sensTimer[1] >= 5000) {
        this->power_down();
        sensTimer[1] = millis();
    }
    this->power_up();
}

#if defined(EXTENDED_FUNCTION_VTABLE)
void HX711Sens::debug() {
    if (millis() - sensTimer[1] >= 500) {
        if (isCalibrate) return;
        Serial.print("| thisValueRaw: ");
        Serial.print(thisValue);
        Serial.println();
        sensTimer[1] = millis();
    }
}

void HX711Sens::calibrate() {
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

void HX711Sens::getValue(float *output) {
    *output = thisValue;
}

void HX711Sens::getValue(int *output) {

}

void HX711Sens::getValue(char *output) {
}

#if defined(EXTENDED_FUNCTION_VTABLE)
void HX711Sens::setCallBack(void (*callbackFunc)(void)) {
    thisCallbackFunc = callbackFunc;
}

void HX711Sens::count() {
}

void HX711Sens::reset() {
}
#endif

float HX711Sens::getValue() const {
    return thisValue;
}

void HX711Sens::setPins(uint8_t _sensorDOUTPin, uint8_t _sensorSCKPin) {
    this->sensorDOUTPin = _sensorDOUTPin;
    this->sensorSCKPin = _sensorSCKPin;
}