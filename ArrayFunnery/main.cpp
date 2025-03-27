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
void DisplayMousePos() {
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

        DisplayMousePos();
        DrawText("hello yes this is workinfg :)", width / 2, height / 2, 20, BLACK);

        view.DrawVert(jeff);
    


        EndDrawing();

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            cube.YRotation(GetMouseDelta().x * 0.075);
            cube.XRotation(GetMouseDelta().y * 0.075);
        }
        if (IsKeyDown(KEY_U)) {
        }
        if (IsKeyDown(KEY_O)) {
        }
        if (IsKeyDown(KEY_W)) {
            view.YTranslate(5);
        }
        if (IsKeyDown(KEY_S)) {
            view.YTranslate(-5);
        }
        if (IsKeyDown(KEY_A)) {
            jeff.XTranslate(-5);
        }
        if (IsKeyDown(KEY_D)) {
            jeff.XTranslate(+5);
        }
        if (IsKeyDown(KEY_SPACE)) {
        }
        if (IsKeyDown(KEY_LEFT_SHIFT)) {
        }
    }
    CloseWindow();

    return 0;
}
