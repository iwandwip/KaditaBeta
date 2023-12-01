/*
 *  Keed.h
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef KEED_H
#define KEED_H

#include "Kadita.h"
#include "KeedConfig.h"

typedef enum {
    IO_EXPANDER_0,
    IO_EXPANDER_1,
    IO_EXPANDER_2,
    IO_EXPANDER_3,
    IO_EXPANDER_4,
    IO_EXPANDER_5,
    IO_EXPANDER_6,
    IO_EXPANDER_7
} io_expander_index_t;

class KeedWelcomingLight {
private:
    IOExpander **ioBase;
    uint8_t ioLen;
    uint8_t ioChannel;
    uint8_t ioVersion;

    void addIoExpander(IOExpander *ioExpander);
    IOExpander *getIoExpander(uint8_t index);
    IOExpander &getIoExpanderRef(uint8_t index);
public:
    KeedWelcomingLight();
    ~KeedWelcomingLight();
    cfg_error_t init(uint8_t io_expander_num, uint8_t channel, uint8_t version);
    void runWelcomingLight();
};

#endif // KEED_H