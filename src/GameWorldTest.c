#include <time.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>
#include "GameWorld.h"

#define KB32 32768
#define L1SIZE KB32

int main(void)
{
    GameWorld gameWorld = GameWorld_Create();

    long time1 = clock();
    for (int i = 0; i < 3000; i++) GameWorld_Update(&gameWorld,20);
    long time2 = clock();

    printf("Boids_C");
    printf("  ");
    Boid_Print(&gameWorld.boids[0]);
    printf(" ");
    printf("%li",time2-time1);
    printf(" \n");

	return 0;
}