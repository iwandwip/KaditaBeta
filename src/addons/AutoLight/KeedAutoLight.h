/*
 *  KeedAutoLight.h
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef KEED_AUTO_LIGHT_H
#define KEED_AUTO_LIGHT_H

#include "KeedIndex.h"

class KeedAutoLight {
private:
    IOExpander **ioBase;
    uint8_t ioLen;
    uint8_t ioChannel;
    uint8_t ioVersion;
    uint8_t ioNum;

    KeedBase *keedBase;
    uint8_t *pinPtr;

    void addIoExpander(IOExpander *ioExpander);
    bool beginExpander();
    KeedBase *switchChannel();

    bool isUsingExpander() const;
public:
    KeedAutoLight();
    ~KeedAutoLight();
    cfg_error_t init(uint8_t io_expander_num, uint8_t channel, uint8_t version, uint8_t *pin_ptr = nullptr);

    void runAutoLight();
    void showInfo();

    IOExpander *getIoExpander(uint8_t index);
    IOExpander &getIoExpanderRef(uint8_t index);
    IOExpander **getIoExpanderPtr();
};

#endif // KEED_AUTO_LIGHT_H