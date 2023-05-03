#pragma once

#include "MyVector2.h"

typedef struct AABB
{
    MyVector2 p0;
    MyVector2 p1;
} AABB;

float AABB_MinX(AABB* aabb);
float AABB_MinY(AABB* aabb);
float AABB_MaxX(AABB* aabb);
float AABB_MaxY(AABB* aabb);
MyVector2 AABB_Size(AABB* aabb);
float AABB_RandPointInside_X(Subgen* subgen, AABB* aabb);
float AABB_RandPointInside_Y(Subgen* subgen, AABB* aabb);
MyVector2 AABB_RandPointInside(Subgen* subgen, AABB* aabb);
MyVector2 AABB_WrapAround(AABB* aabb, MyVector2 point);