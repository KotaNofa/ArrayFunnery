#include "render.h"
#include "globals.h"
#include "SFML/Graphics.hpp"
#include <vector>
#include <cmath>
#include <iostream>

void DrawModelGeometricVerts(const Model& scene, const Viewport& viewport, sf::RenderWindow& window) {

    



}

/*

std::vector<Triangle> Transform(const std::vector<Triangle> &TriBuffer, const Viewport& viewport) {

    std::vector<Triangle>screenBuffer = TriBuffer;

    // translation
    for (int i = 0; i < screenBuffer.size(); ++i) {
        for (int n = 0; n < 3; ++n) {
            for (int j = 0; j < 3; ++j) {
                screenBuffer[i].geo[n][j] -= viewport.position[j];
            }
        }
    }

    // 3d to 2d transformation
    for (int i = 0; i < TriBuffer.size(); ++i) {
        for (int n = 0; n < 3; ++n) {
            // screenBuffer[i].geo[n][0] /= screenBuffer[i].geo[n][2];
            // screenBuffer[i].geo[n][1] /= screenBuffer[i].geo[n][2];

            // FOV = 2 * arctan(width / (2 * focalLength))

            screenBuffer[i].geo[n][0] = 2 * atan(screenBuffer[i].geo[n][0] / (2 * 1));
            screenBuffer[i].geo[n][1] *= 100;
        }
    }

    return screenBuffer;
}

//aggressive clamp for debug purposes
void ClampZ(std::vector<Triangle>& tris, float nearPlane = 0.01f) {
    for (int i = (int)tris.size() - 1; i >= 0; --i) {
        bool v[3] = {false,false,false};
        for (int j = 0; j < 3; ++j) {
            if (tris[i].geo[j][2] < nearPlane)
                v[j] = true;
        }
        // if all three verts are behind the plane, erase
        if (v[0] && v[1] && v[2]) {
            tris.erase(tris.begin() + i);
        }
    }
}

void Center (std::vector<Triangle>& screenBuffer) {
    for (int i = 0; i < screenBuffer.size(); ++i) {
        for (int j = 0; j < 3; ++j) {
            screenBuffer[i].geo[j][0] += winWidth / 2;
            screenBuffer[i].geo[j][1] += winHeight / 2;
        }
    }
}

void SFMLDraw(std::vector<Triangle>& screenBuffer, sf::RenderWindow& window) {
    sf::VertexArray mesh(sf::Triangles);

    for (const auto& tri : screenBuffer) {
        for (int n = 0; n < 3; ++n) {
            mesh.append(sf::Vertex(
                sf::Vector2f(tri.geo[n][0], tri.geo[n][1]),
                sf::Color::White // or any color you want
            ));
        }
    }

    window.draw(mesh);
}

void DrawVerts(const Scene& scene, const Viewport& viewport, sf::RenderWindow& window) {

    std::vector<Triangle>triBuffer = loadTris(scene);
    std::vector<Triangle>screenBuffer = Transform(triBuffer, viewport);
    ClampZ(screenBuffer);
    Center(screenBuffer);
    SFMLDraw(screenBuffer, window);
    triBuffer.clear();
    screenBuffer.clear();
}

*/