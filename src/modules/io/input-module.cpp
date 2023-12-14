/*  
 *  input-module.cpp
 *
 *  input module c
 *  Created on: 2023. 4. 3
 */

#include "input-module.h"

DigitalIn::DigitalIn(int pin)
        : DigitalIn(pin, INPUT_PULLUP) {}

DigitalIn::DigitalIn(int pin, int mode) {
    btnPin = pin;
    debounceTime = 0;
    count = 0;
    countMode = COUNT_FALLING;

    pinMode(btnPin, mode);

    previousSteadyState = getStateRaw();
    lastSteadyState = previousSteadyState;
    lastFlickerableState = previousSteadyState;

    lastDebounceTime = 0;
}

void DigitalIn::setInterrupt(void (*_callback)(), int mode) {
#if defined(ESP32)
    attachInterrupt(btnPin, _callback, mode);
#else
    attachInterrupt(digitalPinToInterrupt(btnPin), _callback, mode);
#endif
}

void DigitalIn::setDebounceTime(unsigned long time) {
    debounceTime = time;
}

int DigitalIn::getState() const {
    return lastSteadyState;
}

int DigitalIn::getStateRaw() const {
    return digitalRead(btnPin);
}

bool DigitalIn::isPressed(unsigned long time) {
    if (millis() - debounceTime >= time) {
        debounceTime = millis();
        return true;
    }
    return false;
}

bool DigitalIn::isPressed() const {
    if (previousSteadyState == HIGH && lastSteadyState == LOW)
        return true;
    else
        return false;
}

bool DigitalIn::isReleased() const {
    if (previousSteadyState == LOW && lastSteadyState == HIGH)
        return true;
    else
        return false;
}

void DigitalIn::setCountMode(int mode) {
    countMode = mode;
}

unsigned long DigitalIn::getCount() const {
    return count;
}

void DigitalIn::resetCount() {
    count = 0;
}

void DigitalIn::update() {
    int currentState = getStateRaw();
    unsigned long currentTime = millis();

    if (currentState != lastFlickerableState) {
        lastDebounceTime = currentTime;
        lastFlickerableState = currentState;
    }

    if ((currentTime - lastDebounceTime) >= debounceTime) {
        previousSteadyState = lastSteadyState;
        lastSteadyState = currentState;
    }

    if (previousSteadyState != lastSteadyState) {
        if (countMode == COUNT_BOTH)
            count++;
        else if (countMode == COUNT_FALLING) {
            if (previousSteadyState == HIGH && lastSteadyState == LOW)
                count++;
        } else if (countMode == COUNT_RISING) {
            if (previousSteadyState == LOW && lastSteadyState == HIGH)
                count++;
        }
    }
}
