/*
 *  Keed6ChannelExt.h
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef KEED_6_CHANNEL_EXT_H
#define KEED_6_CHANNEL_EXT_H

#include "KeedBase.h"

class Keed6ChannelExt : public KeedBase {
private:
    IOExpander **ioBase;
    uint8_t ioNum;
    uint32_t ioTimer;
    uint8_t sequence;
    configuration_t cfg;
    interrupt_t isr;

    void (Keed6ChannelExt::*taskTemp)();
    void (Keed6ChannelExt::*sequences[4])();

    void blink(uint32_t _delay);
    void snake(uint32_t _delay);
    void snakeReverse(uint32_t _delay);
    void set(uint8_t _pin, uint8_t _state);
    void off();
    void on();

public:
    Keed6ChannelExt();
    void init() override;
    void update() override;
    void run(IOExpander **_ioBase, uint8_t _ioNum) override;
    void run(configuration_t _cfg) override;

    void setInterruptConfig(interrupt_t _cfg) override;
    void changeModes() override;

    void (Keed6ChannelExt::*getSequence(uint8_t index))();
    void taskSequence0();
    void taskSequence1();
    void taskSequence2();
    void taskSequence3();
};

#endif // KEED_6_CHANNEL_EXT_H