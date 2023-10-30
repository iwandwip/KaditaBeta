/*
 *  flowmeter-sens.h
 *
 *  flowmeter sensor lib
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef FLOWMETER_SENS_H
#define FLOWMETER_SENS_H

#include "Arduino.h"
#include "base/sensor-module.h"
#include "FlowMeter.h"

#define FLOW_METER_PERIOD 1000

enum flow_meter_index_t {
    FLOW_METER_CURRENT_RATE = 0,
    FLOW_METER_CURRENT_VOLUME = 1,
    FLOW_METER_TOTAL_RATE = 2,
    FLOW_METER_TOTAL_VOLUME = 3,
    FLOW_METER_NUM_VALUE = 4
};

class FlowmeterSens : public BaseSens {
private:
    /*variables*/
    FlowMeter *sensorClass;
    FlowSensorProperties sensorProperties;

    float sensorValue[FLOW_METER_NUM_VALUE];
    uint8_t sensorPin;
    uint32_t sensorTimer;

    /*optional object*/
    void (*sensorCallbackFunc)();

public:
    explicit FlowmeterSens(uint8_t _pin, void (*_callback)(), FlowSensorProperties _properties = UncalibratedSensor);
    ~FlowmeterSens();
    void init() override;
    void update() override;
    void process() override;
    void getValue(float *output) override;
    float getValueFlowMeter(flow_meter_index_t _index = FLOW_METER_CURRENT_RATE) const;
    void setPins(uint8_t _pin);
};

#endif  // FLOWMETER_SENS_H