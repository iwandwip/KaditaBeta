/*
 *  Keed4ChannelExt.h
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef KEED_4_CHANNEL_EXT_H
#define KEED_4_CHANNEL_EXT_H

#include "../KeedBase.h"

class Keed4ChannelExt : public KeedBase {
private:
    IOExpander **ioBase;
    uint8_t ioNum;
    uint8_t sequence;
    uint32_t ioTimer;
    uint32_t isrTimer;

    interrupt_t isr;
    configuration_t cfg;

    void (Keed4ChannelExt::*taskTemp)();
    void (Keed4ChannelExt::*sequences[4])();

protected:
    void sleep(uint32_t _delay);
    void blink(uint32_t _delay);
    void snake(uint32_t _delay);
    void snakeReverse(uint32_t _delay);
    void set(uint8_t _pin, uint8_t _state);
    void off();
    void on();

public:
    Keed4ChannelExt();
    void init() override;
    void update() override;
    void run(IOExpander **_ioBase, uint8_t _ioNum) override;
    void run(configuration_t _cfg) override;

    void setInterruptConfig(interrupt_t _cfg) override;
    void changeModes() override;
    void setBaseDelay(uint32_t _time) override;

    void (Keed4ChannelExt::*getSequence(uint8_t index))();
    void taskSequence1();
    void taskSequence2();
    void taskSequence3();
    void taskSequenceOFF();
};

#endif // KEED_4_CHANNEL_EXT_H