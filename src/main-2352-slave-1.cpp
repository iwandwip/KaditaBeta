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
DigitalOut buzzer(2);
DigitalOut ledRed(11);
DigitalOut ledGreen(12);

/* variables */

void setup() {
    Serial.begin(9600);
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