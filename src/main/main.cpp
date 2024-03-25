#include "Base.h"
#include "Helper.h"
#include "Update.h"
#include "Render.h"

int main()
{
    State* state = CreateState();

    CreateWindow();
    RenderState(state);

    long timeStep = 20;
    int endTime = clock() + timeStep;
    float deltaTime = timeStep / 1000.0f;

    while (true)
    {
        long timeNow;

        timeNow = clock();
        if (endTime <= timeNow)
        {
            endTime = timeNow + timeStep;
            UpdateState(state, deltaTime);
            RenderState(state);
        }

        timeNow = clock();
        long haltTime = endTime - timeNow;
        haltTime -= 2; // gives time for end loop
        if (haltTime > 0)
            Sleep(haltTime);

        while (clock() < endTime)
            if (WindowShouldClose()) break;
        if (WindowShouldClose()) break;
    }

    DestroyState(state);
    DestroyWindow();

	return 0;
}
