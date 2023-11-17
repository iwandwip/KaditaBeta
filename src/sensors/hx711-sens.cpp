/*
 *  hx711-sens.cpp
 *
 *  hx711 sensor c
 *  Created on: 2023. 4. 3
 */

#include "hx711-sens.h"
#include "Arduino.h"

HX711Sens::HX711Sens()
        : sensorValue(0.0),
          sensorTimer{0, 0},
          sensorDOUTPin(2),
          sensorSCKPin(3) {
}

HX711Sens::HX711Sens(uint8_t _sensorDOUTPin, uint8_t _sensorSCKPin)
        : sensorValue(0.0),
          sensorTimer{0, 0},
          sensorDOUTPin(_sensorDOUTPin),
          sensorSCKPin(_sensorSCKPin) {
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
    if (millis() - sensorTimer[0] >= 500) {
        if (this->is_ready()) {
            sensorValue = this->get_units();
        }
        sensorTimer[0] = millis();
    }
//    if (millis() - sensorTimer[1] >= 5000) {
//        this->power_down();
//        sensorTimer[1] = millis();
//    }
//    this->power_up();
}

void HX711Sens::getValue(float *output) {
    *output = sensorValue;
}

void HX711Sens::getValue(int *output) {

}

void HX711Sens::getValue(char *output) {
}

float HX711Sens::getValueWeight() const {
    return sensorValue;
}

void HX711Sens::setPins(uint8_t _sensorDOUTPin, uint8_t _sensorSCKPin) {
    this->sensorDOUTPin = _sensorDOUTPin;
    this->sensorSCKPin = _sensorSCKPin;
}