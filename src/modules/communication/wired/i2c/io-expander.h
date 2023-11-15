/*  
 *  io-expander.h
 *
 *  io expander module header
 *  Created on: 2023. 4. 3
 */

#ifndef KADITA_IO_EXPANDER_H
#define KADITA_IO_EXPANDER_H

#include "Arduino.h"
#include "../../../io/input-module.h"
#include "../../../io/output-module.h"
#include "PCF8574.h"

class IOExpander : public PCF8574 {
private:
    uint8_t addr;
public:
    using PCF8574::PCF8574;
};

#endif  // KADITA_IO_EXPANDER_H
