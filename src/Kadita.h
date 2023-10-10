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

#include "modules/input-module.h"
#include "modules/output-module.h"

#include "timer-duration.h"
#include "timer-task.h"

#endif
