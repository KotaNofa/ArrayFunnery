#include <SFML/Graphics.hpp>

#include "parser.h"

#include <thread>
#include <iostream>

int main() {
    
    Scene world;
    ModelLoader("model/list.txt", world);

    // get current monitor res
    sf::VideoMode primaryDisplay = sf::VideoMode::getDesktopMode();

    // halve it
    primaryDisplay.height /= 2;
    primaryDisplay.width /= 2;

    /*
    float camX = 0.f, camY = 5.f, camZ = 10.f;
    float f = 1.0f;
    float scale = 200.f; // scale projection to pixels
    float centerX = primaryDisplay.width / 2.f;
    float centerY = primaryDisplay.height / 2.f;

    auto project = [&](float x, float y, float z) -> sf::Vector2f {
        float rx = x - camX;
        float ry = y - camY;
        float rz = z - camZ;
        if (rz >= 0) rz = -0.0001f; // avoid division by zero or behind camera

        float Xp = (f * rx) / -rz;
        float Yp = (f * ry) / -rz;

        return sf::Vector2f(centerX + Xp * scale, centerY - Yp * scale);
    };

    std::array<std::array<float, 3>, 4> points = {{
        {-3.974462f, 0.f,  3.974462f},
        { 3.974462f, 0.f,  3.974462f},
        { 3.974462f, 0.f, -3.974462f},
        {-3.974462f, 0.f, -3.974462f}
    }};

    sf::Vector2f p1 = project(points[0][0], points[0][1], points[0][2]);
    sf::Vector2f p2 = project(points[1][0], points[1][1], points[1][2]);
    sf::Vector2f p3 = project(points[2][0], points[2][1], points[2][2]);
    sf::Vector2f p4 = project(points[3][0], points[3][1], points[3][2]);

    sf::VertexArray triangle1(sf::Triangles, 3);
    triangle1[0].position = p1;
    triangle1[1].position = p2;
    triangle1[2].position = p3;

    triangle1[0].color = sf::Color::Red;
    triangle1[1].color = sf::Color::Green;
    triangle1[2].color = sf::Color::Blue;

    sf::VertexArray triangle2(sf::Triangles, 3);
    triangle2[0].position = p1;
    triangle2[1].position = p3;
    triangle2[2].position = p4;

    triangle2[0].color = sf::Color::Red;
    triangle2[1].color = sf::Color::Blue;
    triangle2[2].color = sf::Color::Green;
    */

    
    

    // load font
    sf::Font font;
    if (!font.loadFromFile("font/boubasfont.ttf")) {
        return 1;
    }

    // generic text object
    sf::Text jeff("Hi! I'm Koka!", font, 30);
    jeff.setPosition(0,0);
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
        window.clear(sf::Color::Black);

        // draw text object
        window.draw(jeff);
        // window.draw(triangle1);
        // window.draw(triangle2);
        window.display();
    }
    return 0;
}