#include <Arduino.h>
#include "pump.h"

const int RELAY_PIN = 26;

bool pumpState = false;

void setupPump() {

    pinMode(RELAY_PIN, OUTPUT);

    digitalWrite(RELAY_PIN, LOW);

    pumpState = false;
}

void pumpOn() {

    digitalWrite(RELAY_PIN, HIGH);

    pumpState = true;
}

void pumpOff() {

    digitalWrite(RELAY_PIN, LOW);

    pumpState = false;
}

bool isPumpActive() {
    return pumpState;
}