/*
 *  ina219-sens.cpp
 *
 *  ina219 sensor c
 *  Created on: 2023. 4. 3
 */

#include "ina219-sens.h"
#include "Arduino.h"

INA219Sens::INA219Sens(uint8_t addr)
        : Adafruit_INA219(addr),
          sensorValue{0.0, 0.0, 0.0, 0.0},
          sensorAddr(addr),
          sensorTimer(0) {
}

INA219Sens::~INA219Sens() = default;

void INA219Sens::init() {
    if (!Adafruit_INA219::begin()) {
        Serial.println("Failed to find INA219 chip");
    }
}

void INA219Sens::update() {
    if (millis() - sensorTimer >= 500) {
        sensorValue[INA219_SHUNT_VOLTAGE_MV] = Adafruit_INA219::getShuntVoltage_mV();
        sensorValue[INA219_BUS_VOLTAGE_V] = Adafruit_INA219::getBusVoltage_V();
        sensorValue[INA219_CURRENT_MA] = Adafruit_INA219::getCurrent_mA();
        sensorValue[INA219_POWER_MW] = Adafruit_INA219::getPower_mW();
        sensorTimer = millis();
    }
}

void INA219Sens::getValue(float *output) {
    output[INA219_SHUNT_VOLTAGE_MV] = sensorValue[INA219_SHUNT_VOLTAGE_MV];
    output[INA219_BUS_VOLTAGE_V] = sensorValue[INA219_BUS_VOLTAGE_V];
    output[INA219_CURRENT_MA] = sensorValue[INA219_CURRENT_MA];
    output[INA219_POWER_MW] = sensorValue[INA219_POWER_MW];
}

float INA219Sens::getValueShuntVoltage_mV() const {
    return sensorValue[INA219_SHUNT_VOLTAGE_MV];
}

float INA219Sens::getValueBusVoltage_V() const {
    return sensorValue[INA219_BUS_VOLTAGE_V];
}

float INA219Sens::getValueCurrent_mA() const {
    return sensorValue[INA219_CURRENT_MA];
}

float INA219Sens::getValuePower_mW() const {
    return sensorValue[INA219_POWER_MW];
}

void INA219Sens::setPins(uint8_t _pin) {
    sensorAddr = _pin;
}