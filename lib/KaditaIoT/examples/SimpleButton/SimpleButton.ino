#include <iMakeBeta.h>

DigitalIn button(3);

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (button.isPressed()) {
    Serial.print("Button pressed");
  }
  delay(1000);
}
