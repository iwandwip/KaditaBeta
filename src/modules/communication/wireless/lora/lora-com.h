/*
 *  lora-com.h
 *
 *  lora communication handler
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef LORA_COM_H
#define LORA_COM_H

#include "Arduino.h"
#include "SPI.h"
#include "LoRa.h"

#define NONE ""
#define SEPARATOR ";"

typedef struct {
    uint8_t cs;  // ns ss
    uint8_t rst;
    uint8_t irq;

    uint8_t count;
    uint8_t addr;
    uint8_t destination;
    char outgoing[250];
} lora_config;

// void onReceive(int packetSize);

class LoRaModule {
private:
    String data;
    uint32_t sendTime;
    String parseStr(String data, char separator[], int index);
public:
    LoRaModule();
    ~LoRaModule();
    bool init(long frequency = 915E6);
    bool init(uint8_t ss, uint8_t reset, uint8_t dio0, long frequency = 915E6);

    template<typename T>
    void addData(T value) {
        data += String(value);
        data += SEPARATOR;
    }

    void clearData();
    void sendData(uint32_t __time = 500);
    void receive(void (*onReceive)(String) = nullptr);
    float getData(String data, uint8_t index = 0);
    String getStrData(String data, uint8_t index = 0);
};

#endif  // LORA_COM_H