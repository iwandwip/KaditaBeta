/*
 * Flow Meter
 */

/*
 *  flowmeter-sens.cpp
 *
 *  flowmeter sensor c
 *  Created on: 2023. 4. 3
 */

#include "flowmeter-sens.h"
#include "Arduino.h"

FlowMeter::FlowMeter(unsigned int pin, FlowSensorProperties prop, void (*callback)(void), uint8_t interruptMode) :
        _pin(pin),                                                              //!< store pin number
        _properties(prop),                                                      //!< store sensor properties
        _interruptCallback(callback),
        _interruptMode(interruptMode) {
    pinMode(this->_pin, INPUT_PULLUP);                                      //!< initialize interrupt pin as input with pullup

    if (this->_interruptCallback != NULL) {                                 //!< if ISR callback has been provided, attach it
        attachInterrupt(this->_pin, this->_interruptCallback, this->_interruptMode);
    }

    this->reset();                                                          //!< ignore pulses generated during initialisation
}

double FlowMeter::getCurrentFlowrate() {
    return this->_currentFlowrate;                                          //!< in l/min
}

double FlowMeter::getCurrentVolume() {
    return this->_currentVolume;                                            //!< in l
}

double FlowMeter::getTotalFlowrate() {
    return this->_totalVolume / (this->_totalDuration / 1000.0f) * 60.0f;   //!< in l/min
}

double FlowMeter::getTotalVolume() {
    return this->_totalVolume;                                              //!< in l
}

void FlowMeter::tick(unsigned long duration) {
    /* sampling */
    noInterrupts();                                                         //!< going to change interrupt variable(s)
    volatile unsigned long pulses = this->_currentPulses;                   //!< sample current pulses from counter
    this->_currentPulses = 0;                                               //!< reset pulse counter after successful sampling
    interrupts();                                                           //!< done changing interrupt variable(s)

    /* normalisation */
    double seconds = duration / 1000.0f;                                    //!< normalised duration (in s, i.e. per 1000ms)
    double frequency = pulses / seconds;                                    //!< normalised frequency (in 1/s)

    /* determine current correction factor (from sensor properties) */
    unsigned int decile = floor(10.0f * frequency / (this->_properties.capacity * this->_properties.kFactor));          //!< decile of current flow relative to sensor capacity
    unsigned int ceiling = 9;                                                                                          //!< highest possible decile index
    this->_currentCorrection = this->_properties.kFactor / this->_properties.mFactor[min(decile, ceiling)];             //!< combine constant k-factor and m-factor for decile

    /* update current calculations: */
    this->_currentFlowrate = frequency / this->_currentCorrection;          //!< get flow rate (in l/min) from normalised frequency and combined correction factor
    this->_currentVolume = this->_currentFlowrate / (60.0f / seconds);        //!< get volume (in l) from normalised flow rate and normalised time

    /* update statistics: */
    this->_currentDuration = duration;                                      //!< store current tick duration (convenience, in ms)
    this->_currentFrequency = frequency;                                    //!< store current pulses per second (convenience, in 1/s)
    this->_totalDuration += duration;                                       //!< accumulate total duration (in ms)
    this->_totalVolume += this->_currentVolume;                             //!< accumulate total volume (in l)
    this->_totalCorrection += this->_currentCorrection * duration;          //!< accumulate corrections over time
}

void FlowMeter::count() {
    this->_currentPulses++;                                                 //!< this should be called from an interrupt service routine
}

void FlowMeter::reset() {
    noInterrupts();                                                         //!< going to change interrupt variable(s)
    this->_currentPulses = 0;                                               //!< reset pulse counter
    interrupts();                                                           //!< done changing interrupt variable(s)

    this->_currentFrequency = 0.0f;
    this->_currentDuration = 0.0f;
    this->_currentFlowrate = 0.0f;
    this->_currentVolume = 0.0f;
    this->_currentCorrection = 0.0f;
}

unsigned int FlowMeter::getPin() {
    return this->_pin;
}

unsigned long FlowMeter::getCurrentDuration() {
    return this->_currentDuration;                                          //!< in ms
}

double FlowMeter::getCurrentFrequency() {
    return this->_currentFrequency;                                         //!< in 1/s
}

double FlowMeter::getCurrentError() {
    /// error (in %) = error * 100
    /// error = correction rate - 1
    /// correction rate = k-factor / correction
    return (this->_properties.kFactor / this->_currentCorrection - 1) * 100;  //!< in %
}

unsigned long FlowMeter::getTotalDuration() {
    return this->_totalDuration;                                            //!< in ms
}

double FlowMeter::getTotalError() {
    /// average error (in %) = average error * 100
    /// average error = average correction rate - 1
    /// average correction rate = k-factor / corrections over time * total time
    return (this->_properties.kFactor / this->_totalCorrection * this->_totalDuration - 1) * 100;
}

FlowMeter *FlowMeter::setTotalDuration(unsigned long totalDuration) {
    this->_totalDuration = totalDuration;
    return this;
}

FlowMeter *FlowMeter::setTotalVolume(double totalVolume) {
    this->_totalVolume = totalVolume;
    return this;
}

FlowMeter *FlowMeter::setTotalCorrection(double totalCorrection) {
    this->_totalCorrection = totalCorrection;
    return this;
}

FlowSensorProperties UncalibratedSensor = {60.0f, 5.0f, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
FlowSensorProperties FS300A = {60.0f, 5.5f, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
FlowSensorProperties FS400A = {60.0f, 4.8f, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};


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
    if (millis() - sensorTimer >= FLOW_METER_PERIOD) {
        sensorClass->tick(FLOW_METER_PERIOD);
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