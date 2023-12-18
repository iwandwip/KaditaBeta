/*
 *  KeedDisplay.cpp
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#include "KeedDisplay.h"

KeedDisplay::KeedDisplay(uint32_t _channel, uint8_t _address)
        : channel(_channel), address(_address) {
    display = new Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
    if (!display->begin(SSD1306_SWITCHCAPVCC, address)) {
        Serial.println("SSD1306 allocation failed");
        return;
    }
    display->display();
    delay(200);
    display->clearDisplay();
    setPos();
}

void KeedDisplay::write(uint8_t _pin, uint8_t _state) {
    display->fillRect(pos[_pin][0], pos[_pin][1], WIDTH, HEIGHT, _state ? SSD1306_WHITE : SSD1306_INVERSE);
    display->display();
}

void KeedDisplay::setPos() {
    switch (channel) {
        case 24: pos = (uint8_t(*)[2]) POS_24;
            break;
        case 32: pos = (uint8_t(*)[2]) POS_32;
            break;
    }
}

void KeedDisplay::fillBorder() {
    for (int i = 0; i < channel; ++i) {
        display->drawCircle(pos[i][0], pos[i][1], 2, SSD1306_WHITE);
    }
}


void KeedDisplay::clear() {
    display->clearDisplay();
}

void KeedDisplay::off() {
    for (int i = 0; i < channel; ++i) {
        display->drawRect(pos[i][0], pos[i][1], WIDTH, HEIGHT, SSD1306_INVERSE);
        // display->fillCircle(pos[i][0], pos[i][1], 2, SSD1306_INVERSE);
    }
}

void KeedDisplay::on() {
    for (int i = 0; i < channel; ++i) {
        display->drawRect(pos[i][0], pos[i][1], WIDTH, HEIGHT, SSD1306_WHITE);
        // display->fillCircle(pos[i][0], pos[i][1], 2, SSD1306_WHITE);
    }
}
