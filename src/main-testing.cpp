#define MAIN_TESTING_KADITA
#ifdef MAIN_TESTING_KADITA

#include <Kadita.h>

IOExpander pcfA(0x39);

DOTMatrix dot = DOTMatrix(MD_MAX72XX::FC16_HW, 21, 4);

MD_MAX72XX::PAROLA_HW;

SensorModule sensor;
float value;

void setup() {
    Serial.begin(9600);
    sensor.addModule(new MAX31865Sens(2, 3, 4, 1, MAX31865_2WIRE, 430, 100));
}

void loop() {
    sensor.update();
    sensor.getModule(0).getValue(&value);
}

#endif // MAIN_TESTING_KADITA