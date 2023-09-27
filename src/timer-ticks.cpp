/*
 *  timer-ticks.cpp
 *
 *  timer module c
 *  Created on: 2023. 4. 3
 */

#include "timer-ticks.h"

TimerTicks::TimerTicks() = default;

TimerTicks::TimerTicks(const unsigned long &timeout, const bool &micros) {
    us = micros;
    update(timeout);
}

void TimerTicks::begin(const unsigned long &timeout, const bool &micros) {
    us = micros;
    update(timeout);
}

void TimerTicks::update(const unsigned long &timeout) {
    period = timeout;
    start();
}

void TimerTicks::start() {
    if (us)
        timeBench = micros();
    else
        timeBench = millis();
}

void TimerTicks::reset() {
    timeBench += period;
}

bool TimerTicks::tick(const bool &_reset) {
    unsigned long currentTime;

    if (us)
        currentTime = micros();
    else
        currentTime = millis();

    if (currentTime < timeBench)
        timeDiff = (UL_MAX - timeBench) + currentTime;
    else
        timeDiff = currentTime - timeBench;

    if (timeDiff >= period) {
        if (_reset)
            reset();
        return true;
    }

    return false;
}