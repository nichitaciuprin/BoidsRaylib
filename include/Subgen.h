#pragma once

typedef struct Subgen
{
    int state[55];
    int si;
    int sj;
    int seed;
} Subgen;

Subgen Subgen_Create(int seed);
int Subgen_Next(Subgen* subgen);
float Subgen_FractionUnsigned(Subgen* subgen);
float Subgen_FractionSigned(Subgen* subgen);
float Subgen_Range(Subgen* subgen, float min, float max);