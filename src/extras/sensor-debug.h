/*
 *  sensor-debug.h
 *
 *  sensor debug header
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef SENSOR_DEBUG_H
#define SENSOR_DEBUG_H

#include "Arduino.h"
#include "HardwareSerial.h"
#include "SPI.h"

// for excel (PLX-DAQ) / LabView
class SensorDebug {
private:
    String label;
    String data;
    char *separator;
    uint8_t labelCount;
    uint8_t dataCount;
    uint32_t send_tm;
    bool send2Sheet;

public:
    SensorDebug();
    void init(bool isSendToSheet = true);
    void addLabel(String _label, bool with_separator = true);
    template<typename T>
    void addData(T value, bool with_separator = true);
    void sendLabel();
    void sendData(uint32_t __t = 1000);
    void clearLabel();
    void clearData();
    void setLabel(String _label);
    void setData(String _data);
    void setSeparator(char _sep[]);
    void setSendDataCallback(void (*sendCallback)(void));
    String getLabel();
    String getData();
    void reset();
};

#endif // SENSOR_DEBUG_H