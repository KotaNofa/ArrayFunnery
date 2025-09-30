#include <SFML/Graphics.hpp>

#include "gfx/render.h"
#include "gfx/parser.h"
#include "math/mat4.h"

#include <cmath>
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>

int main() {

    Viewport camera;
    float camSpeed = 5.f;
    Model cube;
    sf::Texture texture;
    cube.InitFromOBJ("assets/model/triCube.obj");
    texture.loadFromFile("assets/texture/triCube.png");

    const unsigned int xRes = 1080;
    const unsigned int yRes = 1080;

    sf::RenderWindow window(sf::VideoMode(xRes, yRes), "Koka3D", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    sf::Color clearColor = {64, 64, 64};
    bool handleInput = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (event.type == sf::Event::LostFocus) {
                clearColor = {64, 64, 64};
                handleInput = false;
            }
            if (event.type == sf::Event::GainedFocus) {
                clearColor = {64, 64, 64};
                handleInput = true;
            }
            if (handleInput) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    window.close();
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                    camera.TranslateZ(camSpeed);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                    camera.TranslateZ(-camSpeed);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                    camera.TranslateX(-camSpeed);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
                    camera.TranslateX(camSpeed);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
                    camera.TranslateY(-camSpeed);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                    camera.TranslateY(camSpeed);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
                    camera.RotateY(camSpeed);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
                    camera.RotateY(camSpeed);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
                    camera.RotateX(camSpeed);
                }

            }
        }

        window.clear(clearColor);
        DrawModelGeometricVerts(cube, texture,  camera, window);

        window.display();
    }
    return 0;
}