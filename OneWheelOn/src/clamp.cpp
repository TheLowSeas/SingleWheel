#include <clamp.h>

int clampI(int input, int min, int max)
{

    int i;

    if (input > max)
        {
            i = max;
        }
    else if (input < min)
        {
            i = min;
        }
    else
        {
            i = input;
        }

    return i;
}

float clampF(float input, float min, float max)
{

    float i;

    if (input > max)
        {
            i = max;
        }
    else if (input < min)
        {
            i = min;
        }
    else
        {
            i = input;
        }

    return i;
}