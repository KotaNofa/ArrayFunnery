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
    unsigned int i_geo[3];
    unsigned int i_normal[3];
    unsigned int i_uv[3];
};

struct Model {
    std::vector<Vertices>verts;
    std::vector<Indices>indices;
};

#endif