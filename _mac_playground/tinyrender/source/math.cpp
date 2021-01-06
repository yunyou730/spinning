#include "math.hpp"

const float PI = 3.1415926f;

float deg2Rad(float deg)
{
    return PI * deg / 180.f;
}

float rad2Deg(float rad)
{
    return 180.f / PI * rad;
}
