#include <Kadita.h>

SoftSerial softCom;
HardSerial hardSerial;

void setup() {
    Serial.begin(9600);
    softCom.begin(2, 3, 9600);
    hardSerial.begin(&Serial);
}

void loop() {
}
