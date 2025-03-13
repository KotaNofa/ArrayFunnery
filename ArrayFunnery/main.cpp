#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <vector>
#include "raylib.h"
#include "ThreeDee.h"
#include "globals.h"
#include "Screen.h"

using namespace std;



int main() {
    InitWindow(width, height, title);
    SetTargetFPS(60);

    Cube cube;
    Cube bruh;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GRAY);

        DrawText("hello yes this is working :)", width / 2, height / 2, 20, BLACK);
        cube.DrawCubePoints(1);
        cube.DrawCubeLines();

        bruh.DrawCubePoints(1);
        bruh.DrawCubeLines();

        EndDrawing();

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            cube.YRotation(GetMouseDelta().x * 0.075);
            cube.XRotation(GetMouseDelta().y * 0.075);
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
