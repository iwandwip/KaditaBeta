/*
 *  Keed.cpp
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#include "Keed.h"

KeedWelcomingLight::KeedWelcomingLight()
        : ioLen(0), ioBase(nullptr) {}

KeedWelcomingLight::~KeedWelcomingLight() {
    free(ioBase);
    ioBase = nullptr;
}

cfg_error_t KeedWelcomingLight::init(uint8_t io_expander_num, uint8_t version) {
    for (int i = 0; i < io_expander_num; i++) {
        addIoExpander(new IOExpander(i2c_address_arr_t[i]));
    }
    for (int i = 0; i < ioLen; ++i) {
        for (int j = 0; j < IO_EXPANDER_PIN_NUM; ++j) {
            ioBase[i]->pinMode(j, OUTPUT);
        }
        if (!ioBase[i]->begin()) return INITIALIZE_ERROR;
    }
    return INITIALIZE_OK;
}

void KeedWelcomingLight::addIoExpander(IOExpander *ioExpander) {
    IOExpander **newIoBase = (IOExpander **) realloc(ioBase, (ioLen + 1) * sizeof(IOExpander *));
    if (newIoBase == nullptr) {
        Serial.println("Memory Allocation Failed !");
        return;
    }
    ioBase = newIoBase;
    ioBase[ioLen] = ioExpander;
    ioLen++;
}
