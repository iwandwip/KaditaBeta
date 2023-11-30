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

class KeedWelcomingLight {
private:
    uint8_t ioLen;
    IOExpander **ioBase;

    void addIoExpander(IOExpander *ioExpander);
public:
    KeedWelcomingLight();
    ~KeedWelcomingLight();
    cfg_error_t init(uint8_t io_expander_num, uint8_t version);
};

#endif // KEED_H