/*
 *  KaditaIoT.h
 *
 *  Kadita lib header
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef KADITA_LIB_H
#define KADITA_LIB_H

#include "Arduino.h"

// custom external sensor: will be updated soon
#ifdef SENSOR_MODULE_H
//#include "sensor-module.h"
//#include "abstract-sens.h"
//#include "sensor-filter.h"
//
//#include "dstemperature-sens.h"
//#include "waterfloat-sens.h"
//#include "dht-sens.h"
#endif

// I/O module
#include "input-module.h"
#include "output-module.h"

// timer lib
#include "timer-duration.h"
#include "timer-task.h"

//#include "blynk-handler.h"

#endif
