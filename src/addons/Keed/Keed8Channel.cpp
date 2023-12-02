/*
 *  Keed8Channel.cpp
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#include "Keed8Channel.h"

Keed8Channel::Keed8Channel() {

}

void Keed8Channel::init() {

}

void Keed8Channel::update() {

}

void Keed8Channel::run(IOExpander **ioBase, uint8_t ioNum) {
    for (int i = 0; i < IO_EXPANDER_NUM; i++) {
        ioBase[IO_EXPANDER_0]->digitalWrite(i, LOW);
    }
    for (int i = 0; i < IO_EXPANDER_NUM; i++) {
        ioBase[IO_EXPANDER_1]->digitalWrite(i, LOW);
    }
    delay(100);
    for (int i = 0; i < IO_EXPANDER_NUM; i++) {
        ioBase[IO_EXPANDER_0]->digitalWrite(i, HIGH);
    }
    for (int i = 0; i < IO_EXPANDER_NUM; i++) {
        ioBase[IO_EXPANDER_1]->digitalWrite(i, HIGH);
    }
    delay(100);
}