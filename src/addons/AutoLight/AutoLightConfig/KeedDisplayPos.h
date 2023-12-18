/*
 *  KeedDisplay.cpp
 *
 *  Kastara Electronics Embedded Development
 *  Created on: 2023. 4. 3
 */

#include "Arduino.h"

const uint8_t SPACE = 2;
const uint8_t WIDTH = 5;
const uint8_t HEIGHT = 2;
const uint8_t BASE_LOW = 0;
const uint8_t BASE_HIGH = 127 - WIDTH;

const uint8_t POS_24[24][2] = {
        {BASE_LOW + 0,   0},
        {BASE_LOW + 10,  0},
        {BASE_LOW + 10,  23},

        {BASE_LOW + 55,  2},
        {BASE_LOW + 55,  5},
        {BASE_LOW + 47,  8},
        {BASE_LOW + 43,  11},
        {BASE_LOW + 39,  14},

        {BASE_LOW + 35,  17},
        {BASE_LOW + 31,  20},
        {BASE_LOW + 27,  23},
        {BASE_LOW + 27,  26},

        {BASE_HIGH - 27, 26},
        {BASE_HIGH - 27, 23},
        {BASE_HIGH - 31, 20},
        {BASE_HIGH - 35, 17},

        {BASE_HIGH - 39, 14},
        {BASE_HIGH - 43, 11},
        {BASE_HIGH - 47, 8},
        {BASE_HIGH - 55, 5},
        {BASE_HIGH - 55, 2},

        {BASE_HIGH - 10, 23},
        {BASE_HIGH - 10, 0},
        {BASE_HIGH - 0,  0},
};

const uint8_t POS_32[32][2] = {
};