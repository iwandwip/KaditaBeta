/*
 *  soft-serial.h
 *
 *  serial communication lib
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef SOFT_SERIAL_COM_H
#define SOFT_SERIAL_COM_H

#include "Arduino.h"
#include "SoftwareSerial.h"

class SoftSerial {
private:
    SoftwareSerial *serialPtr;
    String dataSend;
    uint32_t sendTime;
    String parseStr(String data, char separator[], int index);

public:
    SoftSerial();
    void begin(SoftwareSerial *_serialPtr, long baud = 9600);
    void begin(uint8_t rxPin, uint8_t txPin, long baud = 9600);

    template<typename T>
    void addData(T newData, const char *separator = ";") {
        dataSend += String(newData);
        dataSend += separator;
    }

    void clearData();
    void sendData(uint32_t _time = 500);
    void receive(void (*onReceive)(String) = nullptr);
    float getData(String data, uint8_t index = 0);
    String getStrData(String data, uint8_t index = 0);
};

#endif
