#define BOID_COUNT 300

typedef struct BoidCache
{
    Vector2 vec1;
    Vector2 vec2;
    Vector2 vec3;
    int count1;
    int count2;
}
BoidCache;

typedef struct UpdateCache
{
    BoidCache boidCaches[BOID_COUNT];
}
UpdateCache;

typedef struct Boid
{
    Vector2 position;
    Vector2 velocity;
}
Boid;

typedef struct State
{
    Box box;
    Boid boids[BOID_COUNT];
}
State;

UpdateCache* updateCache;

const float minSpeed = 9;
const float maxSpeed = 15;
const float range1 = 5;
const float range2 = 5;
const float range3 = 2;
const float rangeSquared1 = range1 * range1;
const float rangeSquared2 = range2 * range2;
const float rangeSquared3 = range3 * range3;
const float power1 = 0.01;
const float power2 = 0.01;
const float power3 = 0.04;
const float acc = 10;

void PrintBoid(Boid* boid)
{
    PrintVector2Hex(boid->position);
    PrintVector2Hex(boid->velocity);
}

void ClearCache()
{
    memset(updateCache, 0, sizeof(UpdateCache));
}
Vector2 TargetVelocity(Boid* boids, BoidCache* boidCaches, int boidIndex)
{
    Boid* boid = &boids[boidIndex];
    BoidCache* boidCache = &boidCaches[boidIndex];

    Vector2 result = boid->velocity;

    Vector2 vec1 = boidCache->vec1;
    Vector2 vec2 = boidCache->vec2;
    Vector2 vec3 = boidCache->vec3;
    int count1 = boidCache->count1;
    int count2 = boidCache->count2;

    if (count1 != 0)
    {
        vec1 = Vector2Div(vec1, count1);
        vec1 = Vector2Sub(vec1, boid->position);
    }
    if (count2 != 0)
    {
        vec2 = Vector2Div(vec2, count2);
        vec2 = Vector2Sub(vec2, boid->velocity);
    }

    vec1 = Vector2Mul(vec1, power1);
    vec2 = Vector2Mul(vec2, power2);
    vec3 = Vector2Mul(vec3, power3);

    result = Vector2Add(result, vec1);
    result = Vector2Add(result, vec2);
    result = Vector2Add(result, vec3);

    result = Vector2ClampLength(result, minSpeed, maxSpeed);

    return result;
}
void CalculatePair(Boid* boids, BoidCache* boidsCaches, int boid1Index, int boid2Index)
{
    Boid* boid1 = &boids[boid1Index];
    Boid* boid2 = &boids[boid2Index];

    BoidCache* boid1Cache = &boidsCaches[boid1Index];
    BoidCache* boid2Cache = &boidsCaches[boid2Index];

    Vector2 diff = Vector2Sub(boid1->position, boid2->position);
    float distSquared = diff.x * diff.x + diff.y * diff.y;
    float dist = sqrtf(distSquared);

    // COHESION
    if (distSquared >= rangeSquared1) return;

    boid1Cache->vec1 = Vector2Add(boid1Cache->vec1, boid2->position); boid1Cache->count1++;
    boid2Cache->vec1 = Vector2Add(boid2Cache->vec1, boid1->position); boid2Cache->count1++;

    // ALIGHMENT
    if (distSquared >= rangeSquared2) return;

    boid1Cache->vec2 = Vector2Add(boid1Cache->vec2, boid2->velocity); boid1Cache->count2++;
    boid2Cache->vec2 = Vector2Add(boid2Cache->vec2, boid1->velocity); boid2Cache->count2++;

    // SEPARATION
    if (distSquared >= rangeSquared3) return;

    float normFraction = 1.0f / dist;
    Vector2 normDiff = (Vector2) { diff.x * normFraction, diff.y * normFraction };
    float dist2 = range3 - dist;
    normDiff = Vector2Mul(normDiff, dist2);

    boid1Cache->vec3 = Vector2Add(boid1Cache->vec3, normDiff);
    boid2Cache->vec3 = Vector2Add(boid2Cache->vec3, Vector2Negate(normDiff));
}

Boid CreateBoid(Box* box, Subgen* subgen)
{
    float randSpeed = SubgenRange(subgen, minSpeed, maxSpeed);
    Vector2 randDirection = RandNormDir(subgen);

    Vector2 pos = RandomPointInside(subgen, box);
    Vector2 vel = Vector2Mul(randDirection, randSpeed);

    Boid boid;
    boid.position = pos;
    boid.velocity = vel;

    return boid;
}
void UpdateBoids(Boid* boids, int boidsLength, Box* box, float deltaTime)
{
    ClearCache();

    BoidCache* boidCaches = updateCache->boidCaches;

    // iterating unique pairs
    for (int i = 0;   i < boidsLength; i++)
    for (int j = i+1; j < boidsLength; j++)
        CalculatePair(boids, boidCaches, i, j);

    for (int i = 0; i < boidsLength; i++)
    {
        Boid* boid = &boids[i];

        Vector2 targetVelocity = TargetVelocity(boids, boidCaches, i);
        Vector2 oldVelocity = boid->velocity;
        Vector2 newVelocity = Vector2MoveTowards(boid->velocity, targetVelocity, acc * deltaTime);
        boid->position = Vector2UpdatePositionAdvanced(boid->position, oldVelocity, newVelocity, deltaTime);
        boid->position = WrapAround(box, boid->position);
        boid->velocity = newVelocity;
    }
}

State* CreateState()
{
    State* state = (State*)malloc(sizeof(State));
    updateCache = (UpdateCache*)malloc(sizeof(UpdateCache));;

    Subgen subgen = SubgenCreate(0);

    state->box.p0 = (Vector2){ 0, 0 };
    state->box.p1 = (Vector2){ 50, 50 };

	for (int i = 0; i < BOID_COUNT; i++)
		state->boids[i] = CreateBoid(&state->box, &subgen);

    return state;
}
void UpdateState(State* state, float deltaTime)
{
    UpdateBoids(state->boids, BOID_COUNT, &state->box, deltaTime);
}
void DestroyState(State* state)
{
    free(state);
    free(updateCache);
}
