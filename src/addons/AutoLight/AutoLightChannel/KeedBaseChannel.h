/*
 *  KeedBaseChannel.h
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef KEED_BASE_CHANNEL_H
#define KEED_BASE_CHANNEL_H

#define TASK_SEQUENCE_NUM 7
#define BUTTON_DEBOUNCE_TIME 250

#define setHigh(...) setStateHigh(__VA_ARGS__, -1)
#define setLow(...) setStateLow(__VA_ARGS__, -1)

#include "../KeedBase.h"

class KeedBaseChannel : public KeedBase {
private:
    IOExpander **ioBase;
    KeedDisplay *display;
    uint32_t isrTimer;
    interrupt_t isr;
    configuration_t cfg;
    bool isUsingExpander;

    void (KeedBaseChannel::*taskTemp)();
    void (KeedBaseChannel::*totalMode[(TASK_SEQUENCE_NUM + 2)])();

protected:
    void sleep(uint32_t _delay);
    void set(uint8_t _pin, uint8_t _state);
    void setStateHigh(int index, ...);
    void setStateLow(int index, ...);
    void forceOff();
    void off();
    void on();

public:
    KeedBaseChannel(bool _isUsingExpander = false);
    void init(IOExpander **_ioBase, configuration_t _cfg) override;
    void update() override;
    void run() override;
    void setInterruptConfig(interrupt_t _cfg) override;
    void changeModes() override;
    void setBaseDelay(uint32_t _time) override;
    uint8_t getSequenceIndex() override;
    void (KeedBaseChannel::*getSequence(uint8_t index))();

    void taskSequence0();
    void taskSequence1();
    void taskSequence2();
    void taskSequence3();
    void taskSequence4();
    void taskSequence5();
    void taskSequence6();
};

#endif // KEED_BASE_CHANNEL_H