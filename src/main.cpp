#include <SFML/Graphics.hpp>

#include "render.h"

#include <thread>
#include <iostream>
#include <random>


int main() {
    

    Scene world;
    world.loadModels("model/manifest.txt");
    Viewport camera(world);
    // Render(world, camera);

    // get current monitor res
    sf::VideoMode primaryDisplay = sf::VideoMode::getDesktopMode();

    // halve it
    primaryDisplay.height /= 2;
    primaryDisplay.width = primaryDisplay.height;

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
        window.display();
    }
    return 0;
}