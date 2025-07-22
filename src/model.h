#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <string>

struct Vector3f {
    float x, y, z;
};

struct Vector2f {
    float x, y;
};

// for vertices in 3D space
struct Vertex {
    Vector3f geometricCoord;
    Vector3f normalCoord;
    Vector2f uvCoord;
};

// software rendering structs
class Model {
public:
    std::string name;
    std::vector<Vertex> vertices;
    Model();
    void InitFromOBJ(std::string dirName);
};

#endif