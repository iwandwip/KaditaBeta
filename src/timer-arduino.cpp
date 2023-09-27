/*
 *  timer-arduino.cpp
 *
 *  arduino timer c
 *  Created on: 2023. 4. 3
 */

#include "timer-arduino.h"

#define TICKS 100

TimerArduino::TimerArduino() {
    _startMillis = millis();
    _interval = 0;
}

void TimerArduino::setDuration(unsigned long interval) {
    _interval = interval * 1000;  // convert to milliseconds
}

void TimerArduino::start() {
    _startMillis = millis();
}

bool TimerArduino::isExpired() const {
    return (millis() - _startMillis >= _interval);
}

void TimerArduino::reset() {
    _startMillis = millis();
}

unsigned long TimerArduino::getHours() const {
    unsigned long elapsedTime = millis() - _startMillis;
    return (elapsedTime / 1000) / 3600;
}

unsigned long TimerArduino::getMinutes() const {
    unsigned long elapsedTime = millis() - _startMillis;
    return ((elapsedTime / 1000) / 60) % 60;
}

unsigned long TimerArduino::getSeconds() const {
    unsigned long elapsedTime = millis() - _startMillis;
    return (elapsedTime / 1000) % 60;
}

unsigned long TimerArduino::getDuration() const {
    return _interval / 1000;  // convert back to seconds
}
