/*
 *  swap-serial.cpp
 *
 *  serial communication c
 *  Created on: 2023. 4. 3
 */

#include "swap-serial.h"

#if defined(ESP8266) || defined(ESP32)

SwapSerial::SwapSerial() {
    clearData();
}

void SwapSerial::begin(HardwareSerial *_serialPtr,
                       long baud,
                       SerialConfig cfg,
                       uint8_t rxPin,
                       uint8_t txPin) {
    serialPtr = _serialPtr;
    serialPtr->begin(baud, cfg, rxPin, txPin);
    serialPtr->println();
}

void SwapSerial::clearData() {
    dataSend = "";
}

void SwapSerial::sendData() {
    serialPtr->println(dataSend);
}

void SwapSerial::sendDataCb(void (*callback)()) {
    serialPtr->println(dataSend);
    callback();
}

void SwapSerial::sendDataAsync(uint32_t _time) {
    if (millis() - sendTime >= _time) {
        sendTime = millis();
        serialPtr->println(dataSend);
    }
}

void SwapSerial::sendDataAsyncCb(uint32_t _time, void (*callback)()) {
    if (millis() - sendTime >= _time) {
        sendTime = millis();
        serialPtr->println(dataSend);
        callback();
    }
}

void SwapSerial::receive(void (*callback)(String)) {
    if (callback == nullptr) return;
    if (serialPtr->available()) {
        char rxBuffer[250];
        uint8_t rxBufferPtr = 0;
        rxBuffer[rxBufferPtr++] = serialPtr->read();
        while (1) {
            if (serialPtr->available()) {
                rxBuffer[rxBufferPtr++] = serialPtr->read();
                if (rxBuffer[rxBufferPtr - 1] == '\n') break;
            }
        }
        rxBuffer[rxBufferPtr] = 0;
        String dataCb = String(rxBuffer);
        dataCb.replace("\n", "");
        callback(dataCb);
    }
}

float SwapSerial::getData(String data, uint8_t index) {
    return parseStr(data, ";", index).toFloat();
}

String SwapSerial::getStrData(String data, uint8_t index) {
    return parseStr(data, ";", index);
}

String SwapSerial::parseStr(String data, char separator[], int index) {
    int found = 0;
    int strIndex[] = {0, -1};
    int maxIndex = data.length() - 1;
    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator[0] || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i + 1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

#endif