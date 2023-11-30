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
}

cfg_error_t KeedWelcomingLight::init(uint8_t io_expander_num, uint8_t version) {
    switch (io_expander_num) {
        case 2:
            break;
        case 3:
            break;
        default:
            break;
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
