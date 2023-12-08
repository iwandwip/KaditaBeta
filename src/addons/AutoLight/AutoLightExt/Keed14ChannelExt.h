/*
 *  Keed14ChannelExt.h
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef KEED_14_CHANNEL_EXT_H
#define KEED_14_CHANNEL_EXT_H

#include "../KeedBase.h"

class Keed14ChannelExt : public KeedBase {
private:
    IOExpander **ioBase;
    uint8_t ioNum;
    uint8_t sequence;
    uint32_t ioTimer;
    uint32_t isrTimer;

    interrupt_t isr;
    configuration_t cfg;

    void (Keed14ChannelExt::*taskTemp)();
    void (Keed14ChannelExt::*sequences[4])();

protected:
    void sleep(uint32_t _delay);
    void blink(uint32_t _delay);
    void snake(uint32_t _delay);
    void snakeReverse(uint32_t _delay);
    void set(uint8_t _pin, uint8_t _state);
    void setStateHigh(int index, ...);
    void setStateLow(int index, ...);
    void off();
    void on();

public:
    Keed14ChannelExt();
    void init() override;
    void update() override;
    void run(IOExpander **_ioBase, uint8_t _ioNum) override;
    void run(configuration_t _cfg) override;

    void setInterruptConfig(interrupt_t _cfg) override;
    void changeModes() override;
    void setBaseDelay(uint32_t _time) override;

    void (Keed14ChannelExt::*getSequence(uint8_t index))();
    void taskSequence1();
    void taskSequence2();
    void taskSequence3();
    void taskSequenceOFF();
};

#endif // KEED_14_CHANNEL_EXT_H