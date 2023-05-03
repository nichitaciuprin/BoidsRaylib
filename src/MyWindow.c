#include "MyWindow.h"
#include "MyVector2.h"
#include <raylib.h>
#include <stdio.h>
#include <rlgl.h>

#define MyWindow_Width 500
#define MyWindow_Height 500
#define MyWindow_Scale 10

Vector2 MyWindow_ToWindowSpace(MyVector2 v)
{
    v = MyVector2_Mul(v,MyWindow_Scale);
    v.y = MyWindow_Height - v.y;
    return (Vector2){v.x,v.y};
}
void MyWindow_DrawRectangleLines(int posX, int posY, int width, int height, Color color)
{
    posX   *= MyWindow_Scale;
    posY   *= MyWindow_Scale;
    width  *= MyWindow_Scale;
    height *= MyWindow_Scale;

    posY = MyWindow_Height - posY;
    posY -= height;
    DrawRectangleLines(posX,posY,width,height,color);
}
void MyWindow_DrawTriangle(MyVector2 v1, MyVector2 v2, MyVector2 v3, Color color)
{
    Vector2 rv1 = MyWindow_ToWindowSpace(v1);
    Vector2 rv2 = MyWindow_ToWindowSpace(v2);
    Vector2 rv3 = MyWindow_ToWindowSpace(v3);
    DrawTriangle(rv1,rv2,rv3,color);
}
void MyWindow_BeginDrawing()
{
    BeginDrawing();
    ClearBackground(BLACK);
    DrawFPS(0,0);
}
void MyWindow_EndDrawing()
{
    EndDrawing();
}
void MyWindow_Create()
{
    InitWindow(MyWindow_Width, MyWindow_Height, "BOIDS_C");
    printf("\n"); // padding from Raylib print
    SetWindowPosition(0,0);
	rlDisableBackfaceCulling();
}
void MyWindow_Destroy()
{
    CloseWindow();
}
bool MyWindow_ShouldClose()
{
    return WindowShouldClose();
}