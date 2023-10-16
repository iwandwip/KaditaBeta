#include <Kadita.h>

/*macros*/
#define LDR_UP      0
#define LDR_DOWN    1
#define LDR_LEFT    2
#define LDR_RIGHT   3
#define LDR_NUM     4

/*function prototype*/
void sensorRoutine();
void debug();

/*class instance*/
LiquidCrystal_I2C lcd(0x27, 16, 2);

SensorModule sensor;
BTS7960 driverA(3, 4, 5, 6);
BTS7960 driverB(7, 8, 9, 10);

DigitalOut buzzer(2);
DigitalOut ledRed(11);
DigitalOut ledGreen(12);

/*variables*/
float ldrValue[LDR_NUM];

void setup() {
    Serial.begin(9600);
    sensor.addModule(new LDRSens(A0));
    sensor.addModule(new LDRSens(A1));
    sensor.addModule(new LDRSens(A2));
    sensor.addModule(new LDRSens(A3));
    sensor.init();
    lcd.init();
    lcd.backlight();
}

void loop() {
    sensor.update(sensorRoutine);
    debug();
}

void sensorRoutine() {
    for (uint8_t i = 0; i < LDR_NUM; i++) {
        sensor.getModule(i)->getValue(&ldrValue[i]);
    }
}

void debug() {
    Serial.print("|ldrUp: ");
    Serial.print(ldrValue[LDR_UP]);
    Serial.print("|ldrDown: ");
    Serial.print(ldrValue[LDR_DOWN]);
    Serial.print("|ldrLeft: ");
    Serial.print(ldrValue[LDR_LEFT]);
    Serial.print("|ldrRight: ");
    Serial.print(ldrValue[LDR_RIGHT]);
    Serial.println();
}