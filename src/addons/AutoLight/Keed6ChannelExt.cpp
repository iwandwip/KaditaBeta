/*
 *  Keed6ChannelExt.cpp
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#include "Keed6ChannelExt.h"

Keed6ChannelExt::Keed6ChannelExt()
        : sequence(0), taskTemp(nullptr),
          sequences{&Keed6ChannelExt::taskSequence0, &Keed6ChannelExt::taskSequence1,
                    &Keed6ChannelExt::taskSequence2, &Keed6ChannelExt::taskSequence3} {}

void Keed6ChannelExt::init() {

}

void Keed6ChannelExt::update() {
    taskTemp = sequences[sequence];
    (this->*taskTemp)();
    if (sequence < 3) sequence++;
    else sequence = 0;
}

void Keed6ChannelExt::run(IOExpander **_ioBase, uint8_t _ioNum) {
    update();
}

void Keed6ChannelExt::run(configuration_t _cfg) {
    cfg = _cfg;
    update();
}

void (Keed6ChannelExt::*Keed6ChannelExt::getSequence(uint8_t index))() {
    return sequences[index];
}

void Keed6ChannelExt::taskSequence0() {
    for (int i = 120; i >= 20; i -= 4) {
        blink(i);
    }
}

void Keed6ChannelExt::taskSequence1() {
    for (int i = 40; i >= 20; i -= 4) {
        snake(i);
    }
}

void Keed6ChannelExt::taskSequence2() {
    for (int i = 40; i >= 20; i -= 4) {
        snakeReverse(i);
    }
}

void Keed6ChannelExt::taskSequence3() {
    for (int i = 40; i >= 16; i -= 8) {
        snake(i);
        snakeReverse(i);
    }
}

void Keed6ChannelExt::blink(uint32_t _delay) {
    for (int i = 0; i < cfg.pin_size; i++) {
        digitalWrite(cfg.pin_ptr[i], LOW);
    }
    for (int i = 0; i < cfg.pin_size; i++) {
        digitalWrite(cfg.pin_ptr[i], LOW);
    }
    delay(_delay);
    for (int i = 0; i < cfg.pin_size; i++) {
        digitalWrite(cfg.pin_ptr[i], HIGH);
    }
    for (int i = 0; i < cfg.pin_size; i++) {
        digitalWrite(cfg.pin_ptr[i], HIGH);
    }
    delay(_delay);
}

void Keed6ChannelExt::snake(uint32_t _delay) {
    for (int j = 0; j < cfg.pin_size; j++) {
        digitalWrite(cfg.pin_ptr[j], LOW);
        delay(_delay);
    }
    for (int j = 0; j < cfg.pin_size; j++) {
        digitalWrite(cfg.pin_ptr[j], HIGH);
        delay(_delay);
    }
}

void Keed6ChannelExt::snakeReverse(uint32_t _delay) {
    for (int j = cfg.pin_size; j > 0; j--) {
        digitalWrite(cfg.pin_ptr[j] - 1, LOW);
        delay(_delay);
    }
    for (int j = cfg.pin_size; j > 0; j--) {
        digitalWrite(cfg.pin_ptr[j] - 1, HIGH);
        delay(_delay);
    }
}
