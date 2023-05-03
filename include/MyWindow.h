#pragma once

#include "MyVector2.h"
#include <raylib.h>
#include <stdbool.h>

Vector2 MyWindow_ToWindowSpace(MyVector2 v);
void MyWindow_DrawRectangleLines(int posX, int posY, int width, int height, Color color);
void MyWindow_DrawTriangle(MyVector2 v1, MyVector2 v2, MyVector2 v3, Color color);
void MyWindow_BeginDrawing();
void MyWindow_EndDrawing();
void MyWindow_Create();
void MyWindow_Destroy();
bool MyWindow_ShouldClose();