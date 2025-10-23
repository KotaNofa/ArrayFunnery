#include <SFML/Graphics.hpp>

#include "render/software.h"
#include "parser/obj.h"
#include "math/mat4.h"

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <chrono>

int main() {

    Viewport camera;
    float camSpeed = 5.f;
    Model cube;
    sf::Texture texture;

    std::string  modeltoload;
    std::string  txtrtoload;
    std::cout << "name of model to load: " << std::endl;
    std::cin >> modeltoload;
    std::cout << "name of texture to load: " << std::endl;
    std::cin >> txtrtoload;

    cube.InitFromOBJ("assets/model/" + modeltoload + ".obj");
    texture.loadFromFile("assets/texture/" + txtrtoload + ".png");

    const unsigned int xRes = 1080;
    const unsigned int yRes = 1080;

    sf::Font boubas;
    if (!boubas.loadFromFile("assets/font/boubasfont.ttf")) {
    }
    sf::Text controls;
    std::string move = "Move: WASD, Space, LShift";
    std::string rotate = "Rotate: IJKL";
    std::string scale = "Scale: Dash, Equals";
    std::string spinny = "Spin: B,N";
    std::string tris = "Triangles: " + std::to_string(cube.vertices.size()/3);
    controls.setPosition(10.f, 10.f);
    controls.setFillColor(sf::Color::White);
    controls.setFont(boubas);
    controls.setCharacterSize(40);
    bool spin = false;

    sf::RenderWindow window(sf::VideoMode(xRes, yRes), "Koka3D", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    sf::Color clearColor = {64, 64, 64};
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                    window.close();
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                    // camera.TranslateZ(camSpeed);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                    // camera.TranslateZ(-camSpeed);
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
                    camera.RotateX(camSpeed/0.2);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
                    camera.RotateX(-camSpeed/0.2);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) {
                    camera.RotateY(camSpeed/0.2);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
                    camera.RotateY(-camSpeed/0.2);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) {
                    camera.RotateZ(camSpeed/0.2);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
                    camera.RotateZ(-camSpeed/0.2);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)) {
                    camera.Scale(+50);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash)) {
                    camera.Scale(-50);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
                    spin = true;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
                    spin = false;
                }
            }

            if(spin){
                camera.RotateX(0.05 * M_2_PI);
                camera.RotateY(0.05 * M_2_PI + 0.05);
            }

        window.clear(clearColor);

        auto start = std::chrono::high_resolution_clock::now();
        DrawModelGeometricVerts(cube, texture,  camera, window);
        auto end = std::chrono::high_resolution_clock::now(); 
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        std::string frametime = std::to_string(duration.count()) + " ms";

        controls.setString(move + "\n" + rotate + "\n" + scale + "\n" + spinny + "\n" + tris + "\n" + frametime);
        window.draw(controls);

        window.display();
    }
    return 0;
}