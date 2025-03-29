#include "globals.h"

int width = 1500;
int height = 750;
const char* title = "THREEDEEE";
Screen view;

void GetInput()
{
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        view.YRotation(static_cast<float>(GetMouseDelta().x) * 0.0075);
        view.ZRotation(static_cast<float>(GetMouseDelta().y) * 0.0075);
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
