#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <string>
#include <vector>

class Scene; // forward declaration

class Viewport {
    public:
    float position[3];
    float rotation[3];
    Scene* local;

    Viewport(Scene &scene);

    void TranslateX(float input);
    void TranslateY(float input);
    void TranslateZ(float input);
    void RotateX(float input);
    void RotateY(float input);
    void RotateZ(float input);

};

#endif