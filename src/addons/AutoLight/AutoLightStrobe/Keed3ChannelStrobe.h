/*
 *  Keed3ChannelStrobe.h
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef KEED_3_CHANNEL_STROBE_H
#define KEED_3_CHANNEL_STROBE_H

#include "../KeedBase.h"

class Keed3ChannelStrobe : public KeedBase {
private:
    IOExpander **ioBase;
    uint8_t ioNum;
    uint8_t sequence;
    uint32_t ioTimer;
    uint32_t isrTimer;

    interrupt_t isr;
    configuration_t cfg;

    void (Keed3ChannelStrobe::*taskTemp)();
    void (Keed3ChannelStrobe::*sequences[4])();

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
    Keed3ChannelStrobe();
    void init(IOExpander **_ioBase, configuration_t _cfg) override;
    void update() override;
    void run() override;

    void setInterruptConfig(interrupt_t _cfg) override;
    void changeModes() override;
    void setBaseDelay(uint32_t _time) override;

    void (Keed3ChannelStrobe::*getSequence(uint8_t index))();
    void taskSequence1();
    void taskSequence2();
    void taskSequence3();
    void taskSequenceOFF();
};

#endif // KEED_3_CHANNEL_STROBE_H