/*  
 *  input-module.h
 *
 *  input module header
 *  Created on: 2023. 4. 3
 */

#ifndef KADITA_IO_EXPANDER_H
#define KADITA_IO_EXPANDER_H

#include "Arduino.h"
#include "../../io/input-module.h"
#include "../../io/output-module.h"
#include "PCF8574.h"

#define COUNT_FALLING   0
#define COUNT_RISING    1
#define COUNT_BOTH      2

class IOExpander {
private:
    PCF8574* i2cPtr;
public:
    IOExpander() {
    }
};

#endif  // KADITA_IO_EXPANDER_H
