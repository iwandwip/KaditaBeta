/*
 *  flowmeter-sens.cpp
 *
 *  flowmeter sensor c
 *  Created on: 2023. 4. 3
 */

#include "flowmeter-sens.h"
#include "Arduino.h"

FlowmeterSens::FlowmeterSens(uint8_t _pin, void (*_callback)(), FlowSensorProperties _properties)
        : sensorClass(nullptr),
          sensorProperties(_properties),
          sensorValue{0.0, 0.0, 0.0, 0.0},
          sensorPin(_pin),
          sensorTimer(0),
          sensorCallbackFunc(_callback) {
}

FlowmeterSens::~FlowmeterSens() = default;

void FlowmeterSens::init() {
    sensorClass = new FlowMeter(digitalPinToInterrupt(sensorPin), sensorProperties, sensorCallbackFunc, RISING);
}

void FlowmeterSens::update() {
    if (millis() - sensorTimer >= 1000) {
        sensorClass->tick(1000);
        sensorValue[FLOW_METER_CURRENT_RATE] = (float) sensorClass->getCurrentFlowrate();
        sensorValue[FLOW_METER_CURRENT_VOLUME] = (float) sensorClass->getCurrentVolume();
        sensorValue[FLOW_METER_TOTAL_RATE] = (float) sensorClass->getTotalFlowrate();
        sensorValue[FLOW_METER_TOTAL_VOLUME] = (float) sensorClass->getTotalVolume();
        sensorTimer = millis();
    }
}

void FlowmeterSens::process() {
    sensorClass->count();
}

void FlowmeterSens::getValue(float *output) {
    output[FLOW_METER_CURRENT_RATE] = sensorValue[FLOW_METER_CURRENT_RATE];
    output[FLOW_METER_CURRENT_VOLUME] = sensorValue[FLOW_METER_CURRENT_VOLUME];
    output[FLOW_METER_TOTAL_RATE] = sensorValue[FLOW_METER_TOTAL_RATE];
    output[FLOW_METER_TOTAL_VOLUME] = sensorValue[FLOW_METER_TOTAL_VOLUME];
}

float FlowmeterSens::getValueFlowMeter(flow_meter_index_t _index) const {
    return sensorValue[_index];
}

void FlowmeterSens::setPins(uint8_t _pin) {
    sensorPin = _pin;
}