#include "viewport.h"

Viewport::Viewport() {
    x = 0;
    y = 0;
    z = 0;
    rx = 0;
    ry = 0;
    rz = 0;
    scale = 100;
};

void Viewport::TranslateX(float input) {
    x += input;
};
void Viewport::TranslateY(float input) {
    y += input;
};
void Viewport::TranslateZ(float input) {
    z += input;
};
void Viewport::RotateX(float input) {
    rx += input;
};
void Viewport::RotateY(float input) {
    ry += input;
};
void Viewport::RotateZ(float input) {
    rz += input;
}
void Viewport::Scale(float input) {
    scale += input;
};