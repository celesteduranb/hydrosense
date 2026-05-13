#include "state_machine.h"
#include "thresholds.h"

SoilState evaluateHumidity(float humidity) {

    if (humidity < HUMIDITY_DRY_THRESHOLD) {
        return DRY;
    }

    if (humidity > HUMIDITY_SATURATED_THRESHOLD) {
        return SATURATED;
    }

    return NORMAL;
}