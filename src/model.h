#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>

// for vertices in 3D space
struct Vertice {
    float x, y, z;
};

// for UV coords in 2D space
struct Map {
    float x, y;
};

// software rendering structs
class Model {
public:
    std::vector<Vertice>geometricVerts;
    std::vector<Vertice>normalVerts;
    std::vector<Map>uvsVerts;
};

/* 

Dont use for now
class Scene {
public:
    std::vector<Model>models;
    void loadModels(const std::string dirManifest);
};

*/

#endif