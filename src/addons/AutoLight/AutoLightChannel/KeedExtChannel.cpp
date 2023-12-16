/*
 *  KeedExtChannel.cpp
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#include "KeedExtChannel.h"

#define setHigh(...) setStateHigh(__VA_ARGS__, -1)
#define setLow(...) setStateLow(__VA_ARGS__, -1)

KeedExtChannel::KeedExtChannel()
        : sequence(0), ioTimer(40), taskTemp(nullptr),
          sequences{&KeedExtChannel::off,
                    &KeedExtChannel::taskSequence0,
                    &KeedExtChannel::taskSequence1,
                    &KeedExtChannel::taskSequence2,
                    &KeedExtChannel::taskSequence3,
                    &KeedExtChannel::taskSequence4,
                    &KeedExtChannel::taskSequence5,
                    &KeedExtChannel::taskSequence6,
                    &KeedExtChannel::on} {}

void KeedExtChannel::init(IOExpander **_ioBase, configuration_t _cfg) {
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
}

void KeedExtChannel::update() {
    if (isr.pressed) isr.pressed = false;
    (this->*taskTemp)();
}

void KeedExtChannel::run() {
    update();
}

void KeedExtChannel::setInterruptConfig(interrupt_t _cfg) {
    isr = _cfg;
}

void KeedExtChannel::changeModes() {
    if (millis() - isrTimer >= BUTTON_DEBOUNCE_TIME) {
        sequence = (sequence < ((TASK_SEQUENCE_NUM + 2) - 1)) ? sequence + 1 : 0;
        taskTemp = sequences[sequence];
        isr.num++;
        isr.pressed = true;
        isrTimer = millis();
    }
}

void KeedExtChannel::setBaseDelay(uint32_t _time) {
    ioTimer = _time;
}

void (KeedExtChannel::*KeedExtChannel::getSequence(uint8_t index))() {
    return sequences[index];
}

void KeedExtChannel::taskSequence0() {
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

void KeedExtChannel::taskSequence1() {
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

void KeedExtChannel::taskSequence2() {
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

void KeedExtChannel::taskSequence3() {
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

void KeedExtChannel::taskSequence4() {
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

void KeedExtChannel::taskSequence5() {
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

void KeedExtChannel::taskSequence6() {
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

void KeedExtChannel::sleep(uint32_t _time) {
    if (isr.pressed) return;
    delay(_time);
}

void KeedExtChannel::set(uint8_t _pin, uint8_t _state) {
    if (cfg.reverse) digitalWrite(_pin, !_state);
    else digitalWrite(_pin, _state);
}

void KeedExtChannel::setStateHigh(int index, ...) {
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

void KeedExtChannel::setStateLow(int index, ...) {
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

void KeedExtChannel::off() {
    for (int i = 0; i < cfg.pin_size; i++) {
        set(cfg.pin_ptr[i], LOW);
    }
}

void KeedExtChannel::on() {
    for (int i = 0; i < cfg.pin_size; i++) {
        set(cfg.pin_ptr[i], HIGH);
    }
}

