/*
 *  Keed16Channel.h
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef KEED_16_CHANNEL_H
#define KEED_16_CHANNEL_H

#include "KeedBase.h"

class Keed16Channel : public KeedBase {
private:
    uint32_t chTimer;
public:
    Keed16Channel();
    void init() override;
    void update() override;
    void run(IOExpander **ioBase, uint8_t ioNum) override;
};

#endif // KEED_16_CHANNEL_H