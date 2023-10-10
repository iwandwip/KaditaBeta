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
#include "sensors/base/sensor-module.h"
#include "sensors/abstract-sens.h"
#include "sensors/dht-sens.h"
#include "sensors/aht-sens.h"
#include "sensors/ldr-sens.h"

// modules 
#include "modules/io/input-module.h"
#include "modules/io/output-module.h"

#include "modules/time/timer-duration.h"
#include "modules/time/timer-task.h"

#endif
