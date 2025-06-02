#include "render.h"

#include "globals.h"

#include "SFML/Graphics.hpp"

#include <random>
#include <array>

std::random_device rd; 
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(0, 255);

// extern sf::VideoMode desktop;
// extern unsigned int winWidth;
// extern unsigned int winHeight;

void Translate(const float (&model)[3], const float (&view)[3],float (&temp)[3]) {
    temp[0] = model[0] + view[0];
    temp[1] = model[1] + view[1];
    temp[2] = model[2] + view[2];   
}

void Transform(const float (&model)[3], float (&temp)[3], float scale) {
    temp[0] = (model[0] / model[2]) * scale;
    temp[1] = (model[1] / model[2]) * scale;
};

void Center(const float (&model)[3], float (&temp)[3]) {
    temp[0] = (model[0]) + winWidth / 2;
    temp[1] = (model[1]) + winHeight / 2;
}

// for each model in scene, go through list of indices in models, grab each vertex according to the indices and apply its transformation. If any model after the projection's z values are all below 

float t1[3] = {0,0,0};
float t2[3] = {0,0,0};
float t3[3] = {0,0,0};

sf::Vector2f temp2f[3];

sf::VertexArray mesh(sf::Triangles);

void Render(const Scene& scene, const Viewport& viewport, sf::RenderWindow& window) {
    for (int i = 0; i < scene.models.size(); ++i) {
        for (int j = 0; j < scene.models[i].indices.size(); ++j) {

            for (int n = 0; n < 3; ++n) {
                unsigned int IndexedVert = scene.models[i].indices[j].geo[n];
                Translate(scene.models[i].verts[IndexedVert].geo, viewport.position, t1);
                Transform(t1, t2, 100);
                Center(t2, t3);
                temp2f[n] = {t3[0], t3[1]};
            }
            // sf::Color randomColor(dis(gen), dis(gen), dis(gen));

            for (int n = 0; n < 3; ++n) {
                mesh.append(sf::Vertex(temp2f[n],sf::Color::White));
            }
        }
    }
    window.draw(mesh);
    mesh.clear();
}