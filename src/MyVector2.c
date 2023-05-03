#include "MyVector2.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Helper.h"

void MyVector2_PrintVector2Hex(MyVector2 v1)
{
    Helper_PrintFloatHex(v1.x);
    Helper_PrintFloatHex(v1.y);
}
bool MyVector2_IsZero(MyVector2 v1)
{
    return v1.x == 0 && v1.y == 0;
}
bool MyVector2_Equal(MyVector2 v1, MyVector2 v2)
{
    return v1.x == v2.x && v1.y == v2.y;
}
MyVector2 MyVector2_Zero()                           { return (MyVector2) { 0.0f, 0.0f }; }
MyVector2 MyVector2_Add(MyVector2 v1, MyVector2 v2)  { return (MyVector2) { v1.x + v2.x , v1.y + v2.y }; }
MyVector2 MyVector2_Sub(MyVector2 v1, MyVector2 v2)  { return (MyVector2) { v1.x - v2.x , v1.y - v2.y }; }
MyVector2 MyVector2_Mul(MyVector2 v1, float value)   { return (MyVector2) { v1.x * value, v1.y * value }; }
MyVector2 MyVector2_Div(MyVector2 v1, float value)   { return (MyVector2) { v1.x / value, v1.y / value }; }
MyVector2 MyVector2_Abs(MyVector2 v1)                { return (MyVector2) { fabs(v1.x), fabs(v1.y) }; }
MyVector2 MyVector2_Negate(MyVector2 v1)             { return (MyVector2) { -v1.x,-v1.y }; }
float MyVector2_Length(MyVector2 v)
{
    float distSquared = v.x*v.x + v.y*v.y;
    float dist = sqrtf(distSquared);
    return dist;
}
float MyVector2_LengthSquared(MyVector2 v)
{
    float distSquared = v.x*v.x + v.y*v.y;
    return distSquared;
}
float MyVector2_Angle(MyVector2 v)
{
    // v ( 0, 1) =  0.000000
    // v ( 1, 0) = -1.570796
    // v ( 0,-1) = -3.141593
    // v (-1, 0) =  1.570796
    return MyVector2_IsZero(v) ? 0 : atan2f(v.y,v.x) - M_PI_2;
}
float MyVector2_Distance(MyVector2 v1, MyVector2 v2)
{
    MyVector2 diff = MyVector2_Sub(v1,v2);
    return MyVector2_Length(diff);
}
MyVector2 MyVector2_Normalized(MyVector2 v)
{
    float dist = MyVector2_Length(v);
    float t = 1.0f / dist;
    return (MyVector2) { v.x*t , v.y*t };
}
MyVector2 MyVector2_RandNormDir(Subgen* subgen)
{
    float x = Subgen_FractionSigned(subgen);
    float y = Subgen_FractionSigned(subgen);
    MyVector2 result = {x,y};
    return MyVector2_Normalized(result);
}
MyVector2 MyVector2_ClampLength(MyVector2 v1, float min, float max)
{
    float length = MyVector2_Length(v1);
    if (length > max)
        return MyVector2_Mul(v1,(max/length));
    if (length < min)
        return MyVector2_Mul(v1,(min/length));
    return v1;
}
MyVector2 MyVector2_Rotate(MyVector2 v, float angle)
{
    MyVector2 result = MyVector2_Zero();
    float cosres = cosf(angle);
    float sinres = sinf(angle);
    result.x = v.x*cosres - v.y*sinres;
    result.y = v.x*sinres + v.y*cosres;
    return result;
}
MyVector2 MyVector2_MoveTowards(MyVector2 fromVec, MyVector2 toVec, float delta)
{
    if (MyVector2_Equal(fromVec,toVec)) return fromVec;
    MyVector2 diff = MyVector2_Sub(toVec,fromVec);
    float dist = MyVector2_Length(diff);
    if (dist <= delta) return toVec;
    MyVector2 dir = MyVector2_Normalized(diff);
    MyVector2 moveVec = MyVector2_Mul(dir,delta);
    return MyVector2_Add(fromVec,moveVec);
}
MyVector2 MyVector2_Snap(MyVector2 a, MyVector2 b, float range) { return MyVector2_Distance(a,b) > range ? a : b; } //1E-2f
MyVector2 MyVector2_PositionUpdate_Simple(MyVector2 position, MyVector2 velocity, float deltaTime)
{
    // result = position + velocity * deltaTime
    MyVector2 result;
    result = velocity;
    result = MyVector2_Mul(result,deltaTime);
    result = MyVector2_Add(result,position);
    return result;
}
MyVector2 MyVector2_PositionUpdate_Advanced(MyVector2 position, MyVector2 oldVelocity, MyVector2 newVelocity, float deltaTime)
{
    // result = position + (oldVelocity+velocityNew)/2 * deltaTime
    MyVector2 result;
    result = oldVelocity;
    result = MyVector2_Add(result,newVelocity);
    result = MyVector2_Div(result,2);
    result = MyVector2_Mul(result,deltaTime);
    result = MyVector2_Add(result,position);
    return result;
}