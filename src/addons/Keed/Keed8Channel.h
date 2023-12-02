/*
 *  Keed8Channel.h
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef KEED_8_CHANNEL_H
#define KEED_8_CHANNEL_H

#include "Keed.h"

class Keed8Channel : public KeedBase {
private:
    uint32_t chTimer;
public:
    Keed8Channel();
    void init() override;
    void update() override;
    void run(IOExpander **ioBase, uint8_t ioNum) override;
};

#endif // KEED_8_CHANNEL_H