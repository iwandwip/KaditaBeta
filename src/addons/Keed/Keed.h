/*
 *  Keed.h
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef KEED_H
#define KEED_H

#include "KeedBase.h"
#include "Keed8Channel.h"
#include "Keed16Channel.h"

class KeedWelcomingLight {
private:
    IOExpander **ioBase;
    uint8_t ioLen;
    uint8_t ioChannel;
    uint8_t ioVersion;
    uint8_t ioNum;

    KeedBase *keedBase;

    void addIoExpander(IOExpander *ioExpander);
    bool beginExpander();
    KeedBase* switchChannel();

public:
    KeedWelcomingLight();
    ~KeedWelcomingLight();
    cfg_error_t init(uint8_t io_expander_num, uint8_t channel, uint8_t version);

    void runWelcomingLight();
    void showInfo();

    IOExpander *getIoExpander(uint8_t index);
    IOExpander &getIoExpanderRef(uint8_t index);
    IOExpander **getIoExpanderPtr();
};

#endif // KEED_H