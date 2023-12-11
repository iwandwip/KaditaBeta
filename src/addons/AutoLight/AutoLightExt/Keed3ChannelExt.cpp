/*
 *  Keed3ChannelExt.cpp
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#include "Keed3ChannelExt.h"

#define setHigh(...) setStateHigh(__VA_ARGS__, -1)
#define setLow(...) setStateLow(__VA_ARGS__, -1)

Keed3ChannelExt::Keed3ChannelExt()
        : sequence(0), ioTimer(40), taskTemp(nullptr),
          sequences{&Keed3ChannelExt::taskSequenceOFF, &Keed3ChannelExt::taskSequence1,
                    &Keed3ChannelExt::taskSequence2, &Keed3ChannelExt::taskSequence3} {}

void Keed3ChannelExt::init() {
    pinMode(isr.pin, INPUT_PULLUP);
#if defined(ESP8266)
#elif defined(ESP32)
    attachInterrupt(isr.pin, isr.isrCallback, RISING);
#else
    attachInterrupt(digitalPinToInterrupt(isr.pin), isr.isrCallback, RISING);
#endif
    taskTemp = sequences[sequence];
    off();
}

void Keed3ChannelExt::update() {
    if (isr.pressed) isr.pressed = false;
    (this->*taskTemp)();
}

void Keed3ChannelExt::run(IOExpander **_ioBase, uint8_t _ioNum, configuration_t _cfg) {
    cfg = _cfg;
    update();
}

void Keed3ChannelExt::setInterruptConfig(interrupt_t _cfg) {
    isr = _cfg;
}

void Keed3ChannelExt::changeModes() {
    if (millis() - isrTimer >= 250) {
        sequence = (sequence < 3) ? sequence + 1 : 0;
        taskTemp = sequences[sequence];
        isr.num++;
        isr.pressed = true;
        isrTimer = millis();
    }
}

void Keed3ChannelExt::setBaseDelay(uint32_t _time) {
    ioTimer = _time;
}

void (Keed3ChannelExt::*Keed3ChannelExt::getSequence(uint8_t index))() {
    return sequences[index];
}

void Keed3ChannelExt::taskSequence1() {
    for (int j = 0; j < 2; ++j) {
        for (int i = 0; i < 7; ++i) {
            set(cfg.pin_ptr[1], HIGH);
            sleep(ioTimer);
            set(cfg.pin_ptr[1], LOW);
            sleep(ioTimer);
        }
        off();
        sleep(ioTimer);
        for (int i = 0; i < 7; ++i) {
            set(cfg.pin_ptr[0], HIGH);
            set(cfg.pin_ptr[2], HIGH);
            sleep(ioTimer);
            set(cfg.pin_ptr[0], LOW);
            set(cfg.pin_ptr[2], LOW);
            sleep(ioTimer);
        }
        off();
        sleep(ioTimer);
    }
    off();
    for (int i = 0; i < 6; ++i) {
        blink(ioTimer * 4);
    }
}

void Keed3ChannelExt::taskSequence2() {
    for (int i = 0; i < 2; ++i) {
        snake(ioTimer * 2);
        snakeReverse(ioTimer * 2);
    }
    for (int j = 0; j < 3; ++j) {
        for (int i = 0; i < 8; ++i) {
            blink(ioTimer);
        }
        sleep(ioTimer * 4);
    }
}

void Keed3ChannelExt::taskSequence3() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 15; ++j) {
            set(cfg.pin_ptr[i], HIGH);
            sleep(ioTimer);
            set(cfg.pin_ptr[i], LOW);
            sleep(ioTimer);
        }
        sleep(ioTimer);
    }
}

void Keed3ChannelExt::taskSequenceOFF() {
    off();
}

void Keed3ChannelExt::sleep(uint32_t _time) {
    if (isr.pressed) return;
    delay(_time);
}

void Keed3ChannelExt::blink(uint32_t _time) {
    for (int i = 0; i < cfg.pin_size; i++) {
        set(cfg.pin_ptr[i], HIGH);
    }
    sleep(_time);
    for (int i = 0; i < cfg.pin_size; i++) {
        set(cfg.pin_ptr[i], LOW);
    }
    sleep(_time);
}

void Keed3ChannelExt::snake(uint32_t _time) {
    for (int j = 0; j < cfg.pin_size; j++) {
        set(cfg.pin_ptr[j], HIGH);
        sleep(_time);
    }
    for (int j = 0; j < cfg.pin_size; j++) {
        set(cfg.pin_ptr[j], LOW);
        sleep(_time);
    }
}

void Keed3ChannelExt::snakeReverse(uint32_t _time) {
    for (int j = cfg.pin_size - 1; j >= 0; j--) {
        set(cfg.pin_ptr[j], HIGH);
        sleep(_time);
    }
    for (int j = cfg.pin_size - 1; j >= 0; j--) {
        set(cfg.pin_ptr[j], LOW);
        sleep(_time);
    }
}

void Keed3ChannelExt::set(uint8_t _pin, uint8_t _state) {
    if (cfg.reverse) digitalWrite(_pin, !_state);
    else digitalWrite(_pin, _state);
}

void Keed3ChannelExt::setStateHigh(int index, ...) {
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

void Keed3ChannelExt::setStateLow(int index, ...) {
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

void Keed3ChannelExt::off() {
    for (int i = 0; i < cfg.pin_size; i++) {
        set(cfg.pin_ptr[i], LOW);
    }
}

void Keed3ChannelExt::on() {
    for (int i = 0; i < cfg.pin_size; i++) {
        set(cfg.pin_ptr[i], HIGH);
    }
}

