/*
 *  Keed6ChannelExt.h
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef KEED_6_CHANNEL_EXT_H
#define KEED_6_CHANNEL_EXT_H

#define TASK_SEQUENCE_NUM 4
#define BUTTON_DEBOUNCE_TIME 250

#include "../KeedBase.h"

class Keed6ChannelExt : public KeedBase {
private:
    IOExpander **ioBase;
    uint8_t ioNum;
    uint8_t sequence;
    uint32_t ioTimer;
    uint32_t isrTimer;

    interrupt_t isr;
    configuration_t cfg;

    void (Keed6ChannelExt::*taskTemp)();
    void (Keed6ChannelExt::*sequences[TASK_SEQUENCE_NUM])();

protected:
    void sleep(uint32_t _delay);
    void set(uint8_t _pin, uint8_t _state);
    void setStateHigh(int index, ...);
    void setStateLow(int index, ...);
    void off();
    void on();

public:
    Keed6ChannelExt();
    void init() override;
    void update() override;
    void run(IOExpander **_ioBase, uint8_t _ioNum, configuration_t _cfg) override;

    void setInterruptConfig(interrupt_t _cfg) override;
    void changeModes() override;
    void setBaseDelay(uint32_t _time) override;

    void (Keed6ChannelExt::*getSequence(uint8_t index))();
    void taskSequence1();
    void taskSequence2();
    void taskSequenceOFF();
    void taskSequenceON();
};

#endif // KEED_6_CHANNEL_EXT_H