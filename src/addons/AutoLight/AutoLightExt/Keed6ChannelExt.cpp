/*
 *  Keed6ChannelExt.cpp
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#include "Keed6ChannelExt.h"

Keed6ChannelExt::Keed6ChannelExt()
        : sequence(0), ioTimer(40), taskTemp(nullptr),
          sequences{&Keed6ChannelExt::taskSequenceOFF, &Keed6ChannelExt::taskSequence1,
                    &Keed6ChannelExt::taskSequence2, &Keed6ChannelExt::taskSequenceON} {}

void Keed6ChannelExt::init() {
    pinMode(isr.pin, INPUT_PULLUP);
#if defined(ESP8266)
#elif defined(ESP32)
#else
    attachInterrupt(digitalPinToInterrupt(isr.pin), isr.isrCallback, RISING);
#endif
    taskTemp = sequences[sequence];
}

void Keed6ChannelExt::update() {
    if (isr.pressed) isr.pressed = false;
    (this->*taskTemp)();
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
    if (millis() - isrTimer >= 250) {
        sequence = (sequence < 3) ? sequence + 1 : 0;
        taskTemp = sequences[sequence];
        Serial.println("| pressed: " + String(sequence));
        isr.num++;
        isr.pressed = true;
        isrTimer = millis();
    }
}

void Keed6ChannelExt::setBaseDelay(uint32_t _time) {
    ioTimer = _time;
}

void (Keed6ChannelExt::*Keed6ChannelExt::getSequence(uint8_t index))() {
    return sequences[index];
}

void Keed6ChannelExt::taskSequence1() {
    // sequence 0
    {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 15; ++j) {
                blink(ioTimer);
            }
            sleep(500);
        }
        off();
    }
    // sequence 1
    {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 3; j++) {
                set(cfg.pin_ptr[j], LOW);
            }
            sleep(ioTimer);
            for (int j = 0; j < 3; j++) {
                set(cfg.pin_ptr[j], HIGH);
            }
            sleep(ioTimer);
        }
        sleep(50);
        for (int i = 0; i < 4; ++i) {
            for (int j = 3; j < 6; j++) {
                set(cfg.pin_ptr[j], LOW);
            }
            sleep(ioTimer);
            for (int j = 3; j < 6; j++) {
                set(cfg.pin_ptr[j], HIGH);
            }
            sleep(ioTimer);
        }
        sleep(50);
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 3; j++) {
                set(cfg.pin_ptr[j], LOW);
            }
            sleep(ioTimer);
            for (int j = 0; j < 3; j++) {
                set(cfg.pin_ptr[j], HIGH);
            }
            sleep(ioTimer);
        }
        // sleep(50);
        sleep(500);
        off();
    }
    // sequence 2
    for (int i = 0; i < 4; ++i) {
        for (int j = 3; j < 6; j++) {
            set(cfg.pin_ptr[j], LOW);
        }
        sleep(ioTimer);
        for (int j = 3; j < 6; j++) {
            set(cfg.pin_ptr[j], HIGH);
        }
        sleep(ioTimer);
    }
    sleep(50);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 3; j++) {
            set(cfg.pin_ptr[j], LOW);
        }
        sleep(ioTimer);
        for (int j = 0; j < 3; j++) {
            set(cfg.pin_ptr[j], HIGH);
        }
        sleep(ioTimer);
    }
    sleep(50);
    for (int i = 0; i < 4; ++i) {
        for (int j = 3; j < 6; j++) {
            set(cfg.pin_ptr[j], LOW);
        }
        sleep(ioTimer);
        for (int j = 3; j < 6; j++) {
            set(cfg.pin_ptr[j], HIGH);
        }
        sleep(ioTimer);
    }
    // sleep(50);
    off();
    sleep(500);
    // sequence 3
    for (int k = 0; k < 2; ++k) {
        for (int i = 0; i < 6; i += 2) {
            for (int j = 0; j < 4; ++j) {
                digitalWrite(cfg.pin_ptr[i], LOW);
                digitalWrite(cfg.pin_ptr[i + 1], LOW);
                sleep(ioTimer);
                digitalWrite(cfg.pin_ptr[i], HIGH);
                digitalWrite(cfg.pin_ptr[i + 1], HIGH);
                sleep(ioTimer);
            }
            sleep(300);
        }
        sleep(500);
    }
    off();
    // sequence 4
    for (int i = 6; i > 0; --i) {
        for (int j = 0; j < i; j++) {
            digitalWrite(cfg.pin_ptr[j], LOW);
            sleep(ioTimer * 2);
            digitalWrite(cfg.pin_ptr[j], HIGH);
        }
        digitalWrite(cfg.pin_ptr[i - 1], LOW);
    }
    // off();
    // sleep(500);
    // sequence 5
    for (int i = 6; i > 0; --i) {
        digitalWrite(cfg.pin_ptr[i - 1], HIGH);
        sleep(ioTimer * 2);
    }
    off();
    sleep(500);
    // sequence 6
    for (int k = ioTimer * 2; k >= ioTimer; k -= 5) {
        for (int j = 0; j < 3; ++j) {
            for (int i = 6; i > 3 + j; --i) {
                digitalWrite(cfg.pin_ptr[i - 1], LOW);
                digitalWrite(cfg.pin_ptr[6 - i], LOW);
                sleep(k);
                digitalWrite(cfg.pin_ptr[i - 1], HIGH);
                digitalWrite(cfg.pin_ptr[6 - i], HIGH);
            }
            for (int i = j; i < 3; ++i) {
                digitalWrite(cfg.pin_ptr[i + 3], LOW);
                digitalWrite(cfg.pin_ptr[(3 - 1) - i], LOW);
                sleep(k);
                digitalWrite(cfg.pin_ptr[i + 3], HIGH);
                digitalWrite(cfg.pin_ptr[(3 - 1) - i], HIGH);
            }
            for (int i = 6 - 1; i > 3 + j; --i) {
                digitalWrite(cfg.pin_ptr[i - 1], LOW);
                digitalWrite(cfg.pin_ptr[6 - i], LOW);
                sleep(k);
                digitalWrite(cfg.pin_ptr[i - 1], HIGH);
                digitalWrite(cfg.pin_ptr[6 - i], HIGH);
            }
            digitalWrite(cfg.pin_ptr[3 + j], LOW);
            digitalWrite(cfg.pin_ptr[(3 - 1) - j], LOW);
        }
        for (int i = 0; i < 3; ++i) {
            digitalWrite(cfg.pin_ptr[i + 3], HIGH);
            digitalWrite(cfg.pin_ptr[(3 - 1) - i], HIGH);
            sleep(k);
        }
    }
    on();
    sleep(500);
    for (int i = 6; i > 0; --i) {
        digitalWrite(cfg.pin_ptr[i - 1], HIGH);
        sleep(ioTimer * 2);
    }
    off();
    sleep(500);
}

void Keed6ChannelExt::taskSequence2() {
    // sequence 4
    for (int i = 6; i > 0; --i) {
        for (int j = 0; j < i; j++) {
            digitalWrite(cfg.pin_ptr[j], LOW);
            sleep(ioTimer * 2);
            digitalWrite(cfg.pin_ptr[j], HIGH);
        }
        digitalWrite(cfg.pin_ptr[i - 1], LOW);
    }
    // off();
    // sleep(500);
    // sequence 5
    for (int i = 6; i > 0; --i) {
        digitalWrite(cfg.pin_ptr[i - 1], HIGH);
        sleep(ioTimer * 2);
    }
    off();
    sleep(500);
    // sequence 8
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            digitalWrite(cfg.pin_ptr[i], LOW);
            sleep(ioTimer);
            digitalWrite(cfg.pin_ptr[i], HIGH);
            sleep(ioTimer);
        }
        sleep(ioTimer);
    }
    for (int i = 6; i > 0; --i) {
        for (int j = 0; j < 6; ++j) {
            digitalWrite(cfg.pin_ptr[i - 1], LOW);
            sleep(ioTimer);
            digitalWrite(cfg.pin_ptr[i - 1], HIGH);
            sleep(ioTimer);
        }
        sleep(ioTimer);
    }
    off();
    sleep(500);
    // sequence 9
    for (int i = 0; i < 3 + 1; ++i) {
        for (int j = 0; j < 4; ++j) {
            digitalWrite(cfg.pin_ptr[i], LOW);
            digitalWrite(cfg.pin_ptr[i + 2], LOW);
            sleep(ioTimer);
            digitalWrite(cfg.pin_ptr[i], HIGH);
            digitalWrite(cfg.pin_ptr[i + 2], HIGH);
            sleep(ioTimer);
        }
        sleep(50);
    }
    off();
    sleep(500);
    // sequence 10
    for (float k = ioTimer * 2; k >= ioTimer; k -= (ioTimer / 3)) {
        for (int i = 0; i < 6; i++) {
            digitalWrite(cfg.pin_ptr[i], LOW);
            sleep(k);
        }
        for (int i = 0; i < 6; i++) {
            digitalWrite(cfg.pin_ptr[i], HIGH);
            sleep(k);
        }
        for (int j = 6; j > 0; j--) {
            digitalWrite(cfg.pin_ptr[j - 1], LOW);
            sleep(k);
        }
        for (int j = 6; j > 0; j--) {
            digitalWrite(cfg.pin_ptr[j - 1], HIGH);
            sleep(k);
        }
    }
    off();
    sleep(500);
}

void Keed6ChannelExt::taskSequenceOFF() {
    for (int i = 0; i < cfg.pin_size; i++) {
        digitalWrite(cfg.pin_ptr[i], HIGH);
    }
}

void Keed6ChannelExt::taskSequenceON() {
    for (int i = 0; i < cfg.pin_size; i++) {
        digitalWrite(cfg.pin_ptr[i], LOW);
    }
}

void Keed6ChannelExt::sleep(uint32_t _time) {
    if (isr.pressed) return;
    delay(_time);
}

void Keed6ChannelExt::blink(uint32_t _time) {
    for (int i = 0; i < cfg.pin_size; i++) {
        digitalWrite(cfg.pin_ptr[i], LOW);
    }
    for (int i = 0; i < cfg.pin_size; i++) {
        digitalWrite(cfg.pin_ptr[i], LOW);
    }
    sleep(_time);
    for (int i = 0; i < cfg.pin_size; i++) {
        digitalWrite(cfg.pin_ptr[i], HIGH);
    }
    for (int i = 0; i < cfg.pin_size; i++) {
        digitalWrite(cfg.pin_ptr[i], HIGH);
    }
    sleep(_time);
}

void Keed6ChannelExt::snake(uint32_t _time) {
    for (int j = 0; j < cfg.pin_size; j++) {
        digitalWrite(cfg.pin_ptr[j], LOW);
        sleep(_time);
    }
    for (int j = 0; j < cfg.pin_size; j++) {
        digitalWrite(cfg.pin_ptr[j], HIGH);
        sleep(_time);
    }
}

void Keed6ChannelExt::snakeReverse(uint32_t _time) {
    for (int j = cfg.pin_size; j > 0; j--) {
        digitalWrite(cfg.pin_ptr[j - 1], LOW);
        sleep(_time);
    }
    for (int j = cfg.pin_size; j > 0; j--) {
        digitalWrite(cfg.pin_ptr[j - 1], HIGH);
        sleep(_time);
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