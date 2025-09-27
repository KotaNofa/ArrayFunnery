#include <SFML/Graphics.hpp>

#include "globals.h"
#include "gfx/render.h"
#include "gfx/parser.h"
#include "math/mat4.h"

#include <cmath>
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>

int main() {

    Model cube;
    sf::Texture texture;
    cube.InitFromOBJ("assets/model/cube.obj");
    if (!texture.loadFromFile("assets/texture/laikaUV.png")) {
    }

    Viewport camera;

    sf::RenderWindow window(sf::VideoMode(winWidth, winHeight), "Koka3D", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    
    while (window.isOpen()) {

        float spin = 0.1;
        camera.RotateX(spin);
        camera.RotateY(spin);
        camera.RotateZ(spin);
        spin += 0.1;

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