#include "render.h"
#include "globals.h"
#include "SFML/Graphics.hpp"
#include <vector>
#include <cmath>
#include <iostream>

/*
void Translate(const Model& model, const Viewport& viewport) {
    for (int vertIndex = 0; vertIndex < model.geometricVerts.size(); vertIndex++) {
        for (int dimension = 0; dimension < 3; dimension++) {
            model.geometricVerts[vertIndex].x = 
        }
    }
}
*/

void DrawModelGeometricVerts(const Model& model, const Viewport& viewport, sf::RenderWindow& window) {

    // We've just passed in model data, camera, and window context.
    // sf::VertexArray expects a 2D data structure. 
    // Data inside of it is also not transformable after vertice insertion. 
    // It is at this point where we're actually defining the software render pipeline.
    // It is best to use a matrix where all transformations will initiate onto this indentity matrix.
    // After that, we have to convert the data heap into a sf::Vertex with appropriate texture coords and such.



    sf::VertexArray vertHeap(sf::Triangles);

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