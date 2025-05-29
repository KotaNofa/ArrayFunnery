#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <chrono>

struct Vertices {
    // geometric verts
    float verts[3];
    // TODO: add normals, UVs, etc. as needed
};

struct Indices {
    // geometric indeces
    unsigned int indices[3];
    // TODO: add more for quads/ngons if needed
};

struct Model {
    std::vector<Vertices>verts;
    std::vector<Indices>indices;
    sf::Texture texture;
};

Model ObjToModelParser(std::string name) {

    auto start = std::chrono::high_resolution_clock::now();

    std::ifstream file(name);
    if (!file) std::cout << "Failed to find model: " << name << std::endl;
    
    Model output;
    std::string line;
    std::string type;
    float x, y, z;
    std::string i1, i2, i3, i4 = "";
    // i4 needs to be set empty in case of triangle
    
    std::cout << "Beginning parse of: " << name << std::endl;
    while (std::getline(file, line)) {

        auto start = std::chrono::high_resolution_clock::now();
        std::stringstream input(line);
        input >> type;

        // Geometric Verts
        if (type == "v") {
            input >> x >> y >> z;
            // std::cout << type << " " << x << " " << y << " " << z << std::endl;
            output.verts.push_back({x, y, z});
        }

        // Geometric Indices
        if (type == "f") {

            // TODO: This only gets geometric indeces. Will need texture coordinate index and normal index later.
            input >> i1 >> i2 >> i3 >> i4;
            unsigned int geo1 = std::stoi(i1.substr(0, i1.find('/'))) - 1;
            unsigned int geo2 = std::stoi(i2.substr(0, i2.find('/'))) - 1;
            unsigned int geo3 = std::stoi(i3.substr(0, i3.find('/'))) - 1;

            // Quad case
            if (!i4.empty()) {
                unsigned int geo4 = std::stoi(i4.substr(0, i4.find('/'))) - 1;            
                output.indices.push_back({geo1, geo2, geo3});
                output.indices.push_back({geo1, geo3, geo4});
                // std::cout << type << " " << geo1 << "/" << geo2 << "/" << geo3 <<  "/" << geo4 << " Quad -> Tris " << std::endl;
                // std::cout << "   " << geo1 << " " << geo2 << " " << geo3 << " , " << geo1 << " " << geo3<< " " << geo4 << std::endl;
            }
            // Tri case
            else {
                // std::cout << type << " " << geo1 << "/" << geo2 << "/" << geo3 << " Tri :)" << std::endl;
                output.indices.push_back({geo1, geo2, geo3});
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Model finished parsing in " << duration.count() << "ms a total vert count of " << output.verts.size() << ", and a tri count of " << output.indices.size() << ". that's big, right?" << std::endl;

    return output;
}

int main() {

    ObjToModelParser("model/bigscene.obj");

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