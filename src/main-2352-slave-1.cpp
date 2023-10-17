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
#define DEVICE_ADDRESS 0xAA

/* function prototype */
void debug();

/* class instance */
HX711Sens loadCell(3, 4);

LoRaModule lora;

DigitalOut buzzer(A0);
DigitalOut ledRed(A1);
DigitalOut ledGreen(A3);
DigitalOut ledYellow(A2);

/* variables */
float weight = 0.0;

void setup() {
    Serial.begin(9600);
    loadCell.init();
    lora.init();
    ledRed.on();
    ledGreen.on();
    ledYellow.on();
}

void loop() {
    loadCell.update();
    weight = loadCell.getValue();

    lora.clearData();
    lora.addData(DEVICE_ADDRESS);
    lora.addData(weight);
    lora.sendData();

    debug();
}

void debug() {
    Serial.print("| weight: ");
    Serial.print(weight);
    Serial.println();
}

#endif // AUTOMATIC_GATE_BARRIER_SLAVE_1