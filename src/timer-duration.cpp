/*
 *  timer-duration.cpp
 *
 *  arduino timer duration c
 *  Created on: 2023. 4. 3
 */

#include "timer-duration.h"

#define TICKS 100

TimerDuration::TimerDuration() {
    _startMillis = 0;
    _interval = 0;
    _isRunning = false;
}

void TimerDuration::setDuration(unsigned long interval) {
    _interval = interval * 1000;  // convert to milliseconds
}

void TimerDuration::start() {
    _startMillis = millis();
    _isRunning = true;
}

void TimerDuration::stop() {
    _interval -= (millis() - _startMillis);
    _isRunning = false;
}

void TimerDuration::resume() {
    if (!_isRunning) {
        _startMillis = millis();
        _isRunning = true;
    }
}

bool TimerDuration::isExpired() const {
    if (_isRunning) {
        return (millis() - _startMillis >= _interval);
    } else {
        return false;
    }
}

void TimerDuration::reset() {
    _startMillis = millis();
}

unsigned long TimerDuration::getHours() const {
    unsigned long elapsedTime = millis() - _startMillis;
    return (elapsedTime / 1000) / 3600;
}

unsigned long TimerDuration::getMinutes() const {
    unsigned long elapsedTime = millis() - _startMillis;
    return ((elapsedTime / 1000) / 60) % 60;
}

unsigned long TimerDuration::getSeconds() const {
    unsigned long elapsedTime = millis() - _startMillis;
    return (elapsedTime / 1000) % 60;
}

unsigned long TimerDuration::getDuration() const {
    return _interval / 1000;  // convert back to seconds
}
