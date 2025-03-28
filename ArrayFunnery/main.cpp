#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <vector>
#include "raylib.h"
#include "Vertex.h"
#include "globals.h"
#include "Screen.h"

using namespace std;

// I hate you raylib
void DrawStats() {
    Vector2 pos = GetMousePosition();
    char toChar[100];  
    snprintf(toChar, sizeof(toChar), "X: %.2f Y: %.2f", pos.x, pos.y);  
    DrawText(toChar, width / 36, height / 36, height / 36, BLACK);  
}

int main() {
    InitWindow(width, height, title);
    SetTargetFPS(60);

    Screen view;
    Cube cube;
    Vertex jeff(50, 50, 1);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GRAY);

        DrawStats();
        DrawText("hello yes this is working :) hi!", width / 2, height / 2, 20, BLACK);

        view.DrawVertCube(cube);

        EndDrawing();

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            cube.XRotation(GetMouseDelta().x * 0.075);
            cube.YRotation(GetMouseDelta().y * 0.075);
        }

        if (IsKeyDown(KEY_Q)) {
            cube.YRotation(-5);
        }
        if (IsKeyDown(KEY_E)) {
            cube.YRotation(5);
        }
        if (IsKeyDown(KEY_W)) {
            view.ZTranslate(5);
        }
        if (IsKeyDown(KEY_S)) {
            view.ZTranslate(-5);
        }
        if (IsKeyDown(KEY_A)) {
            view.XTranslate(-5);
        }
        if (IsKeyDown(KEY_D)) {
            view.XTranslate(+5);
        }
        if (IsKeyDown(KEY_SPACE)) {
            view.YTranslate(+5);
        }
        if (IsKeyDown(KEY_LEFT_SHIFT)) {
            view.YTranslate(-5);
        }
    }
    CloseWindow();

    return 0;
}
