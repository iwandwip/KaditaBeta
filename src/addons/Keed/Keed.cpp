/*
 *  Keed.cpp
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#include "Keed.h"

KeedWelcomingLight::KeedWelcomingLight()
        : ioBase(nullptr),
          ioLen(0),
          ioChannel(0),
          ioVersion(0),
          ioNum(0),
          keedBase(nullptr) {}

KeedWelcomingLight::~KeedWelcomingLight() {
    free(ioBase);
    free(keedBase);
    ioBase = nullptr;
    keedBase = nullptr;
}

cfg_error_t KeedWelcomingLight::init(uint8_t io_expander_num, uint8_t channel, uint8_t version) {
    ioNum = io_expander_num;
    ioChannel = channel;
    ioVersion = version;

    if (!beginExpander()) return INITIALIZE_ERROR;
    else {
        showInfo();
        keedBase = switchChannel();
        return INITIALIZE_OK;
    }
}

void KeedWelcomingLight::runWelcomingLight() {
    keedBase->run(ioBase, ioNum);
}

void KeedWelcomingLight::addIoExpander(IOExpander *ioExpander) {
    IOExpander **newIoBase = (IOExpander **) realloc(ioBase, (ioLen + 1) * sizeof(IOExpander *));
    if (newIoBase == nullptr) {
        return;
    }
    ioBase = newIoBase;
    ioBase[ioLen] = ioExpander;
    ioLen++;
}

bool KeedWelcomingLight::beginExpander() {
    for (int i = 0; i < ioNum; i++) {
        addIoExpander(new IOExpander(i2c_address_arr_t[i]));
    }
    for (int i = 0; i < ioLen; i++) {
        for (int j = 0; j < IO_EXPANDER_PIN_NUM; j++) {
            ioBase[i]->pinMode(j, OUTPUT);
        }
        if (!ioBase[i]->begin()) return false;
        for (int j = 0; j < IO_EXPANDER_PIN_NUM; j++) {
            ioBase[i]->digitalWrite(j, HIGH);
        }
    }
    return true;
}

KeedBase *KeedWelcomingLight::switchChannel() {
    switch (ioChannel) {
        case 8: return new Keed8Channel();
        case 16: return new Keed16Channel();
        default: break;
    }
}

IOExpander *KeedWelcomingLight::getIoExpander(uint8_t index) {
    return ioBase[index];
}

IOExpander **KeedWelcomingLight::getIoExpanderPtr() {
    return ioBase;
}

IOExpander &KeedWelcomingLight::getIoExpanderRef(uint8_t index) {
    return *(ioBase[index]);
}

void KeedWelcomingLight::showInfo() {
    KEED_DEBUG_PRINTER("IOEXNUM => " + String(ioNum));
    KEED_DEBUG_PRINTER("CHANNEL => " + String(ioChannel));
    KEED_DEBUG_PRINTER("VERSION => " + String(ioVersion));
}
