/*
 *  serial-com.cpp
 *
 *  serial communication c
 *  Created on: 2023. 4. 3
 */

#include "soft-serial.h"

#include "SoftwareSerial.h"

#define USING_SERIAL espSerial

SoftwareSerial USING_SERIAL(3, 2);

SerialCom::SerialCom() {
    dataSend = "";
    USING_SERIAL.begin(9600);
    USING_SERIAL.println();
}

void SerialCom::addData(const char *newData, const char *separator) {
    dataSend += newData;
    dataSend += separator;
}

void SerialCom::addData(float newData, const char *separator) {
    dataSend += String(newData);
    dataSend += separator;
}

void SerialCom::addData(int newData, const char *separator) {
    dataSend += String(newData);
    dataSend += separator;
}

void SerialCom::clearData() {
    dataSend = "";
}

void SerialCom::sendData(uint32_t __t) {
    if (millis() - sendTime >= __t) {
        sendTime = millis();
        USING_SERIAL.println(dataSend);
        // Serial.println(dataSend);
    }
}

void SerialCom::receive(void (*onReceive)(String)) {
    if (onReceive == nullptr) return;
    if (USING_SERIAL.available()) {
        char rxBuffer[250];
        uint8_t rxBufferPtr = 0;
        rxBuffer[rxBufferPtr++] = USING_SERIAL.read();
        while (1) {
            if (USING_SERIAL.available()) {
                rxBuffer[rxBufferPtr++] = USING_SERIAL.read();
                if (rxBuffer[rxBufferPtr - 1] == '\n') break;
            }
        }
        rxBuffer[rxBufferPtr] = 0;
        onReceive(String(rxBuffer));
    }
}

float SerialCom::getData(String data, uint8_t index) {
    return parseStr(data, ";", index).toFloat();
}

String SerialCom::getStrData(String data, uint8_t index) {
    return parseStr(data, ";", index);
}

String SerialCom::parseStr(String data, char separator[], int index) {
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