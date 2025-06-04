#include "render.h"

#include "globals.h"

#include "SFML/Graphics.hpp"

#include <random>
#include <array>
#include <iostream>

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
    temp[0] = (model[0] / model[2]);
    temp[1] = (model[1] / model[2]);
    temp[2] = model[2];
};

void Center(const float (&model)[3], float (&temp)[3]) {
    temp[0] = (model[0]) + winWidth / 2;
    temp[1] = (model[1]) + winHeight / 2;
    temp[2] = model[2];
}

// for each model in scene, go through list of indices in models, grab each vertex according to the indices and apply its transformation. If any model after the projection's z values are all below 

float t1[3] = {0,0,0};
float t2[3] = {0,0,0};
float t3[3] = {0,0,0};

sf::Vector2f temp2f[3];

struct Triangle {
    sf::Vertex verts[3];
    float depth;
};

Triangle tri;
std::vector<Triangle> triList;

void SortTris(std::vector<Triangle>  &triList) {
    std::sort(triList.begin(), triList.end(), [](const Triangle& a, const Triangle& b) {
    return a.depth < b.depth; // descending order, back-to-front
    });
} 

void ClampZ(std::vector<Triangle>& triList) {
    triList.erase(
        std::remove_if(triList.begin(), triList.end(),
            [](const Triangle& tri) { return tri.depth >= -0.1f; }),
        triList.end()
    );
}

void Render(const Scene& scene, const Viewport& viewport, sf::RenderWindow& window) {
    for (int i = 0; i < scene.models.size(); ++i) {
        for (int j = 0; j < scene.models[i].indices.size(); ++j) {

            float avgDepth[3];
            for (int n = 0; n < 3; ++n) {
                unsigned int IndexedVert = scene.models[i].indices[j].geo[n];
                Translate(scene.models[i].verts[IndexedVert].geo, viewport.position, t1);
                Transform(t1, t2, 100);
                avgDepth[n] = t2[2];
                Center(t2, t3);
                tri.verts[n] = {{t3[0], t3[1]}, sf::Color::Cyan};
            }
            triList.push_back(tri);
            triList[j].depth = (avgDepth[0] + avgDepth[1] + avgDepth[2])/ 3;
    
        }
    }

    ClampZ(triList);

    for (int b = 0;  b < triList.size(); ++b) {
        for (int k = 0; k < 3; ++k) {
            if (b == 0) {
                triList[b].verts[k].color = sf::Color::White;
            }
            else {
                triList[b].verts[k].color = sf::Color::Red;
            }
        }
    }

    SortTris(triList);

    for (int i = 0; i < triList.size(); ++i) {
        window.draw(triList[i].verts, 3, sf::Triangles);
    }

    triList.clear();
}