#include <KaditaIoT.h>

DigitalOut led(LED_BUILTIN);

void setup() {
    Serial.begin(9600);
}

void loop() {
    led.toggle();
    delay(100);
}