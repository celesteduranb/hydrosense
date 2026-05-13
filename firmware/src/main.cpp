#include <Arduino.h>

#include "sensors.h"
#include "state_machine.h"
#include "pump.h"

void setup() {

    Serial.begin(115200);

    analogReadResolution(12);
    analogSetAttenuation(ADC_11db);

    setupPump();
}

void loop() {

    float humidity = readHumidity();

    SoilState state = evaluateHumidity(humidity);

    switch (state) {

        case DRY:
            pumpOn();
            break;

        case SATURATED:
            pumpOff();
            break;

        case NORMAL:
            pumpOff();
            break;
    }

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print("% | Pump: ");

    Serial.println(
        isPumpActive() ? "ON" : "OFF"
    );

    delay(2000);
}