
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

void Transform(Model model, Viewport viewport) {
    mat4f tfMat;
    tfMat.Scale(5);
    // Scale
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