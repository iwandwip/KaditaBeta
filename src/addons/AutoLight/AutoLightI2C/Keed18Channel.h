/*
 *  Keed18Channel.h
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef KEED_18_CHANNEL_EXT_H
#define KEED_18_CHANNEL_EXT_H

#define TASK_SEQUENCE_NUM 7
#define BUTTON_DEBOUNCE_TIME 250

#include "../KeedBase.h"

class Keed18Channel : public KeedBase {
private:
    IOExpander **ioBase;
    uint8_t ioNum;
    uint8_t sequence;
    uint32_t ioTimer;
    uint32_t isrTimer;
    interrupt_t isr;
    configuration_t cfg;

    void (Keed18Channel::*taskTemp)();
    void (Keed18Channel::*sequences[(TASK_SEQUENCE_NUM + 2)])();

protected:
    void sleep(uint32_t _delay);
    void set(uint8_t _pin, uint8_t _state);
    void setStateHigh(int index, ...);
    void setStateLow(int index, ...);
    void off();
    void on();

public:
    Keed18Channel();
    void init() override;
    void update() override;
    void run(IOExpander **_ioBase, uint8_t _ioNum, configuration_t _cfg) override;
    void setInterruptConfig(interrupt_t _cfg) override;
    void changeModes() override;
    void setBaseDelay(uint32_t _time) override;
    void (Keed18Channel::*getSequence(uint8_t index))();

    void taskSequence0();
    void taskSequence1();
    void taskSequence2();
    void taskSequence3();
    void taskSequence4();
    void taskSequence5();
    void taskSequence6();
};

#endif // KEED_18_CHANNEL_EXT_H