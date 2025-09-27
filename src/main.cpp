#include <SFML/Graphics.hpp>

#include "globals.h"
#include "gfx/render.h"
#include "gfx/parser.h"

#include <cmath>
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>

int main() {

    Model cube;
    sf::Texture texture;
    cube.InitFromOBJ("assets/model/triCube.obj");
    if (!texture.loadFromFile("assets/texture/triCube.png")) {
    }

    Viewport camera;

    sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "Koka3D", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }

        window.clear(sf::Color{128, 224, 197});
        DrawModelGeometricVerts(cube, texture,  camera, window);

        window.display();
    }
    return 0;
}