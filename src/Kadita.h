/*
 *  Kadita.h
 *
 *  Kadita index lib
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef KADITA_LIB_H
#define KADITA_LIB_H

#include "Arduino.h"

// custom external sensor: will be updated soon
#include "sensors/base/sensor-module.h"
#include "sensors/abstract-sens.h"
#include "sensors/aht-sens.h"
#include "sensors/bme280-sens.h"
#include "sensors/dht-sens.h"
#include "sensors/ds18b20-sens.h"
#include "sensors/flowmeter-sens.h"
#include "sensors/hx711-sens.h"
#include "sensors/ina219-sens.h"
#include "sensors/ldr-sens.h"
#include "sensors/max6675-sens.h"
#include "sensors/max31865-sens.h"
#include "sensors/tds-sens.h"
#include "sensors/ultrasonic-sens.h"
#include "sensors/voltage-sens.h"

// modules
#include "modules/communication/wired/i2c/i2c-scanner.h"
#include "modules/communication/wired/i2c/io-expander.h"

#include "modules/communication/wired/serial/soft-serial.h"
#include "modules/communication/wired/serial/hard-serial.h"

#include "modules/communication/wired/spi/dot-matrix.h"

#include "modules/communication/wireless/lora/lora-com.h"

#include "modules/driver/bts7960/bts7960.h"

#include "modules/io/input-module.h"
#include "modules/io/output-module.h"

#include "modules/time/timer-duration.h"
#include "modules/time/timer-task.h"

// external lib
//#include "LiquidCrystal_I2C.h"

#endif
