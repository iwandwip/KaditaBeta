/*
 *  KeedAutoLight.cpp
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#include "KeedAutoLight.h"

KeedAutoLight::KeedAutoLight()
        : ioBase(nullptr),
          ioLen(0),
          ioChannel(0),
          ioVersion(0),
          ioNum(0),
          keedBase(nullptr) {}

KeedAutoLight::~KeedAutoLight() {
    free(ioBase);
    free(keedBase);
    ioBase = nullptr;
    keedBase = nullptr;
}

cfg_error_t KeedAutoLight::init(uint8_t io_expander_num, uint8_t channel, uint8_t version) {
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

void KeedAutoLight::runWelcomingLight() {
    keedBase->run(ioBase, ioNum);
}

void KeedAutoLight::addIoExpander(IOExpander *ioExpander) {
    IOExpander **newIoBase = (IOExpander **) realloc(ioBase, (ioLen + 1) * sizeof(IOExpander *));
    if (newIoBase == nullptr) {
        return;
    }
    ioBase = newIoBase;
    ioBase[ioLen] = ioExpander;
    ioLen++;
}

bool KeedAutoLight::beginExpander() {
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

KeedBase *KeedAutoLight::switchChannel() {
    switch (ioChannel) {
        case 16: return new Keed16Channel();
        default: break;
    }
}

IOExpander *KeedAutoLight::getIoExpander(uint8_t index) {
    return ioBase[index];
}

IOExpander **KeedAutoLight::getIoExpanderPtr() {
    return ioBase;
}

IOExpander &KeedAutoLight::getIoExpanderRef(uint8_t index) {
    return *(ioBase[index]);
}

void KeedAutoLight::showInfo() {
    KEED_DEBUG_PRINTER("IOEXNUM => " + String(ioNum));
    KEED_DEBUG_PRINTER("CHANNEL => " + String(ioChannel));
    KEED_DEBUG_PRINTER("VERSION => " + String(ioVersion));
}
