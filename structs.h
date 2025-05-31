#ifndef STRUCTS_H
#define STRUCTS_H

#include <vector>

class Vertices {
public:
    float geo[3];
    float normal[3];
    float uv[2];
};

class Indices {
public:
    unsigned int geo[3];
    unsigned int normal[3];
    unsigned int uv[3];
};

struct Model {
    std::vector<Vertices>verts;
    std::vector<Indices>indices;
};

struct Scene {
    std::vector<Model>models;
};

#endif