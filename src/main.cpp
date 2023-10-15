#include <Kadita.h>

IOExpander io(0x27);

void setup() {
    Serial.begin(9600);
    io.pinMode(P1, OUTPUT);
    io.pinMode(P2, OUTPUT);
    io.pinMode(P3, INPUT);
    io.pinMode(P4, INPUT);
    if (!io.begin()) Serial.println("Failed");
}

void loop() {
    io.digitalWrite(P1, HIGH);
    io.digitalWrite(P2, LOW);

    int stateP3 = io.digitalRead(P3);
    int stateP4 = io.digitalRead(P4);
}
