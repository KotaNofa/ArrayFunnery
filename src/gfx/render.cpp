#include "render.h"
#include "SFML/Graphics.hpp"
#include <vector>
#include <cmath>
#include <iostream>

void CopyInputIntoBuffer(const Model& input, Model& output) {
    for (int vertIndex = 0; vertIndex < input.vertices.size(); vertIndex++) {
        output.vertices.push_back(input.vertices[vertIndex]);
    }
}

void CullBackface(Model& output) {
    for (int i = 0; i < output.vertices.size(); ++i) {
        // this is long overdue and needs to be implemented
    }
}

void Translate(Model& output, const Viewport& viewport) {
    for (int vertIndex = 0; vertIndex < output.vertices.size(); vertIndex++) {
        output.vertices[vertIndex].geometricCoord.x += viewport.x;
        output.vertices[vertIndex].geometricCoord.y += viewport.y;
        output.vertices[vertIndex].geometricCoord.z += viewport.z;
    }
}

void Scale(Model& output, const Viewport& viewport, sf::Texture& texture, int amount) {
    for (int vertIndex = 0; vertIndex < output.vertices.size(); vertIndex++) {
        float scale;
        output.vertices[vertIndex].geometricCoord.x *= amount;
        output.vertices[vertIndex].geometricCoord.y *= amount;
        output.vertices[vertIndex].geometricCoord.z *= amount;
        output.vertices[vertIndex].uvCoord.x *= texture.getSize().x;
        output.vertices[vertIndex].uvCoord.y *= texture.getSize().y;
    }
}

void InsertModelIntoVertexArray(Model& input, sf::VertexArray& vertHeap) {
    for (int vertIndex = 0; vertIndex < input.vertices.size(); ++vertIndex) {
        sf::Vector2f position(input.vertices[vertIndex].geometricCoord.x, input.vertices[vertIndex].geometricCoord.y);
        sf::Vector2f texCoords(input.vertices[vertIndex].uvCoord.x, input.vertices[vertIndex].uvCoord.y);
        vertHeap.append(sf::Vertex(position, sf::Color::White, texCoords));
    }
}

void DrawModelGeometricVerts(const Model& model, sf::Texture texture, const Viewport& viewport, sf::RenderWindow& window) {

    // We've just passed in model data, camera, and window context.
    // sf::VertexArray expects a 2D data structure. 
    // Data inside of it is also not transformable after vertice insertion. 
    // It is at this point where we're actually defining the software render pipeline.
    // It is best to use a matrix where all transformations will initiate onto this indentity matrix.
    // After that, we have to convert the data heap into a sf::Vertex with appropriate texture coords and such.

    Model modelBuffer;
    sf::VertexArray vertHeap(sf::Triangles);

    CopyInputIntoBuffer(model, modelBuffer);
    Translate(modelBuffer, viewport);
    Scale(modelBuffer, viewport, texture, 500);
    InsertModelIntoVertexArray(modelBuffer, vertHeap);
    
    sf::RenderStates states;
    states.texture = &texture;
    window.draw(vertHeap, states);
    
}