#include <SFML/Graphics.hpp>
#include "parser.h"

int main() {

    ObjToModelParser("model/cube.obj");

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
    sf::Text jeff("Hello SFML!", font, 30);
    jeff.setColor(sf::Color::Black);
    jeff.setPosition(0,0);

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
    sf::RenderWindow window(primaryDisplay, "SFML Test", sf::Style::Titlebar | sf::Style::Close);
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
        window.draw(sprite);

        window.display();
    }
    return 0;
}