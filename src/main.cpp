#include <SFML/Graphics.hpp>

#include "globals.h"
#include "render.h"
#include "parser.h"

#include <cmath>
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>

void ScaleUV(Model& in, float amount) {
    for (int i = 0; i < in.vertices.size(); i++) {
        in.vertices[i].uvCoord.x *= amount;
        in.vertices[i].uvCoord.y *= amount;
    }
};


void RotateGeometryY(Model& in, float angleRadians) {
    float cosA = std::cos(angleRadians);
    float sinA = std::sin(angleRadians);

    for (int i = 0; i < in.vertices.size(); i++) {
        float x = in.vertices[i].geometricCoord.x;
        float z = in.vertices[i].geometricCoord.z;

        in.vertices[i].geometricCoord.x = x * cosA + z * sinA;
        in.vertices[i].geometricCoord.z = -x * sinA + z * cosA;
        // Y stays the same
    }
}

int main() {

    Model cube;
    sf::Texture texture;
    cube.InitFromOBJ("model/triCube.obj");
    if (!texture.loadFromFile("texture/triCube.png")) {
        // handle error
    }

    Viewport camera;
    float cameraSpeed = 0.1; // Adjust as needed
    camera.z = 0.f;

    // draw window
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

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {   
        }
        if (event.type == sf::Event::MouseWheelScrolled) {
            float amount = event.mouseWheel.delta;
            RotateGeometryY(cube, amount);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            // ScaleUV(cube, amount);
            RotateGeometryY(cube, -0.1f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            // ScaleUV(cube, .99f);
            RotateGeometryY(cube, 0.1f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            camera.TranslateX(-cameraSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            camera.TranslateX(cameraSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            camera.TranslateY(-cameraSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
            camera.TranslateY(cameraSpeed);
        }

        window.display();
    }
    return 0;
}