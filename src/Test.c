#include "MyVector2.h"
#include "stdio.h"
#include "memory.h"

int main(void)
{
    int vecs[3];
    for (size_t i = 0; i < 3; i++)
        vecs[i] = i;
    for (size_t i = 0; i < 3; i++)
        printf("%i",vecs[i]);
    memset(vecs,0,sizeof vecs);
    for (size_t i = 0; i < 3; i++)
        printf("%i",vecs[i]);
    // MyVector2 zero = MyVector2_Zero();
    // MyVector2_PrintVector2Hex(zero);
	return 0;
}