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

float HX711Sens::getCalibrateFactorInit(float weight) {
    float calibrationFactor = 0.0;
    if (this->is_ready()) {
        this->set_scale();
        Serial.println("Tare... remove any weights from the scale.");
        delay(5000);
        this->tare();
        Serial.println("Tare done...");
        Serial.print("Place a known weight on the scale...");
        delay(5000);
        float reading = this->get_units(10);
        Serial.print("| reading: ");
        Serial.print(reading);
        Serial.print("| result: ");
        Serial.print(reading / weight);
        Serial.println();
        delay(5000);
    }
    return calibrationFactor;
}

bool HX711Sens::isReady() {
    return this->is_ready();
}

void HX711Sens::setScaleDelay(long time, float scale) {
    this->set_scale(scale);
    delay(time);
}

void HX711Sens::setScale(float scale) {
    this->set_scale(scale);
}

void HX711Sens::tareDelay(long time) {
    this->tare();
    delay(time);
}

float HX711Sens::getUnits(byte time) {
    return this->get_units(time);
}

uint32_t HX711Sens::getADC(byte times) {
    return this->read_average();
}

float HX711Sens::getCalibrateFactor(float units, float weight) {
    return units / weight;
}

float HX711Sens::getValueWeight() const {
    return sensorValue;
}

void HX711Sens::setPins(uint8_t _sensorDOUTPin, uint8_t _sensorSCKPin) {
    this->sensorDOUTPin = _sensorDOUTPin;
    this->sensorSCKPin = _sensorSCKPin;
}