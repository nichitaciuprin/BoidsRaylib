#include "AABB.h"
#include "MyVector2.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Helper.h"

float AABB_MinX(AABB* aabb) { return fminf(aabb->p0.x,aabb->p1.x); }
float AABB_MinY(AABB* aabb) { return fminf(aabb->p0.y,aabb->p1.y); }
float AABB_MaxX(AABB* aabb) { return fmaxf(aabb->p0.x,aabb->p1.x); }
float AABB_MaxY(AABB* aabb) { return fmaxf(aabb->p0.y,aabb->p1.y); }
MyVector2 AABB_Size(AABB* aabb) { MyVector2 duno = MyVector2_Sub(aabb->p0,aabb->p1); return MyVector2_Abs(duno); }
float AABB_RandPointInside_X(Subgen* subgen, AABB* aabb) { return Subgen_Range(subgen, AABB_MinX(aabb), AABB_MaxX(aabb) ); }
float AABB_RandPointInside_Y(Subgen* subgen, AABB* aabb) { return Subgen_Range(subgen, AABB_MinY(aabb), AABB_MaxY(aabb) ); }
MyVector2 AABB_RandPointInside(Subgen* subgen, AABB* aabb) { return (MyVector2){ AABB_RandPointInside_X(subgen,aabb), AABB_RandPointInside_Y(subgen,aabb) }; }
MyVector2 AABB_WrapAround(AABB* aabb, MyVector2 point)
{
    MyVector2 size = AABB_Size(aabb);
    if      (point.x < AABB_MinX(aabb)) point.x += size.x;
    else if (point.x > AABB_MaxX(aabb)) point.x -= size.x;
    if      (point.y < AABB_MinY(aabb)) point.y += size.y;
    else if (point.y > AABB_MaxY(aabb)) point.y -= size.y;
    return point;
}