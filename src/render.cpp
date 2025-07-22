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

void Scale(Model& output, const Viewport& viewport) {
    for (int vertIndex = 0; vertIndex < output.vertices.size(); vertIndex++) {
        output.vertices[vertIndex].geometricCoord.x *= 500;
        output.vertices[vertIndex].geometricCoord.y *= 500;
        output.vertices[vertIndex].geometricCoord.z *= 500;
    }
}

void InsertModelIntoVertexArray(Model& input, sf::VertexArray& vertHeap) {
    for (int vertIndex = 0; vertIndex < input.vertices.size(); ++vertIndex) {
        sf::Vector2f position(input.vertices[vertIndex].geometricCoord.x, input.vertices[vertIndex].geometricCoord.y);
        sf::Vector2f texCoords(input.vertices[vertIndex].uvCoord.x, input.vertices[vertIndex].uvCoord.y);
        vertHeap.append(sf::Vertex(position, sf::Color::White, texCoords));
    }
}


void DrawModelGeometricVerts(const Model& model, const Viewport& viewport, sf::RenderWindow& window) {

    // We've just passed in model data, camera, and window context.
    // sf::VertexArray expects a 2D data structure. 
    // Data inside of it is also not transformable after vertice insertion. 
    // It is at this point where we're actually defining the software render pipeline.
    // It is best to use a matrix where all transformations will initiate onto this indentity matrix.
    // After that, we have to convert the data heap into a sf::Vertex with appropriate texture coords and such.

    sf::Texture texture;
    if (!texture.loadFromFile("texture/LaikaDiffuse.png")) {
        // handle error
    }

    Model modelBuffer;
    sf::VertexArray vertHeap(sf::Triangles);

    CopyInputIntoBuffer(model, modelBuffer);
    Translate(modelBuffer, viewport);
    Scale(modelBuffer, viewport);
    InsertModelIntoVertexArray(modelBuffer, vertHeap);

    // Test triangle.
    sf::VertexArray triangle(sf::Triangles, 3);
    triangle[0].position = sf::Vector2f(100, 100);
    triangle[1].position = sf::Vector2f(200, 200);
    triangle[2].position = sf::Vector2f(100, 200);
    triangle[0].color = sf::Color::Red;
    triangle[1].color = sf::Color::Green;
    triangle[2].color = sf::Color::Blue;
    vertHeap.append(triangle[0]);
    vertHeap.append(triangle[1]);
    vertHeap.append(triangle[2]);
    // Test triangle.
    
    window.draw(vertHeap);

}