#include <Kadita.h>

SoftSerial softCom;
HardSerial hardCom;

void setup() {
    Serial.begin(9600);
    softCom.begin(2, 3, 9600);
    hardCom.begin();
}

void loop() {
}
