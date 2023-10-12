#include <Kadita.h>

DHTSens dht(2, DHT22);
AHTSens aht;

SoftSerial com;

float valueDHT[2], valueAHT[2];

void setup() {
    Serial.begin(9600);
    com.begin(2, 3, 9600);
    dht.init();
    aht.init();
}

void loop() {
    dht.getValue(valueDHT);
    aht.getValue(valueAHT);

    aht.update();
    dht.update();
}
