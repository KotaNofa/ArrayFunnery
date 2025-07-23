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

    /*
    // load font
    sf::Font font;
    if (!font.loadFromFile("font/boubasfont.ttf")) {
        return 1;
    }

    // Hello world text object
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
    */

    Model cube;
    cube.InitFromOBJ("model/trika.obj");
    sf::Texture texture;
    if (!texture.loadFromFile("texture/LaikaDiffuse.png")) {
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
        // close on escape
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window.close();
        }
        window.clear(sf::Color{128, 224, 197});


        DrawModelGeometricVerts(cube, texture,camera,window);
        
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) { // Or RShift
            
        }

        // Inside your game loop (outside the event loop)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            float amount = 0;
            amount = 1.01;
            ScaleUV(cube, amount);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            float amount = 0;
            amount = .99f;
            ScaleUV(cube, amount);
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) { // Or RShift
            camera.TranslateY(cameraSpeed);
        }

        std::cout << "\r"
          << "Cam X: " << camera.x
          << " | Cam Y: " << camera.y
          << " | Cam Z: " << camera.z
          << "      " // padding to clear leftovers
          << std::flush;

        /*
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            std::cout << "\nEnter camera Z value: ";
            float input;
            while (!(std::cin >> input)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Enter a numeric Z value: ";
            }
            camera.z = input;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
            */
        RotateGeometryY(cube, 0.1f);

        window.display();
    }
    return 0;
}