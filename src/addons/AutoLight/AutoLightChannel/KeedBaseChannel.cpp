/*
 *  KeedBaseChannel.cpp
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#include "KeedBaseChannel.h"

KeedBaseChannel::KeedBaseChannel(bool _isUsingExpander)
        : sequence(0), ioTimer(40), isUsingExpander(_isUsingExpander), taskTemp(nullptr),
          sequences{&KeedBaseChannel::off,
                    &KeedBaseChannel::taskSequence0,
                    &KeedBaseChannel::taskSequence1,
                    &KeedBaseChannel::taskSequence2,
                    &KeedBaseChannel::taskSequence3,
                    &KeedBaseChannel::taskSequence4,
                    &KeedBaseChannel::taskSequence5,
                    &KeedBaseChannel::taskSequence6,
                    &KeedBaseChannel::on} {}

void KeedBaseChannel::init(IOExpander **_ioBase, configuration_t _cfg) {
    pinMode(isr.pin, INPUT_PULLUP);
#if defined(ESP8266)
#elif defined(ESP32)
    attachInterrupt(isr.pin, isr.isrCallback, RISING);
#else
    attachInterrupt(digitalPinToInterrupt(isr.pin), isr.isrCallback, RISING);
#endif
    taskTemp = sequences[sequence];
    ioBase = _ioBase;
    cfg = _cfg;
    sequence = cfg.sequence;
    taskTemp = sequences[sequence];
    if (cfg.display) {
        display = new KeedDisplay(cfg.channel, 0x3C);
        display->clear();
        display->fillBorder();
    }
}

void KeedBaseChannel::update() {
    if (isr.pressed) {
        forceOff();
        if (cfg.display) {
            display->clear();
            display->fillBorder();
        }
        sequence = (sequence < ((TASK_SEQUENCE_NUM + 2) - 1)) ? sequence + 1 : 0;
        taskTemp = sequences[sequence];
        isr.pressed = false;
    }
    (this->*taskTemp)();
}

void KeedBaseChannel::run() {
    update();
}

void KeedBaseChannel::setInterruptConfig(interrupt_t _cfg) {
    isr = _cfg;
}

void KeedBaseChannel::changeModes() {
    if (millis() - isrTimer >= BUTTON_DEBOUNCE_TIME) {
        isr.num++;
        isr.pressed = true;
        isrTimer = millis();
    }
}

void KeedBaseChannel::setBaseDelay(uint32_t _time) {
    ioTimer = _time;
}

void (KeedBaseChannel::*KeedBaseChannel::getSequence(uint8_t index))() {
    return sequences[index];
}

void KeedBaseChannel::sleep(uint32_t _time) {
    if (isr.pressed) return;
    delay(_time);
}

void KeedBaseChannel::set(uint8_t _pin, uint8_t _state) {
    if (isr.pressed) return;
    if (isUsingExpander) {
        int index = ceil((_pin + 1) / 8.0) - 1;
        int pins_mod = _pin % 8;
        if (cfg.reverse) ioBase[index]->digitalWrite(pins_mod, !_state);
        else ioBase[index]->digitalWrite(pins_mod, _state);
    } else {
        if (cfg.reverse) digitalWrite(_pin, !_state);
        else digitalWrite(_pin, _state);
    }
    if (cfg.display) {
        display->write(_pin, _state);
    }
}

void KeedBaseChannel::setStateHigh(int index, ...) {
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

void KeedBaseChannel::setStateLow(int index, ...) {
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

void KeedBaseChannel::off() {
    for (int i = 0; i < cfg.pin_size; i++) {
        set(cfg.pin_ptr[i], LOW);
    }
}

void KeedBaseChannel::forceOff() {
    if (isUsingExpander) {
        for (int i = 0; i < cfg.io_size; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (cfg.reverse) ioBase[i]->digitalWrite(j, HIGH);
                else ioBase[i]->digitalWrite(j, LOW);
            }
        }
    } else {
        for (int i = 0; i < cfg.pin_size; ++i) {
            if (cfg.reverse) digitalWrite(cfg.pin_ptr[i], HIGH);
            else digitalWrite(cfg.pin_ptr[i], LOW);
        }
    }
}

void KeedBaseChannel::on() {
    for (int i = 0; i < cfg.pin_size; i++) {
        set(cfg.pin_ptr[i], HIGH);
    }
}