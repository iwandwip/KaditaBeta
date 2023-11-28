/*
 *  swap-serial.h
 *
 *  serial communication lib
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef SWAP_SERIAL_COM_H
#define SWAP_SERIAL_COM_H

#if defined(ESP8266) || defined(ESP32)

#include "Arduino.h"
#include "HardwareSerial.h"

class SwapSerial {
private:
    HardwareSerial *serialPtr;
    String dataSend;
    uint32_t sendTime;
    String parseStr(String data, char separator[], int index);

public:
    SwapSerial();
    void begin(HardwareSerial *_serialPtr = &Serial2,
               long baud = 9600,
               SerialConfig cfg = SERIAL_8N1,
               uint8_t rxPin = 13,
               uint8_t txPin = 15);

    template<typename T>
    void addData(T newData, const char *separator = ";") {
        dataSend += String(newData);
        dataSend += separator;
    }

    void clearData();
    void sendData();
    void sendDataCb(void (*callback)());
    void sendDataAsync(uint32_t _time = 500);
    void sendDataAsyncCb(uint32_t _time = 500, void (*callback)() = nullptr);
    void receive(void (*callback)(String));
    float getData(String data, uint8_t index = 0);
    String getStrData(String data, uint8_t index = 0);
};

#endif // defined(ESP8266) || defined(ESP32)
#endif // SWAP_SERIAL_COM_H
