#include <SFML/Graphics.hpp>

#include "globals.h"
#include "render.h"
#include "parser.h"

#include <cmath>
#include <iostream>
#include <sstream>
#include <thread>
#include <chrono>

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
    cube.InitFromOBJ("model/cube.obj");

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

        DrawModelGeometricVerts(cube,camera,window);
        
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) { // Or RShift
            
        }

        // Inside your game loop (outside the event loop)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            camera.TranslateZ(cameraSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            camera.TranslateZ(-cameraSpeed);
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


        window.display();
    }
    return 0;
}