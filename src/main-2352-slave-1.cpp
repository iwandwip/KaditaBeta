/*
 *  project-automatic-gate-barrier
 *
 *  project number: 2352
 *  Created on: 2023. 4. 3
 */

#define AUTOMATIC_GATE_BARRIER_SLAVE_1
#ifdef AUTOMATIC_GATE_BARRIER_SLAVE_1

#include <Kadita.h>

/*macros*/

/* function prototype */
void sensorRoutine();
void debug();

/* class instance */
HX711Sens loadCell(3, 4);

LoRaModule lora;

DigitalOut buzzer(A0);
DigitalOut ledRed(A1);
DigitalOut ledGreen(A3);
DigitalOut ledYellow(A2);

/* variables */

void setup() {
    Serial.begin(9600);
    loadCell.init();
    lora.init();
}

void loop() {
    sensorRoutine();
    debug();
}

void sensorRoutine() {

}

void debug() {
}

#endif // AUTOMATIC_GATE_BARRIER_SLAVE_1