#include <SFML/Graphics.hpp>

#include "parser.h"

#include <thread>
#include <iostream>
#include <random>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(0, 255);


sf::Vector3f toV3f (float input[3]) {
    sf::Vector3f output = { input[0],input[1],input[2]};
    return output;
};

sf::Vector2f projectV3f (sf::Vector3f input) {
    float scale = 200.f;
    input.x = scale * (input.x / input.z + 0.00001) + 960;
    input.y = scale * (-input.y / input.z + 0.00001) + 540;
    return sf::Vector2f(input.x, input.y);
}


int main() {
    
    Scene world;
    ModelLoader("model/list.txt", world);

    std::vector<sf::Vertex>triangleQue;
    
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



    // get current monitor res
    sf::VideoMode primaryDisplay = sf::VideoMode::getDesktopMode();

    // halve it
    primaryDisplay.height /= 2;
    primaryDisplay.width /= 2;

    // load font
    sf::Font font;
    if (!font.loadFromFile("font/boubasfont.ttf")) {
        return 1;
    }

    // generic text object
    sf::Text jeff("Hi! I'm Koka!", font, 30);
    jeff.setPosition(960,540);
    jeff.setFillColor(sf::Color::White);

    // create image
    sf::Image image;
    image.loadFromFile("texture/bitch.png");

    // pass to texture to be drawn
    sf::Texture texture;
    texture.loadFromImage(image);
    
    // pass to sprite
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(400, 400);
    
    // draw window
    sf::RenderWindow window(primaryDisplay, "Koka3D", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // close on escape
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }
        window.clear(sf::Color::White);

        // draw text object
        window.draw(jeff);
        // window.draw(triangle1);
        // window.draw(triangle2);
        window.draw(triangle);
        window.display();
    }
    return 0;
}