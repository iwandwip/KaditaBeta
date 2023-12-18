/*
 *  Keed3ChannelStrobe.cpp
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#include "Keed3ChannelStrobe.h"

#define setHigh(...) setStateHigh(__VA_ARGS__, -1)
#define setLow(...) setStateLow(__VA_ARGS__, -1)

Keed3ChannelStrobe::Keed3ChannelStrobe()
        : sequence(0), ioTimer(40), taskTemp(nullptr),
          sequences{&Keed3ChannelStrobe::taskSequenceOFF,
                    &Keed3ChannelStrobe::taskSequence1,
                    &Keed3ChannelStrobe::taskSequence2,
                    &Keed3ChannelStrobe::taskSequence3} {}

void Keed3ChannelStrobe::init(IOExpander **_ioBase, configuration_t _cfg) {
    pinMode(isr.pin, INPUT_PULLUP);
#if defined(ESP8266)
#elif defined(ESP32)
    attachInterrupt(isr.pin, isr.isrCallback, RISING);
#else
    attachInterrupt(digitalPinToInterrupt(isr.pin), isr.isrCallback, RISING);
#endif
    taskTemp = sequences[sequence];
    cfg = _cfg;
    off();
}

void Keed3ChannelStrobe::update() {
    if (isr.pressed) isr.pressed = false;
    (this->*taskTemp)();
}

void Keed3ChannelStrobe::run() {
    update();
}

void Keed3ChannelStrobe::setInterruptConfig(interrupt_t _cfg) {
    isr = _cfg;
}

void Keed3ChannelStrobe::changeModes() {
    if (millis() - isrTimer >= 250) {
        sequence = (sequence < 3) ? sequence + 1 : 0;
        taskTemp = sequences[sequence];
        isr.num++;
        isr.pressed = true;
        isrTimer = millis();
    }
}

void Keed3ChannelStrobe::setBaseDelay(uint32_t _time) {
    ioTimer = _time;
}

void (Keed3ChannelStrobe::*Keed3ChannelStrobe::getSequence(uint8_t index))() {
    return sequences[index];
}

void Keed3ChannelStrobe::taskSequence1() {
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
    for (int i = 0; i < 8; ++i) {
        blink(ioTimer * 4);
    }
}

void Keed3ChannelStrobe::taskSequence2() {
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

void Keed3ChannelStrobe::taskSequence3() {
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

void Keed3ChannelStrobe::taskSequenceOFF() {
    off();
}

void Keed3ChannelStrobe::sleep(uint32_t _time) {
    if (isr.pressed) return;
    delay(_time);
}

void Keed3ChannelStrobe::blink(uint32_t _time) {
    for (int i = 0; i < cfg.pin_size; i++) {
        set(cfg.pin_ptr[i], HIGH);
    }
    sleep(_time);
    for (int i = 0; i < cfg.pin_size; i++) {
        set(cfg.pin_ptr[i], LOW);
    }
    sleep(_time);
}

void Keed3ChannelStrobe::snake(uint32_t _time) {
    for (int j = 0; j < cfg.pin_size; j++) {
        set(cfg.pin_ptr[j], HIGH);
        sleep(_time);
    }
    for (int j = 0; j < cfg.pin_size; j++) {
        set(cfg.pin_ptr[j], LOW);
        sleep(_time);
    }
}

void Keed3ChannelStrobe::snakeReverse(uint32_t _time) {
    for (int j = cfg.pin_size - 1; j >= 0; j--) {
        set(cfg.pin_ptr[j], HIGH);
        sleep(_time);
    }
    for (int j = cfg.pin_size - 1; j >= 0; j--) {
        set(cfg.pin_ptr[j], LOW);
        sleep(_time);
    }
}

void Keed3ChannelStrobe::set(uint8_t _pin, uint8_t _state) {
    if (cfg.reverse) digitalWrite(_pin, !_state);
    else digitalWrite(_pin, _state);
}

void Keed3ChannelStrobe::setStateHigh(int index, ...) {
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

void Keed3ChannelStrobe::setStateLow(int index, ...) {
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

void Keed3ChannelStrobe::off() {
    for (int i = 0; i < cfg.pin_size; i++) {
        set(cfg.pin_ptr[i], LOW);
    }
}

void Keed3ChannelStrobe::on() {
    for (int i = 0; i < cfg.pin_size; i++) {
        set(cfg.pin_ptr[i], HIGH);
    }
}
