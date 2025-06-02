#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <vector>

class Viewport {
    public:
    float position[3];
    float rotation[3];

    Viewport();

    void TranslateX(float input);
    void TranslateY(float input);
    void TranslateZ(float input);
    void RotateX(float input);
    void RotateY(float input);
    void RotateZ(float input);

};

#endif