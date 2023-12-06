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
    configuration_t cfg;
    IOExpander **ioBase;
    KeedBase *keedBase;
    uint8_t ioLen;

    void addIoExpander(IOExpander *ioExpander);
    bool beginExpander();
    KeedBase *switchChannel();
    bool isUsingExpander() const;
public:
    KeedAutoLight();
    ~KeedAutoLight();
    cfg_error_t init(configuration_t _cfg);

    void runAutoLight();
    void showInfo();

    IOExpander *getIoExpander(uint8_t index);
    IOExpander &getIoExpanderRef(uint8_t index);
    IOExpander **getIoExpanderPtr();

    KeedBase *getChannelClassPtr();
    KeedBase &getChannelClass();
};

#endif // KEED_AUTO_LIGHT_H