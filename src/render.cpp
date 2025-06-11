#include "render.h"
#include "globals.h"
#include "SFML/Graphics.hpp"
#include <vector>
#include <cmath>
#include <iostream>

struct Triangle {
    float geo[3][3];
};

std::vector<Triangle> loadTris (const Scene& scene) {

    Vertices tempVert;
    Triangle tempTri;
    std::vector<Triangle> triBuffer;

    for (int i = 0; i < scene.models.size(); ++i) {
        for (int j = 0; j < scene.models[i].indices.size(); ++j) {
            for (int n = 0; n < 3; ++n) {
                unsigned int sel = scene.models[i].indices[j].geo[n];
                for (int k = 0; k < 3; ++k) {
                    tempTri.geo[n][k] = scene.models[i].verts[sel].geo[k];
                }
            }
            triBuffer.push_back(tempTri);
        }
    }

    return triBuffer;
}

std::vector<Triangle> Transform(const std::vector<Triangle> &TriBuffer, const Viewport& viewport) {

    std::vector<Triangle>screenBuffer = TriBuffer;

    // translation
    for (int i = 0; i < screenBuffer.size(); ++i) {
        for (int n = 0; n < 3; ++n) {
            for (int j = 0; j < 3; ++j) {
                screenBuffer[i].geo[n][j] += viewport.position[j];
            }
        }
    }

    // 3d to 2d transformation
    for (int i = 0; i < TriBuffer.size(); ++i) {
        for (int n = 0; n < 3; ++n) {
            screenBuffer[i].geo[n][0] /= screenBuffer[i].geo[n][2];
            screenBuffer[i].geo[n][1] /= screenBuffer[i].geo[n][2];
        }
    }

    return screenBuffer;
}

//aggressive clamp for debug purposes
void ClampZ(std::vector<Triangle>& screenBuffer) {
    for (int i = screenBuffer.size() - 1; i >= 0; --i) {
        for (int j = 0; j < 3; ++j) {
            if (screenBuffer[i].geo[j][2] >= 1.f) {
                screenBuffer.erase(screenBuffer.begin() + i);
                break;
            }
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

void Render(const Scene& scene, const Viewport& viewport, sf::RenderWindow& window) {

    std::vector<Triangle>triBuffer = loadTris(scene);
    std::vector<Triangle>screenBuffer = Transform(triBuffer, viewport);
    ClampZ(screenBuffer);
    Center(screenBuffer);
    SFMLDraw(screenBuffer, window);
    triBuffer.clear();
    screenBuffer.clear();
}