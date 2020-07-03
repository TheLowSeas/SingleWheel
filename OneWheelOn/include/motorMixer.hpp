#pragma once
#include <clamp.h>

int motorMixer(float PIDOut, float range)
{
    int motorData;
    float normalized;

    PIDOut = clampF(PIDOut, -1 * range, range);
    normalized = PIDOut / range;

    motorData = normalized * 400 + 1500;

    return motorData;
}
