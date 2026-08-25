
#include "software.h"
#include "math/mat4.h"
#include "SFML/Graphics.hpp"

#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>

void CopyInputIntoBuffer(const Model& input, Model& output) {
    for (int vertIndex = 0; vertIndex < input.vertices.size(); vertIndex++) {
        output.vertices.push_back(input.vertices[vertIndex]);
    }
}

void InsertModelIntoVertexArray(Model& input, sf::VertexArray& vertHeap) {
    for (int vertIndex = 0; vertIndex < input.vertices.size(); ++vertIndex) {
        sf::Vector2f position(input.vertices[vertIndex].geometricCoord.x, input.vertices[vertIndex].geometricCoord.y);
        sf::Vector2f texCoords(input.vertices[vertIndex].uvCoord.x, input.vertices[vertIndex].uvCoord.y);
        vertHeap.append(sf::Vertex(position, sf::Color::White, texCoords));
    }
}



void Transform(Model& in, const Viewport& viewport, sf::Texture texture) {

    mat4f tfMat;
    tfMat.Translate(viewport.x, viewport.y, viewport.z);    
    tfMat.RotateX(viewport.rx);
    tfMat.RotateY(viewport.ry);
    tfMat.RotateZ(viewport.rz);
    tfMat.Scale(viewport.scale);
    
    for(int i = 0; i < in.vertices.size(); ++i) {
        vec4f tfVec;
        tfVec.data = {
            in.vertices[i].geometricCoord.x, in.vertices[i].geometricCoord.y,in.vertices[i].geometricCoord.z, 1
        };

        tfVec *= tfMat;

        in.vertices[i].uvCoord.x *= (texture.getSize()).x;
        in.vertices[i].uvCoord.y = (texture.getSize().y - 1) - in.vertices[i].uvCoord.y * texture.getSize().y;
        in.vertices[i].geometricCoord.x = tfVec.data[0] + 1080/2;
        in.vertices[i].geometricCoord.y = -1*tfVec.data[1] + 1080/2;
        in.vertices[i].geometricCoord.z = tfVec.data[2];
    }
}

struct Triangle {
    sf::Vertex v0, v1, v2;
    float avgZ;
};

std::vector<Triangle> SortTrianglesByDepth(const Model& modelBuffer) {
    std::vector<Triangle> triangles;

    for (size_t i = 0; i + 2 < modelBuffer.vertices.size(); i += 3) {
        auto& v0 = modelBuffer.vertices[i];
        auto& v1 = modelBuffer.vertices[i+1];
        auto& v2 = modelBuffer.vertices[i+2];

        sf::Vertex a({v0.geometricCoord.x, v0.geometricCoord.y}, sf::Color::White, {v0.uvCoord.x, v0.uvCoord.y});
        sf::Vertex b({v1.geometricCoord.x, v1.geometricCoord.y}, sf::Color::White, {v1.uvCoord.x, v1.uvCoord.y});
        sf::Vertex c({v2.geometricCoord.x, v2.geometricCoord.y}, sf::Color::White, {v2.uvCoord.x, v2.uvCoord.y});

        float zAvg = (v0.geometricCoord.z + v1.geometricCoord.z + v2.geometricCoord.z) / 3.0f;

        triangles.push_back({a, b, c, zAvg});
    }

    std::sort(triangles.begin(), triangles.end(),
              [](const Triangle& t1, const Triangle& t2) {
                  return t1.avgZ > t2.avgZ; // far → near
              });

    return triangles;
}


void DrawModelGeometricVerts(const Model& model, sf::Texture texture, const Viewport& viewport, sf::RenderWindow& window) {

    Model modelBuffer;
    CopyInputIntoBuffer(model, modelBuffer);

    Transform(modelBuffer, viewport, texture);
    
    auto tris = SortTrianglesByDepth(modelBuffer);
    sf::VertexArray vertHeap(sf::Triangles);
    for (auto& t : tris) {
        vertHeap.append(t.v0);
        vertHeap.append(t.v1);
        vertHeap.append(t.v2);
    }
    
    sf::RenderStates states;
    states.texture = &texture;
    window.draw(vertHeap, states);
    
}