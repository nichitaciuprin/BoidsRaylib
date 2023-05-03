#pragma once

#include "GameWorld.h"

void GameWorldWindow_Create(GameWorld* game);
void GameWorldWindow_Render(GameWorld* game);
bool GameWorldWindow_ShouldExit();
void GameWorldWindow_Destroy();