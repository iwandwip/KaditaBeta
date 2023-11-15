/*
 *  project-solar-tracker
 *
 *  project number: 2351
 *  Created on: 2023. 4. 3
 */

//#define SOLAR_TRACKER
#ifdef SOLAR_TRACKER

#include <Kadita.h>
#include <LiquidCrystal_I2C.h>
#include "main-2351-fuzzy-fis.h"

/* macros */
#define LDR_VALUE_UP 0
#define LDR_VALUE_DOWN 1
#define LDR_VALUE_LEFT 2
#define LDR_VALUE_RIGHT 3
#define LDR_VALUE_NUM 4

#define INA219_VALUE_SHUNT_VOLTAGE_MV 0
#define INA219_VALUE_BUS_VOLTAGE_V 1
#define INA219_VALUE_CURRENT_MA 2
#define INA219_VALUE_POWER_MW 3
#define INA219_VALUE_VALUE_NUM 4

/* function prototype */
void sensorRoutine();
void debug();

/* class instance */
LiquidCrystal_I2C lcd(0x27, 16, 2);

SensorModule sensor;
BTS7960 driverA(3, 4, 5, 6);
BTS7960 driverB(7, 8, 9, 10);

DigitalOut buzzer(2);
DigitalOut ledRed(11);
DigitalOut ledGreen(12);

/* variables */
float ldrValue[4];
float inaValueIn[4];
float inaValueOut[4];

void setup() {
    Serial.begin(9600);
    sensor.addModule(new LDRSens(A0));
    sensor.addModule(new LDRSens(A1));
    sensor.addModule(new LDRSens(A2));
    sensor.addModule(new LDRSens(A3));
    sensor.addModule(new INA219Sens(0x40));
    sensor.addModule(new INA219Sens(0x41));
    sensor.init();
    lcd.init();
    lcd.backlight();
}

void loop() {
    sensorRoutine();
    debug();

    g_fisInput[0] = 0;  // Read Input: ldrRight
    g_fisInput[1] = 0;  // Read Input: ldrLeft
    g_fisInput[2] = 0;  // Read Input: ldrUp
    g_fisInput[3] = 0;  // Read Input: ldrDown

    g_fisOutput[0] = 0;
    g_fisOutput[1] = 0;

    fis_evaluate();
}

void sensorRoutine() {
    sensor.update();
    for (uint8_t i = 0; i < LDR_VALUE_NUM; i++) {
        sensor.getModule(i).getValue(&ldrValue[i]);
        ldrValue[i] = mapF(ldrValue[i], 0, 1023, 0, 100);
    }
    sensor.getModule(5).getValue(inaValueIn);
    sensor.getModule(6).getValue(inaValueOut);
}

void debug() {
    // Serial.print("| up: ");
    // Serial.print(ldrValue[LDR_VALUE_UP]);
    // Serial.print("| down: ");
    // Serial.print(ldrValue[LDR_VALUE_DOWN]);
    // Serial.print("| left: ");
    // Serial.print(ldrValue[LDR_VALUE_LEFT]);
    // Serial.print("| right: ");
    // Serial.print(ldrValue[LDR_VALUE_RIGHT]);

    Serial.print("| LR: ");
    Serial.print(g_fisOutput[0]);
    Serial.print("| UD: ");
    Serial.print(g_fisOutput[1]);
    Serial.print("| mem: ");
    Serial.print(freeMemory());
    Serial.println();
}

#endif  // SOLAR_TRACKER