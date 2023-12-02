/*
 *  Keed16Channel.cpp
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#include "Keed16Channel.h"

Keed16Channel::Keed16Channel()
        : chTimer(0),
          sequence(0) {}

void Keed16Channel::init() {

}

void Keed16Channel::update() {

}

void Keed16Channel::run(IOExpander **_ioBase, uint8_t _ioNum) {
    ioBase = _ioBase;
    ioNum = _ioNum;
    taskTemp = getSequence(sequence);
    (this->*taskTemp)();
    if (sequence < 3) sequence++;
    else sequence = 0;
}

void (Keed16Channel::*Keed16Channel::getSequence(uint8_t index))() {
    switch (index) {
        case 0: return &Keed16Channel::taskSequence0;
        case 1: return &Keed16Channel::taskSequence1;
        case 2: return &Keed16Channel::taskSequence2;
        case 3: return &Keed16Channel::taskSequence3;
    }
    return nullptr;
}

void Keed16Channel::taskSequence0() {
    for (int i = 20; i >= 8; i -= 4) {
        blink(i);
    }
}

void Keed16Channel::taskSequence1() {
    for (int i = 20; i >= 8; i -= 4) {
        snake(i);
    }
}

void Keed16Channel::taskSequence2() {
    for (int i = 20; i >= 8; i -= 4) {
        snakeReverse(i);
    }
}

void Keed16Channel::taskSequence3() {
    for (int i = 20; i >= 8; i -= 4) {
        snake(i);
        snakeReverse(i);
    }
}

void Keed16Channel::blink(uint32_t _delay) {
    for (int i = 0; i < IO_EXPANDER_NUM; i++) {
        ioBase[IO_EXPANDER_0]->digitalWrite(i, LOW);
    }
    for (int i = 0; i < IO_EXPANDER_NUM; i++) {
        ioBase[IO_EXPANDER_1]->digitalWrite(i, LOW);
    }
    delay(_delay);
    for (int i = 0; i < IO_EXPANDER_NUM; i++) {
        ioBase[IO_EXPANDER_0]->digitalWrite(i, HIGH);
    }
    for (int i = 0; i < IO_EXPANDER_NUM; i++) {
        ioBase[IO_EXPANDER_1]->digitalWrite(i, HIGH);
    }
    delay(_delay);
}

void Keed16Channel::snake(uint32_t _delay) {
    for (int i = 0; i < ioNum; i++) {
        for (int j = 0; j < 8; j++) {
            ioBase[i]->digitalWrite(j, LOW);
            delay(_delay);
        }
    }
    for (int i = 0; i < ioNum; i++) {
        for (int j = 0; j < 8; j++) {
            ioBase[i]->digitalWrite(j, HIGH);
            delay(_delay);
        }
    }
}

void Keed16Channel::snakeReverse(uint32_t _delay) {
    for (int i = 2; i > 0; i--) {
        for (int j = 8; j > 0; j--) {
            ioBase[i - 1]->digitalWrite(j - 1, LOW);
            delay(_delay);
        }
    }
    for (int i = 2; i > 0; i--) {
        for (int j = 8; j > 0; j--) {
            ioBase[i - 1]->digitalWrite(j - 1, HIGH);
            delay(_delay);
        }
    }
}
