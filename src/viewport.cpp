#include "viewport.h"

Viewport::Viewport(Scene &scene) {
    position[0] = 0;
    position[1] = 0;
    position[2] = 0;
    rotation[0] = 0;
    rotation[1] = 0;
    rotation[2] = 0;
};

void Viewport::TranslateX(float input) {
    position[0] += input;
};
void Viewport::TranslateY(float input) {
    position[1] += input;
};
void Viewport::TranslateZ(float input) {
    position[2] += input;
};
void Viewport::RotateX(float input) {
    rotation[0] += input;
};
void Viewport::RotateY(float input) {
    rotation[1] += input;
};
void Viewport::RotateZ(float input) {
    rotation[2] += input;
};