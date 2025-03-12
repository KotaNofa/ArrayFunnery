#define _USE_MATH_DEFINES
#include  <raylib.h>
#include <cmath>
#include <iostream>
#include "ThreeDee.h"

using namespace std;

int width = 1080;
int height = 1080;
const char* title = "THREEDEE";

int main() {

    InitWindow(width, height, title);
    SetTargetFPS(60);

    ThreeDee cube[8] = {
        ThreeDee(100, 100, 100),
        ThreeDee(100, -100, 100),
        ThreeDee(-100, -100, 100),
        ThreeDee(-100, 100, 100),
        ThreeDee(100, 100, -100),
        ThreeDee(100, -100, -100),
        ThreeDee(-100, -100, -100),
        ThreeDee(-100, 100, -100)
    };



    while (WindowShouldClose) {
        BeginDrawing();
        ClearBackground(GRAY);
        DrawText("hello yes this is working :)", width / 2, height / 2, 20, BLACK);
        DrawCircle(width / 2, height / 2, 20, RED);

        DrawLine(cube[0].Xindex, cube[0].Yindex, cube[1].Xindex, cube[1].Yindex, BLACK);
        DrawLine(cube[1].Xindex, cube[1].Yindex, cube[2].Xindex, cube[2].Yindex, BLACK);
        DrawLine(cube[2].Xindex, cube[2].Yindex, cube[3].Xindex, cube[3].Yindex, BLACK);
        DrawLine(cube[3].Xindex, cube[3].Yindex, cube[0].Xindex, cube[0].Yindex, BLACK);
        DrawLine(cube[4].Xindex, cube[4].Yindex, cube[5].Xindex, cube[5].Yindex, BLACK);
        DrawLine(cube[5].Xindex, cube[5].Yindex, cube[6].Xindex, cube[6].Yindex, BLACK);
        DrawLine(cube[6].Xindex, cube[6].Yindex, cube[7].Xindex, cube[7].Yindex, BLACK);
        DrawLine(cube[7].Xindex, cube[7].Yindex, cube[4].Xindex, cube[4].Yindex, BLACK);


        for (int i = 0; i < 8; ++i) {
            cube[i].Draw();
        }

        if (IsKeyDown(KEY_J)) {

            for (int i = 0; i < 8; ++i) {
                cube[i].YRotation(-5);
            }
        }

        if (IsKeyDown(KEY_L)) {

            for (int i = 0; i < 8; ++i) {
                cube[i].YRotation(5);
            }
        }

        if (IsKeyDown(KEY_I)) {

            for (int i = 0; i < 8; ++i) {
                cube[i].XRotation(-5);
            }
        }

        if (IsKeyDown(KEY_K)) {

            for (int i = 0; i < 8; ++i) {
                cube[i].XRotation(5);
            }
        }

        if (IsKeyDown(KEY_U)) {

            for (int i = 0; i < 8; ++i) {
                cube[i].ZRotation(5);
            }
        }

        if (IsKeyDown(KEY_O)) {

            for (int i = 0; i < 8; ++i) {
                cube[i].ZRotation(-5);
            }
        }

        if (IsKeyDown(KEY_W)) {

            for (int i = 0; i < 8; ++i) {
                cube[i].Yindex += 5;
            }
        }

        if (IsKeyDown(KEY_S)) {

            for (int i = 0; i < 8; ++i) {
                cube[i].Yindex += -5;
            }
        }

        EndDrawing();
    }

    return 0;
}