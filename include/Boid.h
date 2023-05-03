#pragma once

#include "MyVector2.h"
#include "AABB.h"
#include "Subgen.h"

typedef struct Boid
{
    MyVector2 pos;
    MyVector2 vel;
} Boid;

Boid Boid_Create(AABB* aabb, Subgen* subgen);
void Boid_Update(Boid* boids, int boidsLength, AABB* aabb, float deltaTime);
void Boid_Print(Boid* boid);