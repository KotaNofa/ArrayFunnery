
#include "render.h"
#include "../math/mat4.h"
#include "SFML/Graphics.hpp"

#include <vector>
#include <cmath>
#include <iostream>

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



void Transform(Model& in, const Viewport& viewport) {
    mat4f tfMat;
    tfMat.RotateX(viewport.rx);
    tfMat.RotateY(viewport.ry);
    tfMat.RotateZ(viewport.rz);
    tfMat.Translate(viewport.xRes/2 ,viewport.yRes/2, 0);

    tfMat.Scale(100);

    for(int i = 0; i < in.vertices.size(); ++i) {
        vec4f tfVec;
        tfVec.data = {
            in.vertices[i].geometricCoord.x, in.vertices[i].geometricCoord.y,in.vertices[i].geometricCoord.z, 1
        };
        tfVec *= tfMat;
        
        in.vertices[i].geometricCoord.x = tfVec.data[0];
        in.vertices[i].geometricCoord.y = tfVec.data[1];
        in.vertices[i].geometricCoord.z = tfVec.data[2];
    }
    // Cull Backface
    // Sort Remaining
    // Scale
    // Rotate
    // Translate
    // Project

    // mat4f M = T * S * S;
}


void DrawModelGeometricVerts(const Model& model, sf::Texture texture, const Viewport& viewport, sf::RenderWindow& window) {

    Model modelBuffer;
    CopyInputIntoBuffer(model, modelBuffer);

    Transform(modelBuffer, viewport);    

    sf::VertexArray vertHeap(sf::Triangles);
    InsertModelIntoVertexArray(modelBuffer, vertHeap);
    
    sf::RenderStates states;
    states.texture = &texture;
    window.draw(vertHeap, states);
    
}