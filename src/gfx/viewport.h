#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <vector>


class Viewport {
    public:
    float xRes, yRes;
    float x, y, z;
    float rx, ry, rz;
    Viewport();

    void TranslateX(float input);
    void TranslateY(float input);
    void TranslateZ(float input);
    void RotateX(float input);
    void RotateY(float input);
    void RotateZ(float input);

};

#endif