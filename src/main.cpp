#include <Kadita.h>

DHTSens dht(2, DHT22);

float value[2];

void setup() {
    Serial.begin(9600);
    dht.init();
}

void loop() {
    dht.getValue(value);
    dht.update();
}
