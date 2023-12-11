/*
 *  Keed16Channel.h
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef KEED_16_CHANNEL_H
#define KEED_16_CHANNEL_H

#include "../KeedBase.h"

class Keed16Channel : public KeedBase {
private:
    IOExpander **ioBase;
    uint8_t ioNum;
    uint32_t ioTimer;
    uint8_t sequence;
    configuration_t cfg;
    void (Keed16Channel::*taskTemp)();
    void (Keed16Channel::*sequences[4])();

    void blink(uint32_t _delay);
    void snake(uint32_t _delay);
    void snakeReverse(uint32_t _delay);
public:
    Keed16Channel();
    void init() override;
    void update() override;
    void run(IOExpander **_ioBase, uint8_t _ioNum, configuration_t _cfg) override;

    void (Keed16Channel::*getSequence(uint8_t index))();
    void taskSequence0();
    void taskSequence1();
    void taskSequence2();
    void taskSequence3();
};

#endif // KEED_16_CHANNEL_H