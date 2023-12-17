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
    if (isUsingExpander()) {
        if (!beginExpander()) return INITIALIZE_ERROR;
    }
    keedBase = getChannel();
    if (keedBase == nullptr) return INITIALIZE_ERROR;
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

KeedBase *KeedAutoLight::getChannel() {
    if (!cfg.custom) return new KeedBaseChannel(isUsingExpander());
    if (isUsingExpander()) {
        switch (getIndex()) {
            case AUTO_LIGHT_CUSTOM_0: return nullptr;
            case AUTO_LIGHT_CUSTOM_1: return nullptr;
            case AUTO_LIGHT_CUSTOM_2: return nullptr;
            case AUTO_LIGHT_CUSTOM_3: return nullptr;
        }
    } else {
        switch (cfg.pin_size) {
            case 3: return new Keed3ChannelStrobe();
        }
    }
    return nullptr;
}

int KeedAutoLight::getIndex() {
    for (int i = AUTO_LIGHT_CUSTOM_0; i < AUTO_LIGHT_CUSTOM_NUM; ++i) {
#if defined(ESP32)
        if (strchx(strconv(EEPROM.readString(0)), custom_keed_t[i])) {
            return i;
        }
#else
#endif
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
    static byte hexArray[CUSTOM_LEN];
    for (int i = 0; i < input.length(); i++) {
        hexArray[i] = input[i];
    }
    return hexArray;
}

bool strchx(const byte *a, const byte *b) {
    for (int i = 0; i < 20; i++) {
        if (a[i] != b[i]) return false;
    }
    return true;
}
