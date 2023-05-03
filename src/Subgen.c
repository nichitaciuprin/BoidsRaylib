#include "Subgen.h"

#define MAX 1000000000

int Subgen_Next(Subgen* subgen)
{
	if (!subgen->si--) subgen->si = 54;
	if (!subgen->sj--) subgen->sj = 54;
    int x = subgen->state[subgen->si] - subgen->state[subgen->sj];
	if (x < 0) x += MAX;
	return subgen->state[subgen->si] = x;
}
Subgen Subgen_Create(int seed)
{
    Subgen subgen;

    subgen.si = 0;
    subgen.sj = 24;
    subgen.seed = seed;

    int p2 = 1;
	subgen.state[0] = seed % MAX;
	for (int i = 1, j = 21; i < 55; i++, j += 21)
    {
		if (j >= 55) j -= 55;
		subgen.state[j] = p2;
        p2 = seed - p2;
		if (p2 < 0) p2 += MAX;
		seed = subgen.state[j];
	}
	for (int i = 0; i < 165; i++)
        Subgen_Next(&subgen);

    return subgen;
}
float Subgen_FractionUnsigned(Subgen* subgen)
{
    return Subgen_Next(subgen) / (float)MAX;
}
float Subgen_FractionSigned(Subgen* subgen)
{
    return Subgen_FractionUnsigned(subgen) * 2 - 1;
}
float Subgen_Range(Subgen* subgen, float min, float max)
{
    return min + ((max - min) * Subgen_FractionUnsigned(subgen));
}