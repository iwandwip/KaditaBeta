/*
 *  timer-task.cpp
 *
 *  timer module c
 *  Created on: 2023. 4. 3
 */

#include "timer-task.h"

const unsigned long UL_MAX = 4294967295;

TimerTask::TimerTask() = default;

TimerTask::TimerTask(const unsigned long &timeout, const bool &micros) {
    us = micros;
    update(timeout);
}

void TimerTask::begin(const unsigned long &timeout, const bool &micros) {
    us = micros;
    update(timeout);
}

void TimerTask::update(const unsigned long &timeout) {
    period = timeout;
    start();
}

void TimerTask::start() {
    if (us)
        timeBench = micros();
    else
        timeBench = millis();
}

void TimerTask::reset() {
    timeBench += period;
}

bool TimerTask::triggered(const bool &_reset) {
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