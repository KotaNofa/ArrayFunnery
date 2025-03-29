#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <vector>
#include "globals.h"
#include "raylib.h"
#include "Vertex.h"
#include "Object.h"
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

    Object cube;

    cube.vertices.insert(cube.vertices.end(), {
        Vertex(-100, -100, -100), Vertex(100, -100, -100),
        Vertex(100,  100, -100), Vertex(-100,  100, -100),
        Vertex(-100, -100,  100), Vertex(100, -100,  100),
        Vertex(100,  100,  100), Vertex(-100,  100,  100)
    });

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GRAY);
        DrawStats();
        DrawText("hello yes this is working :) hi!", width / 2, height / 2, 20, BLACK);

        view.DrawVerts(cube);

        GetInput();

        EndDrawing();


    }
    CloseWindow();

    return 0;
}
