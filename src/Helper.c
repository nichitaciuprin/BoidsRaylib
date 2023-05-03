#include <Helper.h>

#include <string.h>
#include <stdio.h>

void Helper_PrintFloatHex(float f)
{
    unsigned int ui;
    memcpy(&ui, &f, sizeof (ui));
    printf("%X", ui);
}