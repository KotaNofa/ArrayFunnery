#ifndef STRUCTS_H
#define STRUCTS+H

#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <chrono>

class Vertices {
public:
    float geo[3];
    float normal[3];
    float uv[2];
};

class Indices {
public:
    unsigned int i_geo[3];
    unsigned int i_normal[3];
    unsigned int i_uv[3];
};

struct Model {
    std::vector<Vertices>verts;
    std::vector<Indices>indices;
    sf::Texture texture;
};

#endif STRUCTS_H