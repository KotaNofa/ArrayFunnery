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
    std::vector<Vertice>geometric;
    std::vector<Vertice>normal;
    std::vector<Map>uvs;
};

class Scene {
public:
    std::vector<Model>models;
    void loadModels(const std::string dirManifest);
};

#endif