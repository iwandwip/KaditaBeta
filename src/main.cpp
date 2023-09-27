#include <Arduino.h>
#include "output-module.h"
#include "input-module.h"

void setup() {
    Serial.begin(9600);
}

void loop() {
    Serial.println(20);
    delay(1000);
}