/*
 *  KeedBase.h
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef KEED_BASE_H
#define KEED_BASE_H

#include "KeedConfig.h"

typedef enum {
    IO_EXPANDER_0,
    IO_EXPANDER_1,
    IO_EXPANDER_2,
    IO_EXPANDER_3,
    IO_EXPANDER_4,
    IO_EXPANDER_5,
    IO_EXPANDER_6,
    IO_EXPANDER_7,
    IO_EXPANDER_NUM
} io_expander_index_t;

class KeedBase {
public:
    virtual void init() = 0;
    virtual void update() = 0;
    virtual void run(IOExpander **ioBase, uint8_t ioNum) = 0;
    virtual void run(configuration_t _cfg) = 0;

    KeedBase &operator=(const KeedBase &) = default;
    KeedBase &operator=(KeedBase &&) = default;
};

#endif // KEED_BASE_H