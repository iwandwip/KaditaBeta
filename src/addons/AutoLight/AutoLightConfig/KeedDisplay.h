/*
 *  KeedDisplay.h
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef KEED_DISPLAY_H
#define KEED_DISPLAY_H

#include "Arduino.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "KeedDisplayPos.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

class KeedDisplay {
private:
    Adafruit_SSD1306 *display;
    uint8_t size;
    uint8_t channel;
    uint8_t address;
    uint8_t (*pos)[2];

    void setPos();
public:
    KeedDisplay(uint32_t _channel, uint8_t _address);
    void write(uint8_t _pin, uint8_t _state);
    void fillBorder();
    void clear();
    void off();
    void on();
};

#endif // KEED_DISPLAY_H