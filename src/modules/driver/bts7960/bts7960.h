/*
 *  bts7960.h
 *
 *  bts7960 motor driver
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef BTS_7960_H
#define BTS_7960_H

#include "Arduino.h"

class BTS7960 {
private:
    uint8_t _L_EN;
    uint8_t _R_EN;
    uint8_t _L_PWM;
    uint8_t _R_PWM;
public:
    BTS7960(uint8_t EN, uint8_t L_PWM, uint8_t R_PWM)
            : BTS7960(EN, 0, L_PWM, R_PWM) {}

    BTS7960(uint8_t L_EN, uint8_t R_EN, uint8_t L_PWM, uint8_t R_PWM);
    void enable();
    void disable();

    void turnLeft(uint8_t pwm);
    void turnRight(uint8_t pwm);
    void stop();
};

#endif  // BTS_7960_H