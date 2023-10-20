/*
 *  sensor-module.cpp
 *
 *  sensor module c
 *  Created on: 2023. 4. 3
 */

#include "HardwareSerial.h"
#include "sensor-module.h"

SensorModule::SensorModule()
        : base(nullptr) {
}

SensorModule::~SensorModule() {
    if (base != nullptr) {
        free(base);
        base = nullptr;
        len = 0;
    }
}

void SensorModule::init(void (*initializeCallback)(void)) {
    if (initializeCallback != nullptr) initializeCallback();
    if (base == nullptr) return;
    for (uint8_t i = 0; i < len; i++) {
        base[i]->init();
    }
}

void SensorModule::update(void (*updateCallback)(void)) {
    if (updateCallback != nullptr) updateCallback();
    if (base == nullptr) return;
    for (uint8_t i = 0; i < len; i++) {
        base[i]->update();
    }
}

void SensorModule::addModule(BaseSens *sensModule) {
    BaseSens **newBase = (BaseSens **) realloc(base, (len + 1) * sizeof(BaseSens *));  // increase length by 1
    if (newBase == nullptr) {
        Serial.println("Memory Allocation Failed !");
        return;
    }
    base = newBase;
    base[len] = sensModule;  // assign to correct index
    len++;
}

void SensorModule::removeModule(uint8_t index) {
    if (base == nullptr || index >= len) return;
    delete base[index];
    for (uint8_t i = index; i < len - 1; i++) {
        base[i] = base[i + 1];
    }
    len--;
    BaseSens **newBase = (BaseSens **) realloc(base, len * sizeof(BaseSens *));
    if (newBase != nullptr) {
        base = newBase;
    }
}

BaseSens &SensorModule::getModule(uint8_t index) {
    return *(base[index]);
}

BaseSens *SensorModule::getModulePtr(uint8_t index) {
    if (base == nullptr || index >= len) return nullptr;
    return base[index];
}

void SensorModule::clearModules() {
    if (base == nullptr) return;
    for (uint8_t i = 0; i < len; i++) {
        delete base[i];
    }
    free(base);
    base = nullptr;
    len = 0;
}

uint8_t SensorModule::getModuleCount() {
    return len;
}

void SensorModule::setModule(uint8_t index, BaseSens *sensModule) {
    if (base == nullptr || index >= len) return;
    delete base[index];
    base[index] = sensModule;
}

void SensorModule::swapModules(uint8_t index1, uint8_t index2) {
    if (base == nullptr || index1 >= len || index2 >= len) return;
    BaseSens *temp = base[index1];
    base[index1] = base[index2];
    base[index2] = temp;
}

bool SensorModule::isModulePresent(BaseSens *sensModule) {
    if (base == nullptr) return false;
    for (uint8_t i = 0; i < len; i++) {
        if (base[i] == sensModule) {
            return true;
        }
    }
    return false;
}

bool SensorModule::isModulePresent(uint8_t index) {
    if (base == nullptr || index >= len) return false;
    return true;
}