#pragma once

#include "AABB.h"
#include "Boid.h"

#define GAMEWORLD_BOIDSCOUNT 300

typedef struct GameWorld
{
    AABB aabb;
    Boid boids[GAMEWORLD_BOIDSCOUNT];
} GameWorld;

GameWorld GameWorld_Create();
void GameWorld_Update(GameWorld* gameWorld, long deltaTimeInMilliseconds);