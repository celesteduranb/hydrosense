#include <Arduino.h>
#include "sensors.h"
#include "thresholds.h"

const int SENSOR_PIN = 34;
const int N_SAMPLES = 20;

float readHumidity() {

    long sum = 0;

    for (int i = 0; i < N_SAMPLES; i++) {
        sum += analogRead(SENSOR_PIN);
        delay(10);
    }

    int average = sum / N_SAMPLES;

    float humidity = map(
        average,
        ADC_SECO,
        ADC_SATURADO,
        0,
        100
    );

    humidity = constrain(humidity, 0, 100);

    return humidity;
}