#include <MyMath.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
// #include <raymath.h>

#define MATH_M_PI_2 M_PI_2

inline float Math_Clamp(float value, float min, float max)
{
    float result = (value < min)? min : value;
    if (result > max) result = max;
    return result;
}
inline float Math_Sign(float value)
{
    if (value > 0) { return  1; }
    if (value < 0) { return -1; }
                     return  0;
}
inline float Math_Abs(float value)
{
    return abs(value);
}
inline float Math_Sqrt(float value)
{
    return sqrtf(value);
}