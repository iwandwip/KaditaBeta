#include <iMakeBeta.h>

TimerTicks time(1000);

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (time.tick()) {
    // run every 1000ms
  }
  delay(1000);
}
