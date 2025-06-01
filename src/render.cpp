#include "render.h"

#include <random>

#include "SFML/Graphics.hpp"

void Render(const Scene& scene, const Viewport& viewport) {
    
};

/* std::random_device rd; 
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(0, 255);

sf::Vector3f toV3f (float input[3]) {
    sf::Vector3f output = { input[0],input[1],input[2]};
    return output;
};



sf::Vector2f projectV3f (sf::Vector3f input) {
    float scale = 500.f;
    input.x = scale * (input.x) + 540;
    input.y = scale * (-input.y) + 1050;
    return sf::Vector2f(input.x, input.y);
}

void Render(Scene* scene, Viewport* viewport){
    
};


/* std::vector<sf::Vertex>triangleQue;

// drawing all models in scene
for (int i = 0; i < world.models.size(); ++i ) {
    // drawing all triangles in model
    for (int j = 0; j < world.models[i].indices.size(); ++j) {
        // getting all points from indeces
        for (int n = 0; n < 3; ++ n) {
            int selVert = world.models[i].indices[j].geo[n];
            sf::Vector3f temp = toV3f(world.models[i].verts[selVert].geo);
            sf::Color randomColor(dis(gen), dis(gen), dis(gen));
            triangleQue.push_back(sf::Vertex(projectV3f(temp), randomColor));
        }
    }
}

sf::VertexArray triangle(sf::Triangles);

for (size_t i = 0; i < triangleQue.size(); ++i) {
    triangle.append(triangleQue[i]);
} 
*/