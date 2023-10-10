/*
 *  output-module.cpp
 *
 *  output module c
 *  Created on: 2023. 4. 3
 */

#include "output-module.h"

DigitalOut::DigitalOut() {
    _pin = 0;
    _state = false;
    _onDelayTime = 0;
    _onDelayStart = 0;
    _onDelayState = false;
    _offDelayTime = 0;
    _offDelayStart = 0;
    _offDelayState = false;
}

DigitalOut::DigitalOut(int pin, bool isReverse) {
    _pin = pin;
    _reverse = isReverse;
    init();
}

void DigitalOut::init() {
    pinMode(_pin, OUTPUT);
    off();
}

void DigitalOut::on() {
    if (_reverse)
        digitalWrite(_pin, LOW);
    else
        digitalWrite(_pin, HIGH);
    _state = true;
}

void DigitalOut::off() {
    if (_reverse)
        digitalWrite(_pin, HIGH);
    else
        digitalWrite(_pin, LOW);
    _state = false;
}

void DigitalOut::set(bool state) {
    if (state) {
        on();
    } else {
        off();
    }
}

void DigitalOut::toggle() {
    set(!_state);
}

void DigitalOut::onDelay(unsigned long delay_time) {
    _onDelayTime = delay_time;
    _onDelayStart = millis();
    _onDelayState = true;
}

void DigitalOut::offDelay(unsigned long delay_time) {
    _offDelayTime = delay_time;
    _offDelayStart = millis();
    _offDelayState = true;
}

void DigitalOut::update() {
    if (_onDelayState) {
        unsigned long currentMillisOn = millis();
        if (currentMillisOn - _onDelayStart >= _onDelayTime) {
            on();
            _onDelayState = false;
        }
    }
    if (_offDelayState) {
        unsigned long currentMillisOff = millis();
        if (currentMillisOff - _offDelayStart >= _offDelayTime) {
            off();
            _offDelayState = false;
        }
    }
}

void DigitalOut::reverse() {
    _reverse = true;
}

void DigitalOut::setPins(uint8_t pin, bool isReverse) {
    _reverse = isReverse;
    _pin = pin;
    init();
}

bool DigitalOut::getState() const {
    return _state;
}