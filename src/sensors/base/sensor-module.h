/*  
 *  sensor-module.h
 *
 *  sensor module header
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef SENSOR_MODULE_H
#define SENSOR_MODULE_H

#include "Arduino.h"
#include "HardwareSerial.h"
#include "SPI.h"

typedef enum {
    SENS_RET_RAW_DATA,
    SENS_RET_FILTERED_DATA,
    SENS_RET_OFFSET_DATA,
    SENS_RET_ACT_DATA,
    SENS_RET_AVG_DATA,
    SENS_RET_TOTAL_DATA,
} sens_ret_index_t;

class BaseSens {
public:
    /*pure virtual function*/
    virtual void init() = 0;
    virtual void update() = 0;
#if defined(EXTENDED_FUNCTION_VTABLE)
    virtual void debug() {
        /*updated soon*/
    }
    virtual void calibrate() {
        /*updated soon*/
    }
#endif

    virtual void getValue(float *output) {
        /*updated soon*/
    }

    virtual void getValue(int *output) {
        /*updated soon*/
    }

    virtual void getValue(char *output) {
        /*updated soon*/
    }

#if defined(EXTENDED_FUNCTION_VTABLE)
    virtual void setCallBack(void (*callbackFunc)()) {
        /* updated soon*/
    }
    virtual void count() {
        /*updated soon*/
    }
    virtual void reset() {
        /*updated soon*/
    }
#endif
    BaseSens &operator=(const BaseSens &) = default;
    BaseSens &operator=(BaseSens &&) = default;
};

class SensorModule {
private:
    BaseSens **base;
    uint8_t len = 0;
public:
    SensorModule();
    ~SensorModule();
    void init(void (*initialize)() = nullptr);
    void update(void (*update)() = nullptr);
    void debug(int _index = -1);
    static void loop(void (*loop)() = nullptr);
    void addModule(BaseSens *sensModule);
    void removeModule(uint8_t index);
    BaseSens *getModule(uint8_t index);
    void clearModules();
    uint8_t getModuleCount();
    void setModule(uint8_t index, BaseSens *sensModule);
    void swapModules(uint8_t index1, uint8_t index2);
    bool isModulePresent(BaseSens *sensModule);
    bool isModulePresent(uint8_t index);
};


#endif  // SENSOR_MODULE_H