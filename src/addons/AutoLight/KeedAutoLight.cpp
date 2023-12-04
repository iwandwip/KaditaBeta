/*
 *  KeedAutoLight.cpp
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#include "KeedAutoLight.h"

KeedAutoLight::KeedAutoLight()
        : ioBase(nullptr),
          keedBase(nullptr) {}

KeedAutoLight::~KeedAutoLight() {
    free(ioBase);
    free(keedBase);
    ioBase = nullptr;
    keedBase = nullptr;
}

cfg_error_t KeedAutoLight::init(configuration_t _cfg) {
    cfg = _cfg;
    if (isUsingExpander()) {
        if (!beginExpander()) return INITIALIZE_ERROR;
        keedBase = switchChannel();
    } else {

    }
//    showInfo();
    return INITIALIZE_OK;
}

void KeedAutoLight::runAutoLight() {
    if (isUsingExpander()) keedBase->run(ioBase, cfg.io_size);
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
    for (int i = 0; i < cfg.io_size; i++) {
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
    switch (cfg.channel) {
        case 16: return new Keed16Channel();
    }
    return nullptr;
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

bool KeedAutoLight::isUsingExpander() const {
    return cfg.pin_ptr == nullptr && cfg.pin_size == 0;
}

void KeedAutoLight::showInfo() {
    Serial.print("| version: ");
    Serial.print(cfg.version);
    Serial.print("| channel: ");
    Serial.print(cfg.channel);
    Serial.print("| io_size: ");
    Serial.print(cfg.io_size);
    Serial.print("| isUsingExpander(): ");
    Serial.print(isUsingExpander());
    Serial.print("| pin_ptr: ");
    Serial.print(cfg.pin_ptr == nullptr ? "NULL" : "NOT NULL");
    Serial.print("| pin_size: ");
    Serial.print(cfg.pin_size);
    Serial.println();
}
