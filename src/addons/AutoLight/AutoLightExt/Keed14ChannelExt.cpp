/*
 *  Keed14ChannelExt.cpp
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#include "Keed14ChannelExt.h"

#define setHigh(...) setStateHigh(__VA_ARGS__, -1)
#define setLow(...) setStateLow(__VA_ARGS__, -1)

Keed14ChannelExt::Keed14ChannelExt()
        : sequence(0), ioTimer(40), taskTemp(nullptr),
          sequences{&Keed14ChannelExt::taskSequenceOFF, &Keed14ChannelExt::taskSequence1,
                    &Keed14ChannelExt::taskSequence2, &Keed14ChannelExt::taskSequenceON} {}

void Keed14ChannelExt::init() {
    pinMode(isr.pin, INPUT_PULLUP);
#if defined(ESP8266)
#elif defined(ESP32)
#else
    attachInterrupt(digitalPinToInterrupt(isr.pin), isr.isrCallback, RISING);
#endif
    taskTemp = sequences[sequence];
}

void Keed14ChannelExt::update() {
    if (isr.pressed) isr.pressed = false;
    (this->*taskTemp)();
}

void Keed14ChannelExt::run(IOExpander **_ioBase, uint8_t _ioNum) {
    update();
}

void Keed14ChannelExt::run(configuration_t _cfg) {
    cfg = _cfg;
    update();
}

void Keed14ChannelExt::setInterruptConfig(interrupt_t _cfg) {
    isr = _cfg;
}

void Keed14ChannelExt::changeModes() {
    if (millis() - isrTimer >= 250) {
        sequence = (sequence < 3) ? sequence + 1 : 0;
        taskTemp = sequences[sequence];
        isr.num++;
        isr.pressed = true;
        isrTimer = millis();
    }
}

void Keed14ChannelExt::setBaseDelay(uint32_t _time) {
    ioTimer = _time;
}

void (Keed14ChannelExt::*Keed14ChannelExt::getSequence(uint8_t index))() {
    return sequences[index];
}

void Keed14ChannelExt::taskSequence1() {
    on();
    delay(ioTimer);
    off();
    delay(ioTimer);
}

void Keed14ChannelExt::taskSequence2() {
    snake(ioTimer);
    snakeReverse(ioTimer);
}

void Keed14ChannelExt::taskSequenceON() {
    on();
}

void Keed14ChannelExt::taskSequenceOFF() {
    off();
}

void Keed14ChannelExt::sleep(uint32_t _time) {
    if (isr.pressed) return;
    delay(_time);
}

void Keed14ChannelExt::blink(uint32_t _time) {
    for (int i = 0; i < cfg.pin_size; i++) {
        set(cfg.pin_ptr[i], HIGH);
    }
    sleep(_time);
    for (int i = 0; i < cfg.pin_size; i++) {
        set(cfg.pin_ptr[i], LOW);
    }
    sleep(_time);
}

void Keed14ChannelExt::snake(uint32_t _time) {
    for (int j = 0; j < cfg.pin_size; j++) {
        set(cfg.pin_ptr[j], HIGH);
        sleep(_time);
    }
    for (int j = 0; j < cfg.pin_size; j++) {
        set(cfg.pin_ptr[j], LOW);
        sleep(_time);
    }
}

void Keed14ChannelExt::snakeReverse(uint32_t _time) {
    for (int j = cfg.pin_size - 1; j >= 0; j--) {
        set(cfg.pin_ptr[j], HIGH);
        sleep(_time);
    }
    for (int j = cfg.pin_size - 1; j >= 0; j--) {
        set(cfg.pin_ptr[j], LOW);
        sleep(_time);
    }
}

void Keed14ChannelExt::set(uint8_t _pin, uint8_t _state) {
    if (cfg.reverse) digitalWrite(_pin, !_state);
    else digitalWrite(_pin, _state);
}

void Keed14ChannelExt::setStateHigh(int index, ...) {
    for (int i = 0; i < cfg.pin_size; i++) {
        set(cfg.pin_ptr[i], LOW);
    }
    va_list args;
    va_start(args, index);
    int currentIndex = index;
    while (currentIndex != -1) {
        set(cfg.pin_ptr[currentIndex], HIGH);
        currentIndex = va_arg(args, int);
    }
    va_end(args);
}

void Keed14ChannelExt::setStateLow(int index, ...) {
    for (int i = 0; i < cfg.pin_size; i++) {
        set(cfg.pin_ptr[i], LOW);
    }
    va_list args;
    va_start(args, index);
    int currentIndex = index;
    while (currentIndex != -1) {
        set(cfg.pin_ptr[currentIndex], LOW);
        currentIndex = va_arg(args, int);
    }
    va_end(args);
}

void Keed14ChannelExt::off() {
    for (int i = 0; i < cfg.pin_size; i++) {
        set(cfg.pin_ptr[i], LOW);
    }
}

void Keed14ChannelExt::on() {
    for (int i = 0; i < cfg.pin_size; i++) {
        set(cfg.pin_ptr[i], HIGH);
    }
}

