/*
 *  io-expander.h
 *
 *  io expander module header
 *  Created on: 2023. 4. 3
 */

#ifndef KADITA_DOT_MATRIX_H
#define KADITA_DOT_MATRIX_H

#include "Arduino.h"
#include "MD_MAX72xx.h"
#include "SPI.h"

class DOTMatrix : public MD_MAX72XX {
private:
    uint8_t addr;
public:
    using MD_MAX72XX::MD_MAX72XX;
};

#endif  // KADITA_DOT_MATRIX_H
