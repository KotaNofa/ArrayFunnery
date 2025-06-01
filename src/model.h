#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>

struct Vertices {
    float geo[3];
    float normal[3];
    float uv[2];
};

struct Indices {
    unsigned int geo[3];
    unsigned int normal[3];
    unsigned int uv[3];
};

class Model {
public:
    std::vector<Vertices>verts;
    std::vector<Indices>indices;
    void ObjToModelParser(std::string name, Model& output);
};

class Scene {
public:
    std::vector<Model>models;
    void loadModels(const std::string manifest);
};

#endif