/*
 *  project-automatic-gate-barrier
 *
 *  project number: 2352
 *  Created on: 2023. 4. 3
 */

#define AUTOMATIC_GATE_BARRIER_MASTER
#ifdef AUTOMATIC_GATE_BARRIER_MASTER

#include <Kadita.h>

/*macros*/
#define DEVICE_ADDRESS 0xAA

/* function prototype */
void debug();

/* class instance */

LoRaModule lora;

DigitalOut buzzer(A4);
DigitalOut ledRed(A1);
DigitalOut ledGreen(A3);
DigitalOut ledYellow(A2);

/* variables */

void setup() {
    Serial.begin(9600);
    lora.init();
    ledRed.on();
    ledGreen.on();
    ledYellow.on();
}

void loop() {
    lora.clearData();
    lora.addData(DEVICE_ADDRESS);
    lora.sendData();

    debug();
}

void debug() {
}

#endif // AUTOMATIC_GATE_BARRIER_MASTER