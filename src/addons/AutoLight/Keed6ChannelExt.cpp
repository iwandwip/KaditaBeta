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
#if defined(ESP8266)
#elif defined(ESP32)
#else // avr & etc
    pinMode(isr.pin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(isr.pin), isr.isrCallback, FALLING);
#endif
}

void Keed6ChannelExt::update() {
    taskTemp = sequences[sequence];
    (this->*taskTemp)();
//    if (sequence < 3) sequence++;
//    else sequence = 0;
}

void Keed6ChannelExt::run(IOExpander **_ioBase, uint8_t _ioNum) {
    update();
}

void Keed6ChannelExt::run(configuration_t _cfg) {
    cfg = _cfg;
    update();
}

void Keed6ChannelExt::setInterruptConfig(interrupt_t _cfg) {
    isr = _cfg;
}

void Keed6ChannelExt::changeModes() {
    if (millis() - ioTimer >= 250) {
        isr.num++;
        isr.pressed = true;
        ioTimer = millis();
    }
}

void (Keed6ChannelExt::*Keed6ChannelExt::getSequence(uint8_t index))() {
    return sequences[index];
}

void Keed6ChannelExt::taskSequence0() {
    // sequence 0
    {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 15; ++j) {
                blink(30);
            }
            delay(1000);
        }
        off();
    }
    // sequence 1
    {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 3; j++) {
                set(cfg.pin_ptr[j], LOW);
            }
            delay(30);
            for (int j = 0; j < 3; j++) {
                set(cfg.pin_ptr[j], HIGH);
            }
            delay(30);
        }
        delay(90);
        for (int i = 0; i < 4; ++i) {
            for (int j = 3; j < 6; j++) {
                set(cfg.pin_ptr[j], LOW);
            }
            delay(30);
            for (int j = 3; j < 6; j++) {
                set(cfg.pin_ptr[j], HIGH);
            }
            delay(30);
        }
        delay(90);
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 3; j++) {
                set(cfg.pin_ptr[j], LOW);
            }
            delay(30);
            for (int j = 0; j < 3; j++) {
                set(cfg.pin_ptr[j], HIGH);
            }
            delay(30);
        }
        delay(90);
        delay(1000);
        off();
    }
    // sequence 2
    {
        for (int i = 0; i < 4; ++i) {
            for (int j = 3; j < 6; j++) {
                set(cfg.pin_ptr[j], LOW);
            }
            delay(30);
            for (int j = 3; j < 6; j++) {
                set(cfg.pin_ptr[j], HIGH);
            }
            delay(30);
        }
        delay(90);
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 3; j++) {
                set(cfg.pin_ptr[j], LOW);
            }
            delay(30);
            for (int j = 0; j < 3; j++) {
                set(cfg.pin_ptr[j], HIGH);
            }
            delay(30);
        }
        delay(90);
        for (int i = 0; i < 4; ++i) {
            for (int j = 3; j < 6; j++) {
                set(cfg.pin_ptr[j], LOW);
            }
            delay(30);
            for (int j = 3; j < 6; j++) {
                set(cfg.pin_ptr[j], HIGH);
            }
            delay(30);
        }
        delay(90);
        off();
        delay(1000);
    }
    // sequence 3
    {
        for (int k = 0; k < 2; ++k) {
            for (int i = 0; i < 6; i += 2) {
                for (int j = 0; j < 4; ++j) {
                    digitalWrite(cfg.pin_ptr[i], LOW);
                    digitalWrite(cfg.pin_ptr[i + 1], LOW);
                    delay(30);
                    digitalWrite(cfg.pin_ptr[i], HIGH);
                    digitalWrite(cfg.pin_ptr[i + 1], HIGH);
                    delay(30);
                }
                delay(250);
            }
            delay(1000);
        }
        off();
    }
    // sequence 4
    for (int i = 6; i > 0; --i) {
        for (int j = 0; j < i; j++) {
            digitalWrite(cfg.pin_ptr[j], LOW);
            delay(60);
            digitalWrite(cfg.pin_ptr[j], HIGH);
        }
        digitalWrite(cfg.pin_ptr[i - 1], LOW);
    }
    // off();
    // delay(1000);
    // sequence 5
    for (int i = 6; i > 0; --i) {
        digitalWrite(cfg.pin_ptr[i - 1], HIGH);
        delay(60);
    }
    off();
    delay(1000);
    // sequence 6
    for (int k = 60; k >= 30; k -= 5) {
        for (int j = 0; j < 3; ++j) {
            for (int i = 6; i > 3 + j; --i) {
                digitalWrite(cfg.pin_ptr[i - 1], LOW);
                digitalWrite(cfg.pin_ptr[6 - i], LOW);
                delay(k);
                digitalWrite(cfg.pin_ptr[i - 1], HIGH);
                digitalWrite(cfg.pin_ptr[6 - i], HIGH);
            }
            for (int i = j; i < 3; ++i) {
                digitalWrite(cfg.pin_ptr[i + 3], LOW);
                digitalWrite(cfg.pin_ptr[(3 - 1) - i], LOW);
                delay(k);
                digitalWrite(cfg.pin_ptr[i + 3], HIGH);
                digitalWrite(cfg.pin_ptr[(3 - 1) - i], HIGH);
            }
            for (int i = 6 - 1; i > 3 + j; --i) {
                digitalWrite(cfg.pin_ptr[i - 1], LOW);
                digitalWrite(cfg.pin_ptr[6 - i], LOW);
                delay(k);
                digitalWrite(cfg.pin_ptr[i - 1], HIGH);
                digitalWrite(cfg.pin_ptr[6 - i], HIGH);
            }
            digitalWrite(cfg.pin_ptr[3 + j], LOW);
            digitalWrite(cfg.pin_ptr[(3 - 1) - j], LOW);
        }
        for (int i = 0; i < 3; ++i) {
            digitalWrite(cfg.pin_ptr[i + 3], HIGH);
            digitalWrite(cfg.pin_ptr[(3 - 1) - i], HIGH);
            delay(k);
        }
    }
    on();
    delay(1000);
    for (int i = 6; i > 0; --i) {
        digitalWrite(cfg.pin_ptr[i - 1], HIGH);
        delay(60);
    }
    off();
    delay(1000);
    // sequence 8
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            digitalWrite(cfg.pin_ptr[i], LOW);
            delay(30);
            digitalWrite(cfg.pin_ptr[i], HIGH);
            delay(30);
        }
        delay(30);
    }
    for (int i = 6; i > 0; --i) {
        for (int j = 0; j < 6; ++j) {
            digitalWrite(cfg.pin_ptr[i - 1], LOW);
            delay(30);
            digitalWrite(cfg.pin_ptr[i - 1], HIGH);
            delay(30);
        }
        delay(30);
    }
    off();
    delay(1000);
    // sequence 9
    for (int i = 0; i < 3 + 1; ++i) {
        for (int j = 0; j < 4; ++j) {
            digitalWrite(cfg.pin_ptr[i], LOW);
            digitalWrite(cfg.pin_ptr[i + 2], LOW);
            delay(30);
            digitalWrite(cfg.pin_ptr[i], HIGH);
            digitalWrite(cfg.pin_ptr[i + 2], HIGH);
            delay(30);
        }
        delay(90);
    }
    off();
    delay(1000);
    // sequence 10
    for (int k = 40; k >= 20; k -= 4) {
        for (int i = 0; i < 6; i++) {
            digitalWrite(cfg.pin_ptr[i], LOW);
            delay(k);
        }
        for (int i = 0; i < 6; i++) {
            digitalWrite(cfg.pin_ptr[i], HIGH);
            delay(k);
        }
        for (int j = 6; j > 0; j--) {
            digitalWrite(cfg.pin_ptr[j - 1], LOW);
            delay(k);
        }
        for (int j = 6; j > 0; j--) {
            digitalWrite(cfg.pin_ptr[j - 1], HIGH);
            delay(k);
        }
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

void Keed6ChannelExt::set(uint8_t _pin, uint8_t _state) {
    digitalWrite(_pin, _state);
}

void Keed6ChannelExt::off() {
    for (int i = 0; i < cfg.pin_size; i++) {
        digitalWrite(cfg.pin_ptr[i], HIGH);
    }
}

void Keed6ChannelExt::on() {
    for (int i = 0; i < cfg.pin_size; i++) {
        digitalWrite(cfg.pin_ptr[i], LOW);
    }
}