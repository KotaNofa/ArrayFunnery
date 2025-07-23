#include "render.h"
#include "globals.h"
#include "SFML/Graphics.hpp"
#include <vector>
#include <cmath>
#include <iostream>

void CopyInputIntoBuffer(const Model& input, Model& output) {
    for (int vertIndex = 0; vertIndex < input.vertices.size(); vertIndex++) {
        output.vertices.push_back(input.vertices[vertIndex]);
    }
}

void Translate(Model& output, const Viewport& viewport) {
    for (int vertIndex = 0; vertIndex < output.vertices.size(); vertIndex++) {
        output.vertices[vertIndex].geometricCoord.x += viewport.x;
        output.vertices[vertIndex].geometricCoord.y += viewport.y;
        output.vertices[vertIndex].geometricCoord.z += viewport.z;
    }
}

void Scale(Model& output, const Viewport& viewport, sf::Texture& texture) {
    for (int vertIndex = 0; vertIndex < output.vertices.size(); vertIndex++) {
        float scale;
        output.vertices[vertIndex].geometricCoord.x *= 500;
        output.vertices[vertIndex].geometricCoord.y *= 500;
        output.vertices[vertIndex].geometricCoord.z *= 500;
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

void CullBackface(Model& output) {
    Model buffer;
    int index = 0;
    for (auto& vertex : output.vertices) {
        index++;
        if (output.vertices[index].geometricCoord.z < -0.5f) {
            buffer.vertices.push_back(output.vertices[index]);
        }
    }
    output.vertices = buffer.vertices;
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
    Scale(modelBuffer, viewport, texture);
    InsertModelIntoVertexArray(modelBuffer, vertHeap);
    
    sf::RenderStates states;
    states.texture = &texture;
    window.draw(vertHeap, states);
    
}