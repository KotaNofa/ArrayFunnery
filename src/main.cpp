#include <SFML/Graphics.hpp>

#include "globals.h"
#include "render.h"

#include <cmath>
#include <iostream>

int main() {

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

    Scene world;
    world.loadModels("model/manifest.txt");
    Viewport camera;

    float cameraSpeed = 0.01f; // Adjust as needed

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
        window.clear(sf::Color::Black);

        // draw text object
        window.draw(jeff);
        
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) { // Or RShift
            
        }

        Render(world, camera, window);

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

        window.display();
    }
    return 0;
}