#pragma once

#include <stdbool.h>
#include "Subgen.h"

typedef struct MyVector2
{
    float x;
    float y;
} MyVector2;

MyVector2 MyVector2_Zero();
void MyVector2_PrintVector2Hex(MyVector2 v1);
bool MyVector2_IsZero(MyVector2 v1);
bool MyVector2_Equal(MyVector2 v1, MyVector2 v2);
MyVector2 MyVector2_Zero();
MyVector2 MyVector2_Add(MyVector2 v1, MyVector2 v2);
MyVector2 MyVector2_Sub(MyVector2 v1, MyVector2 v2);
MyVector2 MyVector2_Mul(MyVector2 v1, float value);
MyVector2 MyVector2_Div(MyVector2 v1, float value);
MyVector2 MyVector2_Abs(MyVector2 v1);
MyVector2 MyVector2_Negate(MyVector2 v1);
float MyVector2_Length(MyVector2 v);
float MyVector2_LengthSquared(MyVector2 v);
float MyVector2_Angle(MyVector2 v);
float MyVector2_Distance(MyVector2 v1, MyVector2 v2);
MyVector2 MyVector2_Normalized(MyVector2 v);
MyVector2 MyVector2_RandNormDir(Subgen* subgen);
MyVector2 MyVector2_ClampLength(MyVector2 v1, float min, float max);
MyVector2 MyVector2_Rotate(MyVector2 v, float angle);
MyVector2 MyVector2_MoveTowards(MyVector2 fromVec, MyVector2 toVec, float delta);
MyVector2 MyVector2_Snap(MyVector2 a, MyVector2 b, float range); //1E-2f
MyVector2 MyVector2_PositionUpdate_Simple(MyVector2 position, MyVector2 velocity, float deltaTime);
MyVector2 MyVector2_PositionUpdate_Advanced(MyVector2 position, MyVector2 oldVelocity, MyVector2 newVelocity, float deltaTime);