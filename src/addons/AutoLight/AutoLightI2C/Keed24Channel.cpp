/*
 *  Keed24Channel.cpp
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#include "Keed24Channel.h"

#define setHigh(...) setStateHigh(__VA_ARGS__, -1)
#define setLow(...) setStateLow(__VA_ARGS__, -1)

Keed24Channel::Keed24Channel()
        : sequence(0), ioTimer(40), taskTemp(nullptr),
          sequences{&Keed24Channel::off,
                    &Keed24Channel::taskSequence0,
                    &Keed24Channel::taskSequence1,
                    &Keed24Channel::taskSequence2,
                    &Keed24Channel::taskSequence3,
                    &Keed24Channel::taskSequence4,
                    &Keed24Channel::taskSequence5,
                    &Keed24Channel::taskSequence6,
                    &Keed24Channel::on} {}

void Keed24Channel::init() {
    pinMode(isr.pin, INPUT_PULLUP);
#if defined(ESP8266)
#elif defined(ESP32)
    attachInterrupt(isr.pin, isr.isrCallback, RISING);
#else
    attachInterrupt(digitalPinToInterrupt(isr.pin), isr.isrCallback, RISING);
#endif
    taskTemp = sequences[sequence];
}

void Keed24Channel::update() {
    if (isr.pressed) isr.pressed = false;
    (this->*taskTemp)();
}

void Keed24Channel::run(IOExpander **_ioBase, uint8_t _ioNum, configuration_t _cfg) {
    ioBase = _ioBase;
    ioNum = _ioNum;
    cfg = _cfg;
    update();
}

void Keed24Channel::setInterruptConfig(interrupt_t _cfg) {
    isr = _cfg;
}

void Keed24Channel::changeModes() {
    if (millis() - isrTimer >= BUTTON_DEBOUNCE_TIME) {
        sequence = (sequence < ((TASK_SEQUENCE_NUM + 2) - 1)) ? sequence + 1 : 0;
        taskTemp = sequences[sequence];
        isr.num++;
        isr.pressed = true;
        isrTimer = millis();
    }
}

void Keed24Channel::setBaseDelay(uint32_t _time) {
    ioTimer = _time;
}

void (Keed24Channel::*Keed24Channel::getSequence(uint8_t index))() {
    return sequences[index];
}

uint8_t Keed24Channel::getTaskSequenceIndex() {
    return sequence;
}

void Keed24Channel::taskSequence0() {
    // blink ////////////////////////////////////////
    {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 15; ++j) {
                for (int k = 0; k < cfg.pin_size; k++) {
                    set(cfg.pin_ptr[k], HIGH);
                }
                sleep(ioTimer);
                for (int k = 0; k < cfg.pin_size; k++) {
                    set(cfg.pin_ptr[k], LOW);
                }
                sleep(ioTimer);
            }
            sleep(500);
        }
        off();
    }
    // half blink ////////////////////////////////////////
    {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < (cfg.pin_size / 2); j++) {
                set(cfg.pin_ptr[j], HIGH);
            }
            sleep(ioTimer);
            for (int j = 0; j < (cfg.pin_size / 2); j++) {
                set(cfg.pin_ptr[j], LOW);
            }
            sleep(ioTimer);
        }
        sleep(50);
        for (int i = 0; i < 4; ++i) {
            for (int j = (cfg.pin_size / 2); j < cfg.pin_size; j++) {
                set(cfg.pin_ptr[j], HIGH);
            }
            sleep(ioTimer);
            for (int j = (cfg.pin_size / 2); j < cfg.pin_size; j++) {
                set(cfg.pin_ptr[j], LOW);
            }
            sleep(ioTimer);
        }
        sleep(50);
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < (cfg.pin_size / 2); j++) {
                set(cfg.pin_ptr[j], HIGH);
            }
            sleep(ioTimer);
            for (int j = 0; j < (cfg.pin_size / 2); j++) {
                set(cfg.pin_ptr[j], LOW);
            }
            sleep(ioTimer);
        }
        sleep(500);
        off();
    }
    // half blink ////////////////////////////////////////
    {
        for (int i = 0; i < 4; ++i) {
            for (int j = (cfg.pin_size / 2); j < cfg.pin_size; j++) {
                set(cfg.pin_ptr[j], HIGH);
            }
            sleep(ioTimer);
            for (int j = (cfg.pin_size / 2); j < cfg.pin_size; j++) {
                set(cfg.pin_ptr[j], LOW);
            }
            sleep(ioTimer);
        }
        sleep(50);
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < (cfg.pin_size / 2); j++) {
                set(cfg.pin_ptr[j], HIGH);
            }
            sleep(ioTimer);
            for (int j = 0; j < (cfg.pin_size / 2); j++) {
                set(cfg.pin_ptr[j], LOW);
            }
            sleep(ioTimer);
        }
        sleep(50);
        for (int i = 0; i < 4; ++i) {
            for (int j = (cfg.pin_size / 2); j < cfg.pin_size; j++) {
                set(cfg.pin_ptr[j], HIGH);
            }
            sleep(ioTimer);
            for (int j = (cfg.pin_size / 2); j < cfg.pin_size; j++) {
                set(cfg.pin_ptr[j], LOW);
            }
            sleep(ioTimer);
        }
        off();
        sleep(500);
    }
}

void Keed24Channel::taskSequence1() {
    // fill 2 point ////////////////////////////////////////
    {
        for (int i = 0; i < cfg.pin_size / 2; i += 2) {
            for (int j = 0; j < 8; ++j) {
                set(cfg.pin_ptr[i], HIGH);
                set(cfg.pin_ptr[i + 1], HIGH);
                sleep(ioTimer);
                set(cfg.pin_ptr[i], LOW);
                set(cfg.pin_ptr[i + 1], LOW);
                sleep(ioTimer);
            }
            set(cfg.pin_ptr[i], HIGH);
            set(cfg.pin_ptr[i + 1], HIGH);
            sleep(300);
            if (i < (cfg.pin_size / 2) - 1) {
                for (int j = 0; j < 8; ++j) {
                    set(cfg.pin_ptr[(cfg.pin_size - 1) - i], HIGH);
                    set(cfg.pin_ptr[(cfg.pin_size - 1) - (i + 1)], HIGH);
                    sleep(ioTimer);
                    set(cfg.pin_ptr[(cfg.pin_size - 1) - i], LOW);
                    set(cfg.pin_ptr[(cfg.pin_size - 1) - (i + 1)], LOW);
                    sleep(ioTimer);
                }
                set(cfg.pin_ptr[(cfg.pin_size - 1) - i], HIGH);
                set(cfg.pin_ptr[(cfg.pin_size - 1) - (i + 1)], HIGH);
                sleep(300);
            }
        }
        for (int i = cfg.pin_size; i > 0; --i) {
            set(cfg.pin_ptr[i - 1], LOW);
            sleep(ioTimer * 2);
        }
        off();
        sleep(500);
    }
}

void Keed24Channel::taskSequence2() {
    // fill right ////////////////////////////////////////
    {
        for (int i = cfg.pin_size; i > 0; --i) {
            for (int j = 0; j < i; j++) {
                set(cfg.pin_ptr[j], HIGH);
                sleep(ioTimer * 2);
                set(cfg.pin_ptr[j], LOW);
            }
            set(cfg.pin_ptr[i - 1], HIGH);
        }
        for (int i = cfg.pin_size; i > 0; --i) {
            set(cfg.pin_ptr[i - 1], LOW);
            sleep(ioTimer * 2);
        }
        off();
        sleep(500);
    }
}

void Keed24Channel::taskSequence3() {
    // fill in ////////////////////////////////////////
    {
        for (int j = 0; j < cfg.pin_size / 2; ++j) {
            for (int i = cfg.pin_size; i > cfg.pin_size / 2 + j; --i) {
                set(cfg.pin_ptr[i - 1], HIGH);
                set(cfg.pin_ptr[cfg.pin_size - i], HIGH);
                sleep(ioTimer * 2);
                set(cfg.pin_ptr[i - 1], LOW);
                set(cfg.pin_ptr[cfg.pin_size - i], LOW);
            }
            for (int i = j; i < cfg.pin_size / 2; ++i) {
                set(cfg.pin_ptr[i + cfg.pin_size / 2], HIGH);
                set(cfg.pin_ptr[(cfg.pin_size / 2 - 1) - i], HIGH);
                sleep(ioTimer * 2);
                set(cfg.pin_ptr[i + cfg.pin_size / 2], LOW);
                set(cfg.pin_ptr[(cfg.pin_size / 2 - 1) - i], LOW);
            }
            for (int i = cfg.pin_size - 1; i > cfg.pin_size / 2 + j; --i) {
                set(cfg.pin_ptr[i - 1], HIGH);
                set(cfg.pin_ptr[cfg.pin_size - i], HIGH);
                sleep(ioTimer * 2);
                set(cfg.pin_ptr[i - 1], LOW);
                set(cfg.pin_ptr[cfg.pin_size - i], LOW);
            }
            set(cfg.pin_ptr[cfg.pin_size / 2 + j], HIGH);
            set(cfg.pin_ptr[(cfg.pin_size / 2 - 1) - j], HIGH);
        }
        for (int i = 0; i < cfg.pin_size / 2; ++i) {
            set(cfg.pin_ptr[i + cfg.pin_size / 2], LOW);
            set(cfg.pin_ptr[(cfg.pin_size / 2 - 1) - i], LOW);
            sleep(ioTimer * 2);
        }
        off();
        sleep(500);
    }
}

void Keed24Channel::taskSequence4() {
    // blink 1 by 1 ////////////////////////////////////////
    {
        for (int i = 0; i < cfg.pin_size; ++i) {
            for (int j = 0; j < 4; ++j) {
                set(cfg.pin_ptr[i], HIGH);
                sleep(ioTimer);
                set(cfg.pin_ptr[i], LOW);
                sleep(ioTimer);
            }
            sleep(ioTimer);
        }
        for (int i = cfg.pin_size; i > 0; --i) {
            for (int j = 0; j < 4; ++j) {
                set(cfg.pin_ptr[i - 1], HIGH);
                sleep(ioTimer);
                set(cfg.pin_ptr[i - 1], LOW);
                sleep(ioTimer);
            }
            sleep(ioTimer);
        }
        off();
        sleep(500);
    }
}

void Keed24Channel::taskSequence5() {
    // blink 2 fill ////////////////////////////////////////
    {
        for (int j = 0; j < cfg.pin_size / 2; ++j) {
            for (int i = cfg.pin_size / 2; i > j; --i) {
                for (int k = 0; k < 4; ++k) {
                    set(cfg.pin_ptr[i - 1], HIGH);
                    set(cfg.pin_ptr[cfg.pin_size - i], HIGH);
                    sleep(ioTimer);
                    set(cfg.pin_ptr[i - 1], LOW);
                    set(cfg.pin_ptr[cfg.pin_size - i], LOW);
                    sleep(ioTimer);
                }
            }
            set(cfg.pin_ptr[j], HIGH);
            set(cfg.pin_ptr[(cfg.pin_size - 1) - j], HIGH);
        }
        off();
        sleep(500);
    }
}

void Keed24Channel::taskSequence6() {
    // snake and snake reverse ////////////////////////////////////////
    {
        for (float k = ioTimer * 2; k >= ioTimer; k -= ioTimer) {
            for (int i = 0; i < cfg.pin_size; i++) {
                set(cfg.pin_ptr[i], HIGH);
                sleep(k);
            }
            for (int i = 0; i < cfg.pin_size; i++) {
                set(cfg.pin_ptr[i], LOW);
                sleep(k);
            }
            for (int j = cfg.pin_size; j > 0; j--) {
                set(cfg.pin_ptr[j - 1], HIGH);
                sleep(k);
            }
            for (int j = cfg.pin_size; j > 0; j--) {
                set(cfg.pin_ptr[j - 1], LOW);
                sleep(k);
            }
        }
        off();
        sleep(500);
    }
}

void Keed24Channel::sleep(uint32_t _time) {
    if (isr.pressed) return;
    delay(_time);
}

void Keed24Channel::set(uint8_t _pin, uint8_t _state) {
    int index = ceil((_pin + 1) / 8.0) - 1;
    int pins_mod = _pin % 8;
    if (cfg.reverse) ioBase[index]->digitalWrite(pins_mod, !_state);
    else ioBase[index]->digitalWrite(pins_mod, _state);
}

void Keed24Channel::setStateHigh(int index, ...) {
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

void Keed24Channel::setStateLow(int index, ...) {
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

void Keed24Channel::off() {
    for (int i = 0; i < cfg.pin_size; i++) {
        set(cfg.pin_ptr[i], LOW);
    }
}

void Keed24Channel::on() {
    for (int i = 0; i < cfg.pin_size; i++) {
        set(cfg.pin_ptr[i], HIGH);
    }
}

