/*
 *  KeedTaskSeq.h
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef KEED_TASK_SEQ_H
#define KEED_TASK_SEQ_H

#define TASK_SEQUENCE_NUM 7
#define BUTTON_DEBOUNCE_TIME 250

#include "KeedBase.h"

class KeedTaskSeq : public KeedBase {
private:
    IOExpander **ioBase;
    uint8_t sequence;
    uint32_t ioTimer;
    uint32_t isrTimer;
    interrupt_t isr;
    configuration_t cfg;

    void (KeedTaskSeq::*taskTemp)();
    void (KeedTaskSeq::*sequences[(TASK_SEQUENCE_NUM + 2)])();

protected:
    void sleep(uint32_t _delay);
    void set(uint8_t _pin, uint8_t _state);
    void setStateHigh(int index, ...);
    void setStateLow(int index, ...);
    void off();
    void on();

public:
    KeedTaskSeq();
    void init(IOExpander **_ioBase, configuration_t _cfg) override;
    void update() override;
    void run() override;
    void setInterruptConfig(interrupt_t _cfg) override;
    void changeModes() override;
    void setBaseDelay(uint32_t _time) override;
    void (KeedTaskSeq::*getSequence(uint8_t index))();

    void taskSequence0();
    void taskSequence1();
    void taskSequence2();
    void taskSequence3();
    void taskSequence4();
    void taskSequence5();
    void taskSequence6();
};

#endif // KEED_TASK_SEQ_H