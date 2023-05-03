#include "Boid.h"

#define GAMEWORLD_BOIDSCOUNT 300

typedef struct GameWorld
{
    AABB aabb;
    Boid boids[GAMEWORLD_BOIDSCOUNT];
} GameWorld;

GameWorld GameWorld_Create()
{
    GameWorld gameWorld;

    Subgen subgen = Subgen_Create(0);
    gameWorld.aabb.p0 = (MyVector2){ 0, 0 };
    gameWorld.aabb.p1 = (MyVector2){ 50, 50 };
	for (int i = 0; i < GAMEWORLD_BOIDSCOUNT; i++)
		gameWorld.boids[i] = Boid_Create(&gameWorld.aabb,&subgen);

    return gameWorld;
}
void GameWorld_Update(GameWorld* gameWorld, long deltaTimeInMilliseconds)
{
    float deltaTimeInSeconds = ((float)deltaTimeInMilliseconds)/1000;
    Boid_Update(gameWorld->boids,GAMEWORLD_BOIDSCOUNT,&gameWorld->aabb,deltaTimeInSeconds);
}