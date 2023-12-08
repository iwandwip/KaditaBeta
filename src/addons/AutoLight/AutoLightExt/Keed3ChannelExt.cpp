/*
 *  Keed3ChannelExt.cpp
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#include "Keed3ChannelExt.h"

Keed3ChannelExt::Keed3ChannelExt()
        : sequence(0), ioTimer(40), taskTemp(nullptr),
          sequences{&Keed3ChannelExt::taskSequenceOFF, &Keed3ChannelExt::taskSequence1,
                    &Keed3ChannelExt::taskSequence2, &Keed3ChannelExt::taskSequence3} {}

void Keed3ChannelExt::init() {
    pinMode(isr.pin, INPUT_PULLUP);
#if defined(ESP8266)
#elif defined(ESP32)
#else
    attachInterrupt(digitalPinToInterrupt(isr.pin), isr.isrCallback, RISING);
#endif
    taskTemp = sequences[sequence];
}

void Keed3ChannelExt::update() {
    if (isr.pressed) isr.pressed = false;
    (this->*taskTemp)();
}

void Keed3ChannelExt::run(IOExpander **_ioBase, uint8_t _ioNum) {
    update();
}

void Keed3ChannelExt::run(configuration_t _cfg) {
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

}

void Keed3ChannelExt::taskSequence2() {

}

void Keed3ChannelExt::taskSequence3() {

}

void Keed3ChannelExt::taskSequenceOFF() {

}

void Keed3ChannelExt::sleep(uint32_t _time) {
    if (isr.pressed) return;
    delay(_time);
}

void Keed3ChannelExt::blink(uint32_t _time) {
    for (int i = 0; i < cfg.pin_size; i++) {
        digitalWrite(cfg.pin_ptr[i], LOW);
    }
    sleep(_time);
    for (int i = 0; i < cfg.pin_size; i++) {
        digitalWrite(cfg.pin_ptr[i], HIGH);
    }
    sleep(_time);
}

void Keed3ChannelExt::snake(uint32_t _time) {
    for (int j = 0; j < cfg.pin_size; j++) {
        digitalWrite(cfg.pin_ptr[j], LOW);
        sleep(_time);
    }
    for (int j = 0; j < cfg.pin_size; j++) {
        digitalWrite(cfg.pin_ptr[j], HIGH);
        sleep(_time);
    }
}

void Keed3ChannelExt::snakeReverse(uint32_t _time) {
    for (int j = cfg.pin_size; j > 0; j--) {
        digitalWrite(cfg.pin_ptr[j - 1], LOW);
        sleep(_time);
    }
    for (int j = cfg.pin_size; j > 0; j--) {
        digitalWrite(cfg.pin_ptr[j - 1], HIGH);
        sleep(_time);
    }
}

void Keed3ChannelExt::set(uint8_t _pin, uint8_t _state) {
    digitalWrite(_pin, _state);
}

void Keed3ChannelExt::off() {
    for (int i = 0; i < cfg.pin_size; i++) {
        digitalWrite(cfg.pin_ptr[i], HIGH);
    }
}

void Keed3ChannelExt::on() {
    for (int i = 0; i < cfg.pin_size; i++) {
        digitalWrite(cfg.pin_ptr[i], LOW);
    }
}