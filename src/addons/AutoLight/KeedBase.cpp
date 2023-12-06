/*
 *  KeedBase.cpp
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#include "KeedBase.h"

void KeedBase::setInterruptConfig(interrupt_t _cfg) {
    /*not implemented yet*/
}

void KeedBase::changeModes() {
    /*not implemented yet*/
}

void interrupt_t::attachInterrupt(uint8_t _pin, void (*_callback)()) {
    pin = _pin;
    isrCallback = _callback;
}