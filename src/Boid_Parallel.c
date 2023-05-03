#include "AABB.h"
#include <pthread.h>
#include <stdio.h>

const float minSpeed = 9;
const float maxSpeed = 15;
const float range_1 = 5;
const float range_2 = 5;
const float range_3 = 2;
const float rangeSquared_1 = range_1*range_1;
const float rangeSquared_2 = range_2*range_2;
const float rangeSquared_3 = range_3*range_3;
const float power1 = 0.01;
const float power2 = 0.01;
const float power3 = 0.04;

typedef struct Boid
{
    MyVector2 pos;
    MyVector2 vel;
    MyVector2 velNew;
} Boid;

typedef struct BoidTask
{
    pthread_t thread;
    Boid* boids;
    int boidsCount;
    int startIndex;
    int count;
    volatile bool enabled;
} BoidTask;

void* BoidTask_Thread(void* arg);
void Boid_Update_Velocity(int boidIndex, Boid* boids, int boidsCount);
void Update_Position(Boid* boid, AABB* aabb, float deltaTime);
void Boid_Update(Boid* boids, int boidsLength, AABB* aabb, float deltaTime);
Boid Boid_Create(AABB* aabb, Subgen* subgen);
void Boid_Print(Boid* boid);
void Boid_MaybeInit();

void BoidTask_InitThread(BoidTask* boidTask);
void BoidTask_Start(BoidTask* boidTask, Boid* boids, int boidsCount, int index, int count);
void BoidTask_Wait(BoidTask* boidTask);
void* BoidTask_Thread(void* arg);

volatile bool initWas = false;
BoidTask boidTask1;
BoidTask boidTask2;
BoidTask boidTask3;
BoidTask boidTask4;

void BoidTask_InitThread(BoidTask* boidTask)
{
    // pthread_mutex_init(&boidTask->lock, NULL);
    // pthread_cond_init(&boidTask->cond, NULL);
    pthread_create(&boidTask->thread, NULL, BoidTask_Thread, boidTask);
}
void BoidTask_Start(BoidTask* boidTask, Boid* boids, int boidsCount, int index, int count)
{
    boidTask->boids = boids;
    boidTask->boidsCount = boidsCount;
    boidTask->startIndex = index;
    boidTask->count = count;
    boidTask->enabled = true;
}
void BoidTask_Wait(BoidTask* boidTask)
{
    // while (boidTask->enabled) { Sleep(10); }
    while (boidTask->enabled) { }
}
void* BoidTask_Thread(void* arg)
{
    BoidTask* boidTask = (BoidTask*)arg;
    while (true)
    {
        while (!boidTask->enabled) { }

        Boid* boids = boidTask->boids;
        int length = boidTask->startIndex + boidTask->count;
        for (int i = boidTask->startIndex; i < length; i++)
            Boid_Update_Velocity(i,boids,boidTask->boidsCount);

        boidTask->enabled = false;
    }
    return 0;
}

void Boid_MaybeInit()
{
    if (initWas) return;
    initWas = true;
    BoidTask_InitThread(&boidTask1);
    BoidTask_InitThread(&boidTask2);
    BoidTask_InitThread(&boidTask3);
    BoidTask_InitThread(&boidTask4);
}
void Boid_Print(Boid* boid)
{
    MyVector2_PrintVector2Hex(boid->pos);
    MyVector2_PrintVector2Hex(boid->vel);
}
Boid Boid_Create(AABB* aabb, Subgen* subgen)
{
    float randSpeed = Subgen_Range(subgen,minSpeed,maxSpeed);
    MyVector2 randDirection = MyVector2_RandNormDir(subgen);

    MyVector2 pos = AABB_RandPointInside(subgen,aabb);
    MyVector2 vel = MyVector2_Mul(randDirection,randSpeed);

    Boid boid;
    boid.pos = pos;
    boid.vel = vel;

    return boid;
}
void Boid_Update_Velocity(int boidIndex, Boid* boids, int boidsCount)
{
    Boid* boid = &boids[boidIndex];
    MyVector2 vec_1 = MyVector2_Zero();
    MyVector2 vec_2 = MyVector2_Zero();
    MyVector2 vec_3 = MyVector2_Zero();
    int count_1 = 0;
    int count_2 = 0;

    for (int boidIndexOther = 0; boidIndexOther < boidsCount; boidIndexOther++)
    {
        if (boidIndex == boidIndexOther) continue;
        Boid* boidOther = &boids[boidIndexOther];

        MyVector2 diff = MyVector2_Sub(boid->pos,boidOther->pos);
        float distSquared = diff.x*diff.x + diff.y*diff.y;
        float dist = sqrtf(distSquared);

        // COHESION
        if (distSquared >= rangeSquared_1) continue;

        vec_1 = MyVector2_Add(vec_1,boidOther->pos); count_1++;

        // ALIGHMENT
        if (distSquared >= rangeSquared_2) continue;

        vec_2 = MyVector2_Add(vec_2,boidOther->vel); count_2++;

        // SEPARATION
        if (distSquared >= rangeSquared_3) continue;

        float normFraction = 1.0f/dist;
        MyVector2 normDiff = (MyVector2) { diff.x*normFraction, diff.y*normFraction };
        float dist2 = range_3 - dist;
        normDiff = MyVector2_Mul(normDiff,dist2);

        vec_3 = MyVector2_Add(vec_3,normDiff);
    }

    if (count_1 != 0)
    {
        vec_1 = MyVector2_Div(vec_1,count_1);
        vec_1 = MyVector2_Sub(vec_1,boid->pos);
    }
    if (count_2 != 0)
    {
        vec_2 = MyVector2_Div(vec_2,count_2);
        vec_2 = MyVector2_Sub(vec_2,boid->vel);
    }

    vec_1 = MyVector2_Mul(vec_1,power1);
    vec_2 = MyVector2_Mul(vec_2,power2);
    vec_3 = MyVector2_Mul(vec_3,power3);

    boid->velNew = boid->vel;
    boid->velNew = MyVector2_Add(boid->velNew,vec_1);
    boid->velNew = MyVector2_Add(boid->velNew,vec_2);
    boid->velNew = MyVector2_Add(boid->velNew,vec_3);
    boid->velNew = MyVector2_ClampLength(boid->velNew,minSpeed,maxSpeed);
}
void Update_Position(Boid* boid, AABB* aabb, float deltaTime)
{
    MyVector2 velocityDelta = MyVector2_Mul(boid->vel,deltaTime);
    boid->pos = MyVector2_Add(boid->pos,velocityDelta);
    boid->pos = AABB_WrapAround(aabb,boid->pos);
}
void Boid_Update(Boid* boids, int boidsLength, AABB* aabb, float deltaTime)
{
    Boid_MaybeInit();

    BoidTask_Start(&boidTask1,boids,300,0,75);
    BoidTask_Start(&boidTask2,boids,300,75,75);
    BoidTask_Start(&boidTask3,boids,300,150,75);
    BoidTask_Start(&boidTask4,boids,300,225,75);
    BoidTask_Wait(&boidTask1);
    BoidTask_Wait(&boidTask2);
    BoidTask_Wait(&boidTask3);
    BoidTask_Wait(&boidTask4);

    for (int i = 0; i < boidsLength; i++)
        boids[i].vel = boids[i].velNew;

    for (int i = 0; i < boidsLength; i++)
        Update_Position(&boids[i],aabb,deltaTime);
}