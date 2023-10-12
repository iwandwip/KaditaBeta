/*
 *  serial-com.h
 *
 *  serial communication lib
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef SERIAL_COM_H
#define SERIAL_COM_H

#include "Arduino.h"
#include "HardwareSerial.h"
#include "WString.h"
#include "stdint.h"

class SerialCom {
private:
    String dataSend;
    uint32_t sendTime;
    String parseStr(String data, char separator[], int index);

public:
    SerialCom();
    void addData(const char *newData, const char *separator = ";");
    void addData(float newData, const char *separator = ";");
    void addData(int newData, const char *separator = ";");
    void clearData();
    void sendData(uint32_t __t = 500);
    void receive(void (*onReceive)(String) = nullptr);
    float getData(String data, uint8_t index = 0);
    String getStrData(String data, uint8_t index = 0);
};

#endif
