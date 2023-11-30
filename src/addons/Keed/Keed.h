/*
 *  Keed.h
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef KEED_H
#define KEED_H

#include "Kadita.h"
#include "KeedConfig.h"

class KeedWelcomingLight {
private:
public:
    KeedWelcomingLight() {

    }

    cfg_error_t init(uint8_t channel, uint8_t version) {
        return INITIALIZE_ERROR;
    }
};

#endif // KEED_H