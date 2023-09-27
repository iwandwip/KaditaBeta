/*
 *  sensor-debug.cpp
 *
 *  sensor debug c
 *  Created on: 2023. 4. 3
 */

#include "HardwareSerial.h"
#include "sensor-debug.h"
#include "Arduino.h"

SensorDebug::SensorDebug()
        : label("LABEL"), data("DATA"), labelCount(0), dataCount(0), send2Sheet(true), separator(",") {
}

void SensorDebug::init(bool isSendToSheet) {
    this->send2Sheet = isSendToSheet;
    if (!send2Sheet) {
        label = "";
        data = "";
    } else {
        SPI.begin();
        Serial.println("CLEARSHEET");
    }
}

void SensorDebug::addLabel(String _label, bool with_separator) {
    if (with_separator && label != "") label += separator;
    label += _label;
    labelCount++;
}

// gcc ver < C++17 (C++11 / C++14)
template<typename T>
void SensorDebug::addData(T value, bool with_separator) {
    if (with_separator && data != "") data += separator;
    data += String(value);
    dataCount++;
}

void SensorDebug::sendLabel() {
    Serial.println(label);
}

void SensorDebug::sendData(uint32_t __t) {
    if (millis() - send_tm >= __t) {
        if (labelCount != dataCount) Serial.println("Data and Label len didn't match");
        else {
            Serial.println(data);
        }
        send_tm = millis();
    }
}

void SensorDebug::clearLabel() {
    if (!send2Sheet) {
        labelCount = 0;
        label = "";
    } else {
        labelCount = 0;
        label = "LABEL";
    }
}

void SensorDebug::clearData() {
    if (!send2Sheet) {
        dataCount = 0;
        data = "";
    } else {
        dataCount = 0;
        data = "DATA";
    }
}

void SensorDebug::setLabel(String _label) {
    label = _label;
}

void SensorDebug::setData(String _data) {
    data = _data;
}

void SensorDebug::setSeparator(char _sep[]) {
    separator = _sep;
}

void SensorDebug::setSendDataCallback(void (*sendCallback)(void)) {
    sendCallback();
}

String SensorDebug::getLabel() {
    return label;
}

String SensorDebug::getData() {
    return data;
}

void SensorDebug::reset() {
    label = "LABEL";
    data = "DATA";
    labelCount = 0;
    dataCount = 0;
    Serial.println("CLEARSHEET");
}