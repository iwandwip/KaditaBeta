/*
 *  KeedBaseChannelTask.cpp
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#include "KeedBaseChannel.h"

void KeedBaseChannel::taskSequence0() {
    // blink ////////////////////////////////////////
    {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 15; ++j) {
                for (int k = 0; k < cfg.pin_size; k++) {
                    set(cfg.pin_ptr[k], HIGH);
                }
                sleep(cfg.delay_time);
                for (int k = 0; k < cfg.pin_size; k++) {
                    set(cfg.pin_ptr[k], LOW);
                }
                sleep(cfg.delay_time);
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
            sleep(cfg.delay_time);
            for (int j = 0; j < (cfg.pin_size / 2); j++) {
                set(cfg.pin_ptr[j], LOW);
            }
            sleep(cfg.delay_time);
        }
        sleep(50);
        for (int i = 0; i < 4; ++i) {
            for (int j = (cfg.pin_size / 2); j < cfg.pin_size; j++) {
                set(cfg.pin_ptr[j], HIGH);
            }
            sleep(cfg.delay_time);
            for (int j = (cfg.pin_size / 2); j < cfg.pin_size; j++) {
                set(cfg.pin_ptr[j], LOW);
            }
            sleep(cfg.delay_time);
        }
        sleep(50);
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < (cfg.pin_size / 2); j++) {
                set(cfg.pin_ptr[j], HIGH);
            }
            sleep(cfg.delay_time);
            for (int j = 0; j < (cfg.pin_size / 2); j++) {
                set(cfg.pin_ptr[j], LOW);
            }
            sleep(cfg.delay_time);
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
            sleep(cfg.delay_time);
            for (int j = (cfg.pin_size / 2); j < cfg.pin_size; j++) {
                set(cfg.pin_ptr[j], LOW);
            }
            sleep(cfg.delay_time);
        }
        sleep(50);
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < (cfg.pin_size / 2); j++) {
                set(cfg.pin_ptr[j], HIGH);
            }
            sleep(cfg.delay_time);
            for (int j = 0; j < (cfg.pin_size / 2); j++) {
                set(cfg.pin_ptr[j], LOW);
            }
            sleep(cfg.delay_time);
        }
        sleep(50);
        for (int i = 0; i < 4; ++i) {
            for (int j = (cfg.pin_size / 2); j < cfg.pin_size; j++) {
                set(cfg.pin_ptr[j], HIGH);
            }
            sleep(cfg.delay_time);
            for (int j = (cfg.pin_size / 2); j < cfg.pin_size; j++) {
                set(cfg.pin_ptr[j], LOW);
            }
            sleep(cfg.delay_time);
        }
        off();
        sleep(500);
    }
}

void KeedBaseChannel::taskSequence1() {
    // fill 2 point ////////////////////////////////////////
    {
        for (int i = 0; i < cfg.pin_size / 2; i += 2) {
            for (int j = 0; j < 8; ++j) {
                set(cfg.pin_ptr[i], HIGH);
                set(cfg.pin_ptr[i + 1], HIGH);
                sleep(cfg.delay_time);
                set(cfg.pin_ptr[i], LOW);
                set(cfg.pin_ptr[i + 1], LOW);
                sleep(cfg.delay_time);
            }
            set(cfg.pin_ptr[i], HIGH);
            set(cfg.pin_ptr[i + 1], HIGH);
            sleep(300);
            if (i < (cfg.pin_size / 2) - 1) {
                for (int j = 0; j < 8; ++j) {
                    set(cfg.pin_ptr[(cfg.pin_size - 1) - i], HIGH);
                    set(cfg.pin_ptr[(cfg.pin_size - 1) - (i + 1)], HIGH);
                    sleep(cfg.delay_time);
                    set(cfg.pin_ptr[(cfg.pin_size - 1) - i], LOW);
                    set(cfg.pin_ptr[(cfg.pin_size - 1) - (i + 1)], LOW);
                    sleep(cfg.delay_time);
                }
                set(cfg.pin_ptr[(cfg.pin_size - 1) - i], HIGH);
                set(cfg.pin_ptr[(cfg.pin_size - 1) - (i + 1)], HIGH);
                sleep(300);
            }
        }
        for (int i = cfg.pin_size; i > 0; --i) {
            set(cfg.pin_ptr[i - 1], LOW);
            sleep(cfg.delay_time * 2);
        }
        off();
        sleep(500);
    }
}

void KeedBaseChannel::taskSequence2() {
    // fill right ////////////////////////////////////////
    {
        for (int i = cfg.pin_size; i > 0; --i) {
            for (int j = 0; j < i; j++) {
                set(cfg.pin_ptr[j], HIGH);
                sleep(cfg.delay_time * 2);
                set(cfg.pin_ptr[j], LOW);
            }
            set(cfg.pin_ptr[i - 1], HIGH);
        }
        for (int i = cfg.pin_size; i > 0; --i) {
            set(cfg.pin_ptr[i - 1], LOW);
            sleep(cfg.delay_time * 2);
        }
        off();
        sleep(500);
    }
}

void KeedBaseChannel::taskSequence3() {
    // fill in ////////////////////////////////////////
    {
        for (int j = 0; j < cfg.pin_size / 2; ++j) {
            for (int i = cfg.pin_size; i > cfg.pin_size / 2 + j; --i) {
                set(cfg.pin_ptr[i - 1], HIGH);
                set(cfg.pin_ptr[cfg.pin_size - i], HIGH);
                sleep(cfg.delay_time * 2);
                set(cfg.pin_ptr[i - 1], LOW);
                set(cfg.pin_ptr[cfg.pin_size - i], LOW);
            }
            for (int i = j; i < cfg.pin_size / 2; ++i) {
                set(cfg.pin_ptr[i + cfg.pin_size / 2], HIGH);
                set(cfg.pin_ptr[(cfg.pin_size / 2 - 1) - i], HIGH);
                sleep(cfg.delay_time * 2);
                set(cfg.pin_ptr[i + cfg.pin_size / 2], LOW);
                set(cfg.pin_ptr[(cfg.pin_size / 2 - 1) - i], LOW);
            }
            for (int i = cfg.pin_size - 1; i > cfg.pin_size / 2 + j; --i) {
                set(cfg.pin_ptr[i - 1], HIGH);
                set(cfg.pin_ptr[cfg.pin_size - i], HIGH);
                sleep(cfg.delay_time * 2);
                set(cfg.pin_ptr[i - 1], LOW);
                set(cfg.pin_ptr[cfg.pin_size - i], LOW);
            }
            set(cfg.pin_ptr[cfg.pin_size / 2 + j], HIGH);
            set(cfg.pin_ptr[(cfg.pin_size / 2 - 1) - j], HIGH);
        }
        for (int i = 0; i < cfg.pin_size / 2; ++i) {
            set(cfg.pin_ptr[i + cfg.pin_size / 2], LOW);
            set(cfg.pin_ptr[(cfg.pin_size / 2 - 1) - i], LOW);
            sleep(cfg.delay_time * 2);
        }
        off();
        sleep(500);
    }
}

void KeedBaseChannel::taskSequence4() {
    // blink 1 by 1 ////////////////////////////////////////
    {
        for (int i = 0; i < cfg.pin_size; ++i) {
            for (int j = 0; j < 4; ++j) {
                set(cfg.pin_ptr[i], HIGH);
                sleep(cfg.delay_time);
                set(cfg.pin_ptr[i], LOW);
                sleep(cfg.delay_time);
            }
            sleep(cfg.delay_time);
        }
        for (int i = cfg.pin_size; i > 0; --i) {
            for (int j = 0; j < 4; ++j) {
                set(cfg.pin_ptr[i - 1], HIGH);
                sleep(cfg.delay_time);
                set(cfg.pin_ptr[i - 1], LOW);
                sleep(cfg.delay_time);
            }
            sleep(cfg.delay_time);
        }
        off();
        sleep(500);
    }
}

void KeedBaseChannel::taskSequence5() {
    // blink 2 fill ////////////////////////////////////////
    {
        for (int j = 0; j < cfg.pin_size / 2; ++j) {
            for (int i = cfg.pin_size / 2; i > j; --i) {
                for (int k = 0; k < 4; ++k) {
                    set(cfg.pin_ptr[i - 1], HIGH);
                    set(cfg.pin_ptr[cfg.pin_size - i], HIGH);
                    sleep(cfg.delay_time);
                    set(cfg.pin_ptr[i - 1], LOW);
                    set(cfg.pin_ptr[cfg.pin_size - i], LOW);
                    sleep(cfg.delay_time);
                }
            }
            set(cfg.pin_ptr[j], HIGH);
            set(cfg.pin_ptr[(cfg.pin_size - 1) - j], HIGH);
        }
        off();
        sleep(500);
    }
}

void KeedBaseChannel::taskSequence6() {
    // snake and snake reverse ////////////////////////////////////////
    {
        for (float k = cfg.delay_time * 2; k >= cfg.delay_time; k -= cfg.delay_time) {
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

void KeedBaseChannel::taskSequence7() {
    auto setRandomLed = [&](int value) -> void {
        int data[cfg.pin_size];
        for (int i = 0; i < cfg.pin_size; ++i) {
            data[i] = !value;
        }
        for (int i = 0; i < cfg.pin_size; ++i) {
            int index;
            do {
                index = random(cfg.pin_size);
            } while (data[index] == value);
            data[index] = value;
            for (int j = 0; j < cfg.pin_size; ++j) {
                set(cfg.pin_ptr[j], data[j]);
            }
            sleep(cfg.delay_time);
        }
    };

    setRandomLed(HIGH);
    setRandomLed(LOW);
}

void KeedBaseChannel::taskSequence8() {
    auto setWaveLed = [&](int value) -> void {
        for (int i = 0; i < (cfg.pin_size / 2) + 2; ++i) {
            if (i < ((cfg.pin_size / 2) / 2) + 1) {
                set(cfg.pin_ptr[i], value);
                if (!((i == (cfg.pin_size / cfg.pin_size)) || (i == ((cfg.pin_size / 2) / 2)))) {
                    if (i > (cfg.pin_size / cfg.pin_size) && (i < ((cfg.pin_size / 2) / 2))) {
                        set(cfg.pin_ptr[(cfg.pin_size / 2) - i], value);
                    } else {
                        set(cfg.pin_ptr[(cfg.pin_size / 2) - (i + 1)], value);
                    }
                }
            } else {
                set(cfg.pin_ptr[i + (cfg.pin_size / 2) - 2], value);
                if (!((i + (cfg.pin_size / 2) - 2 == (cfg.pin_size - 2)) || (i + (cfg.pin_size / 2) - 2 == (cfg.pin_size / 2) + (((cfg.pin_size / 2) / 2) - 1)))) {
                    if ((i + (cfg.pin_size / 2) - 2 < (cfg.pin_size - 2)) && (i + (cfg.pin_size / 2) - 2 > (cfg.pin_size / 2) + (((cfg.pin_size / 2) / 2) - 1))) {
                        set(cfg.pin_ptr[(cfg.pin_size - (i + (cfg.pin_size / 2) - 2)) + (cfg.pin_size / 2) - 2], value);
                    } else {
                        set(cfg.pin_ptr[cfg.pin_size / 2], value);
                    }
                }
            }
            sleep(cfg.delay_time);
        }
    };

    setWaveLed(HIGH);
    setWaveLed(LOW);
}
