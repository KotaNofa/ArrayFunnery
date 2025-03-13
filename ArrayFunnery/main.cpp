#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <vector>
#include "raylib.h"
#include "ThreeDee.h"

using namespace std;

int width = 1080;
int height = 1080;
const char* title = "THREEDEE";

int main() {
    InitWindow(width, height, title);
    SetTargetFPS(60);

    Cube cube;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GRAY);

        DrawText("hello yes this is working :)", width / 2, height / 2, 20, BLACK);
        cube.DrawCubePoints(1);
        cube.DrawCubeLines();

        EndDrawing();

        if (IsKeyDown(KEY_J)) {
            cube.YRotation(5);
        }
        if (IsKeyDown(KEY_L)) {
            cube.YRotation(-5);
        }
        if (IsKeyDown(KEY_I)) {
            cube.XRotation(5);
        }
        if (IsKeyDown(KEY_K)) {
            cube.XRotation(-5);
        }
        if (IsKeyDown(KEY_U)) {
            cube.ZRotation(5);
        }
        if (IsKeyDown(KEY_O)) {
            cube.ZRotation(-5);
        }

        if (IsKeyDown(KEY_W)) {
            cube.ZTranslate(-5); 
        }
        if (IsKeyDown(KEY_S)) {
            cube.ZTranslate(5); 
        }
        if (IsKeyDown(KEY_A)) {
            cube.XTranslate(5); 
        }
        if (IsKeyDown(KEY_D)) {
            cube.XTranslate(-5);  
        }
        if (IsKeyDown(KEY_SPACE)) {
            cube.YTranslate(-5); 
        }
        if (IsKeyDown(KEY_LEFT_SHIFT)) {
            cube.YTranslate(5); 
        }
    }
    CloseWindow();

    return 0;
}
