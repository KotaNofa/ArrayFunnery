#ifndef PARSER_H
#define PARSER_H

#include "structs.h"

#include <SFML/Graphics.hpp>

#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <chrono>
#include <array>
#include <thread>
#include <mutex>

void ObjToModelParser(std::string name, Model& output) {

    std::thread::id id = std::this_thread::get_id();
    std::cout << "Executed on this thread BTW: " << id << std::endl;

    std::ifstream file(name);
    if (!file) {
        std::cout << "Failed to find model: " << name << std::endl;
        return;
    }
    
    std::string line;
    std::string type;
    float x, y, z;
    std::string i1, i2, i3, i4 = "";
    // i4 needs to be set empty in case of triangle

    std::vector<std::array<float, 3>> geos;
    geos.push_back(std::array<float, 3>{x, y, z});
    std::vector<std::array<float, 3>> normals;
    normals.push_back(std::array<float, 3>{x, y, z});
    std::vector<std::array<float, 2>> uvs;
    uvs.push_back(std::array<float, 2>{x, y});

    std::vector<unsigned int> geoIndices;
    std::vector<unsigned int> normalIndices;
    std::vector<unsigned int> uvIndices;

    std::cout << "Beginning parse of: " << name << std::endl;
    while (std::getline(file, line)) {

        std::stringstream input(line);
        input >> type;

        // Verts
        if (type == "v") {
            input >> x >> y >> z;
            geos.push_back({x,y,z});
            std::cout << "Vert Geometry: " << x << " " << y << " " << z << std::endl;
        }
        else if (type == "vn") {
            input >> x >> y >> z;
            normals.push_back({x, y, z});
            std::cout << "Vert Normal: " << x << " " << y << " " << z << std::endl;            
        }
        else if (type == "vt") {
            input >> x >> y;
            uvs.push_back({x, y});
            std::cout << "Vert UV: " << x << " " << y << std::endl;
        } 
        else if (type == "f") {
            input >> i1 >> i2 >> i3 >> i4;
        }
    }

    std::cout << "Model has total vert count of " << output.verts.size() << ", and a tri count of " << output.indices.size() << ". that's big, right?" << std::endl;
}

void ModelLoader(std::string modelList, Scene& output) {

    auto start = std::chrono::high_resolution_clock::now();

    std::ifstream file(modelList);
    if (!file) {
        std::cout << "Failed to find model list: " << modelList << std::endl;
    }
    unsigned int threadCount = std::thread::hardware_concurrency();
    unsigned int batchSize = threadCount / 4;
    std::cout << "You'll have " << threadCount << " threads working"<< std::endl;

    std::string line;
    std::string name;
    std::vector<std::string> list;
    
    while(std::getline(file, line)) {
        std::stringstream input(line);
        input >> name;
        if (!name.empty()) {
            list.push_back("model/" + name);
            output.models.push_back({});
        }
    }
    
    for (int i = 0; i < list.size(); i += batchSize) {
        std::vector<std::thread> threads;
        for (int j = 0; j < batchSize && (i + j) < list.size(); ++j) {
            threads.emplace_back(ObjToModelParser, list[i + j], std::ref(output.models.at(j + i)));
        }
        for (auto& t : threads) {
            t.join();
        } 
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Loaded " << list.size() << " models in " << duration.count() << "ms" << std::endl;
}


#endif