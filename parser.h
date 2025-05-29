#ifndef PARSER_H
#define PARSER_H

#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <chrono>

#include "structs.h"

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
    int vertCount = 0;
    int i = 0;
    int j = 0;

    std::vector<Vertices> tempVerts;
    std::vector<Indices> tempIndices;

    std::cout << "Beginning parse of: " << name << std::endl;
    while (std::getline(file, line)) {

        auto start = std::chrono::high_resolution_clock::now();
        std::stringstream input(line);
        input >> type;

        // Geometric Verts
        if (type == "v") {
            input >> x >> y >> z;
            std::cout << "Geometric Vert " << x << " " << y << " " << z << std::endl;

            output.verts.push_back({{x,y,z},{0,0,0},{0,0}});

            ++vertCount;
        }

        if (type == "vn") {
            input >> x >> y >> z;
            std::cout << "Normal Vert " << x << " " << y << " " << z << std::endl;

        }

        if (type == "vt") {
            std::cout << "UV Vert " << x << " " << y << " " << z << std::endl;

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
                std::cout << "Geometric Indice " << geo1 << "/" << geo2 << "/" << geo3 <<  "/" << geo4 << " Quad -> Tris " << std::endl;
                std::cout << "   " << geo1 << " " << geo2 << " " << geo3 << " , " << geo1 << " " << geo3<< " " << geo4 << std::endl;
            }
            // Tri case
            else {
                std::cout << "Geometric Indice  " << geo1 << "/" << geo2 << "/" << geo3 << " Tri :)" << std::endl;
                output.indices.push_back({geo1, geo2, geo3});
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Model finished parsing in " << duration.count() << "ms a total vert count of " << output.verts.size() << ", and a tri count of " << output.indices.size() << ". that's big, right?" << std::endl;

    return output;
}

#endif