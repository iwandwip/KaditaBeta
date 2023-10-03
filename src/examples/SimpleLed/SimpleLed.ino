#include <iMakeBeta.h>

DigitalOut led(13);

void setup() {
  Serial.begin(9600);
}

void loop() {
  led.toggle();
  delay(1000);
}
