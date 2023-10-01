#include <KaditaIoT.h>

DigitalOut led(13);

void setup() {
  Serial.begin(9600);
}

void loop() {
  led.on();
  delay(1000);
  led.off();
  delay(1000);
}
