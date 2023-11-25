/*
 *  hard-serial.cpp
 *
 *  serial communication c
 *  Created on: 2023. 4. 3
 */

#include "hard-serial.h"

HardSerial::HardSerial() {
    clearData();
}

void HardSerial::begin(HardwareSerial *_serialPtr, long baud) {
    serialPtr = _serialPtr;
    serialPtr->begin(baud);
    serialPtr->println();
}

void HardSerial::clearData() {
    dataSend = "";
}

void HardSerial::sendData() {
    serialPtr->println(dataSend);
}

void HardSerial::sendDataAsync(uint32_t _time) {
    if (millis() - sendTime >= _time) {
        sendTime = millis();
        serialPtr->println(dataSend);
    }
}

void HardSerial::sendDataAsyncCb(uint32_t _time, void (*onReceive)()) {
    if (millis() - sendTime >= _time) {
        sendTime = millis();
        serialPtr->println(dataSend);
        onReceive();
    }
}

void HardSerial::receive(void (*onReceive)(String)) {
    if (onReceive == nullptr) return;
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
        onReceive(dataCb);
    }
}

float HardSerial::getData(String data, uint8_t index) {
    return parseStr(data, ";", index).toFloat();
}

String HardSerial::getStrData(String data, uint8_t index) {
    return parseStr(data, ";", index);
}

String HardSerial::parseStr(String data, char separator[], int index) {
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