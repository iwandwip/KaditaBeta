/*
 *  Keed4ChannelExt.cpp
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#include "Keed4ChannelExt.h"

Keed4ChannelExt::Keed4ChannelExt()
        : sequence(0), ioTimer(40), taskTemp(nullptr),
          sequences{&Keed4ChannelExt::taskSequenceOFF, &Keed4ChannelExt::taskSequence1,
                    &Keed4ChannelExt::taskSequence2, &Keed4ChannelExt::taskSequence3} {}

void Keed4ChannelExt::init() {
    pinMode(isr.pin, INPUT_PULLUP);
#if defined(ESP8266)
#elif defined(ESP32)
#else
    attachInterrupt(digitalPinToInterrupt(isr.pin), isr.isrCallback, RISING);
#endif
    taskTemp = sequences[sequence];
}

void Keed4ChannelExt::update() {
    if (isr.pressed) isr.pressed = false;
    (this->*taskTemp)();
}

void Keed4ChannelExt::run(IOExpander **_ioBase, uint8_t _ioNum) {
    update();
}

void Keed4ChannelExt::run(configuration_t _cfg) {
    cfg = _cfg;
    update();
}

void Keed4ChannelExt::setInterruptConfig(interrupt_t _cfg) {
    isr = _cfg;
}

void Keed4ChannelExt::changeModes() {
    if (millis() - isrTimer >= 250) {
        sequence = (sequence < 3) ? sequence + 1 : 0;
        taskTemp = sequences[sequence];
        isr.num++;
        isr.pressed = true;
        isrTimer = millis();
    }
}

void Keed4ChannelExt::setBaseDelay(uint32_t _time) {
    ioTimer = _time;
}

void (Keed4ChannelExt::*Keed4ChannelExt::getSequence(uint8_t index))() {
    return sequences[index];
}

void Keed4ChannelExt::taskSequence1() {

}

void Keed4ChannelExt::taskSequence2() {

}

void Keed4ChannelExt::taskSequence3() {

}

void Keed4ChannelExt::taskSequenceOFF() {

}

void Keed4ChannelExt::sleep(uint32_t _time) {
    if (isr.pressed) return;
    delay(_time);
}

void Keed4ChannelExt::blink(uint32_t _time) {
    for (int i = 0; i < cfg.pin_size; i++) {
        digitalWrite(cfg.pin_ptr[i], LOW);
    }
    sleep(_time);
    for (int i = 0; i < cfg.pin_size; i++) {
        digitalWrite(cfg.pin_ptr[i], HIGH);
    }
    sleep(_time);
}

void Keed4ChannelExt::snake(uint32_t _time) {
    for (int j = 0; j < cfg.pin_size; j++) {
        digitalWrite(cfg.pin_ptr[j], LOW);
        sleep(_time);
    }
    for (int j = 0; j < cfg.pin_size; j++) {
        digitalWrite(cfg.pin_ptr[j], HIGH);
        sleep(_time);
    }
}

void Keed4ChannelExt::snakeReverse(uint32_t _time) {
    for (int j = cfg.pin_size; j > 0; j--) {
        digitalWrite(cfg.pin_ptr[j - 1], LOW);
        sleep(_time);
    }
    for (int j = cfg.pin_size; j > 0; j--) {
        digitalWrite(cfg.pin_ptr[j - 1], HIGH);
        sleep(_time);
    }
}

void Keed4ChannelExt::set(uint8_t _pin, uint8_t _state) {
    digitalWrite(_pin, _state);
}

void Keed4ChannelExt::off() {
    for (int i = 0; i < cfg.pin_size; i++) {
        digitalWrite(cfg.pin_ptr[i], HIGH);
    }
}

void Keed4ChannelExt::on() {
    for (int i = 0; i < cfg.pin_size; i++) {
        digitalWrite(cfg.pin_ptr[i], LOW);
    }
}