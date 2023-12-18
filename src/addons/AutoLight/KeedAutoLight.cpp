/*
 *  KeedAutoLight.cpp
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#include "KeedAutoLight.h"

const byte *strconv(String input);
bool strchx(const byte *a, const byte *b);

KeedAutoLight::KeedAutoLight()
        : ioBase(nullptr),
          keedBase(nullptr) {}

KeedAutoLight::~KeedAutoLight() {
    free(ioBase);
    free(keedBase);
    ioBase = nullptr;
    keedBase = nullptr;
}

cfg_error_t KeedAutoLight::setChannel(configuration_t _cfg) {
    cfg = _cfg;
    keedBase = getChannel();
    if (keedBase == nullptr) return INITIALIZE_ERROR;
    if (isUsingExpander()) {
        if (!beginExpander()) return INITIALIZE_ERROR;
    }
    return INITIALIZE_OK;
}

cfg_error_t KeedAutoLight::init() {
    if (keedBase == nullptr) return INITIALIZE_ERROR;
    if (isUsingExpander()) {
        cfg.pin_size = cfg.channel;
        cfg.pin_ptr = new uint8_t[cfg.pin_size];
        for (uint8_t i = 0; i < cfg.pin_size; ++i) {
            cfg.pin_ptr[i] = i;
        }
    }
    keedBase->init(ioBase, cfg);
    return INITIALIZE_OK;
}

void KeedAutoLight::runAutoLight() {
    if (keedBase == nullptr) return;
    keedBase->run();
}

void KeedAutoLight::setInterruptConfig(interrupt_t _cfg) {
    keedBase->setInterruptConfig(_cfg);
}

void KeedAutoLight::changeModes() {
    keedBase->changeModes();
}

void KeedAutoLight::setBaseDelay(uint32_t _time) {
    keedBase->setBaseDelay(_time);
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
        if (!cfg.custom) addIoExpander(new IOExpander(i2c_address_arr_t[i]));
        else addIoExpander(new IOExpander(cfg.i2c_ptr[i]));
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

KeedBase *KeedAutoLight::getChannel() {
    if (!cfg.custom) return new KeedBaseChannel(isUsingExpander());
    if (isUsingExpander()) {
        switch (getIndex()) {
            case AUTO_LIGHT_CUSTOM_0: return new KeedBaseChannel(true);
            case AUTO_LIGHT_CUSTOM_1: {
                cfg.channel = 16;
                cfg.io_size = 2;
                cfg.setAddress(cfg.io_size, 0x24, 0x20);
                return new KeedBaseChannel(true);
            }
            case AUTO_LIGHT_CUSTOM_3: {
                cfg.channel = 16;
                cfg.io_size = 2;
                cfg.setAddress(cfg.io_size, 0x20, 0x24);
                return new KeedBaseChannel(true);
            }
        }
    } else {
        switch (getIndex()) {
            case AUTO_LIGHT_CUSTOM_2: return new Keed3ChannelStrobe();
        }
    }
    return nullptr;
}

int KeedAutoLight::getIndex() {
    for (int i = AUTO_LIGHT_CUSTOM_0; i < AUTO_LIGHT_CUSTOM_NUM; ++i) {
        if (strchx(strconv(readMEM(0)), custom_keed_t[i])) return i;
    }
    return -1;
}

bool KeedAutoLight::isUsingExpander() const {
    return cfg.pin_ptr == nullptr && cfg.pin_size == 0;
}

IOExpander *KeedAutoLight::getIoExpander(uint8_t index) {
    return ioBase[index];
}

IOExpander &KeedAutoLight::getIoExpanderRef(uint8_t index) {
    return *(ioBase[index]);
}

IOExpander **KeedAutoLight::getIoExpanderPtr() {
    return ioBase;
}

KeedBase *KeedAutoLight::getChannelClassPtr() {
    return keedBase;
}

KeedBase &KeedAutoLight::getChannelClass() {
    return *(keedBase);
}

void KeedAutoLight::showInfo() {
    Serial.print("| SERIAL-KEY: ");
    Serial.print(readMEM(0));
    Serial.print("| INDEX: ");
    Serial.print(getIndex());
    Serial.println();
    Serial.print("| version: ");
    Serial.print(cfg.version);
    Serial.print("| channel: ");
    Serial.print(cfg.channel);
    Serial.print("| io_size: ");
    Serial.print(cfg.io_size);
    Serial.print("| isUsingExpander(): ");
    Serial.print(isUsingExpander() ? "YES" : "NO");
    Serial.print("| pin_ptr: ");
    Serial.print(cfg.pin_ptr == nullptr ? "NULL" : "NOT NULL");
    Serial.print("| pin_size: ");
    Serial.print(cfg.pin_size);
    Serial.println();
}

const byte *strconv(String input) {
    static byte hex_arr[CUSTOM_LEN];
    for (int i = 0; i < input.length(); i++) {
        hex_arr[i] = input[i];
    }
    return hex_arr;
}

bool strchx(const byte *a, const byte *b) {
    for (int i = 0; i < 20; i++) {
#if defined(ESP32)
        if (a[i] != b[i]) return false;
#else
        if (a[i] != pgm_read_byte(&(b[i]))) return false;
#endif
    }
    return true;
}
