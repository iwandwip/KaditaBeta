/*
 *  timer-arduino.h
 *
 *  arduino timer lib
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef KADITA_TIMER_ARDUINO_H
#define KADITA_TIMER_ARDUINO_H

#include "Arduino.h"

class TimerArduino {
public:
    TimerArduino();

    void setDuration(unsigned long interval);

    void start();

    bool isExpired() const;

    void reset();

    unsigned long getHours() const;

    unsigned long getMinutes() const;

    unsigned long getSeconds() const;

    unsigned long getDuration() const;

private:
    unsigned long _startMillis;
    unsigned long _interval;  // in milliseconds
};

#endif // KADITA_TIMER_ARDUINO_H