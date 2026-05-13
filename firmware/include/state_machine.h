#pragma once

enum SoilState {
    DRY,
    NORMAL,
    SATURATED
};

SoilState evaluateHumidity(float humidity);