/*
 *  timer-task.h
 *
 *  timer task module header
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef KADITA_TIMER_TASK_H
#define KADITA_TIMER_TASK_H

#include "Arduino.h"

#define MILLI_SECONDS false
#define MICRO_SECONDS true

class TimerTask {
private:
    unsigned long timeBench = 0;
    unsigned long period = 0;
    unsigned long timeDiff = 0;
    bool us = false;

public:
    TimerTask();

    explicit TimerTask(const unsigned long &timeout, const bool &micros = false);

    void begin(const unsigned long &timeout, const bool &micros = false);

    void update(const unsigned long &timeout);

    void start();

    void reset();

    bool triggered(const bool &_reset = true);
};

#endif  // KADITA_TIMER_TASK_H
