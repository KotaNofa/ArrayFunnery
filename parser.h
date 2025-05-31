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

    std::ifstream file(name);
    if (!file) {
        std::cout << "Failed to find " << name << std::endl;
        return;
    }
    
    std::string line;
    std::string type;
    float x, y, z;
    std::string i1, i2, i3, i4 = "";
    // i4 needs to be set empty in case of triangle

    std::vector<std::array<float, 3>> v_geos;
    std::vector<std::array<float, 3>> v_normals;
    std::vector<std::array<float, 2>> v_uvs;

    std::vector<std::array<unsigned int, 3>> i_geos;
    std::vector<std::array<unsigned int, 3>> i_normals;
    std::vector<std::array<unsigned int, 3>> i_uvs;

    std::cout << "Beginning parse of: " << name << std::endl;
    while (std::getline(file, line)) {

        std::stringstream input(line);
        input >> type;

        // Verts
        if (type == "v") {
            input >> x >> y >> z;
            v_geos.push_back({x,y,z});
            // std::cout << "Vert Geometry: " << x << " " << y << " " << z << std::endl;
        }
        else if (type == "vn") {
            input >> x >> y >> z;
            v_normals.push_back({x, y, z});
            // std::cout << "Vert Normal: " << x << " " << y << " " << z << std::endl;            
        }
        else if (type == "vt") {
            input >> x >> y;
            v_uvs.push_back({x, y});
            // std::cout << "Vert UV: " << x << " " << y << std::endl;
        } 
        else if (type == "f") {
            input >> i1 >> i2 >> i3 >> i4;

            auto parseIndex = [](const std::string& vertexStr) -> unsigned int {
                size_t slashPos = vertexStr.find('/');
                std::string idxStr = (slashPos == std::string::npos) ? vertexStr : vertexStr.substr(0, slashPos);
                return static_cast<unsigned int>(std::stoi(idxStr)) - 1;  // OBJ indices are 1-based
            };

            // Push triangle from first 3 vertices
            i_geos.push_back({
                parseIndex(i1),
                parseIndex(i2),
                parseIndex(i3)
            });

            // If there's a fourth vertex, triangulate quad into two triangles
            if (!i4.empty()) {
                i_geos.push_back({
                    parseIndex(i1),
                    parseIndex(i3),
                    parseIndex(i4)
                });
            }
        }
    }


    // find largest 
    size_t largestIndex = std::max({v_geos.size(), v_normals.size(), v_uvs.size()});
    // resize to largest index found in list
    output.verts.resize(largestIndex);
    // copying to output
    for (int i = 0; i < largestIndex; ++i) {
        output.verts[i].geo[0] = v_geos[i][0];
        output.verts[i].geo[1] = v_geos[i][1];
        output.verts[i].geo[2] = v_geos[i][2];

        output.verts[i].normal[0] = v_normals[i][0];
        output.verts[i].normal[1] = v_normals[i][1];
        output.verts[i].normal[2] = v_normals[i][2];

        output.verts[i].uv[0] = {v_uvs[i][0]};
        output.verts[i].uv[1] = {v_uvs[i][1]};
    }

    output.indices.resize(i_geos.size());
    for (size_t i = 0; i < i_geos.size(); ++i) {
        output.indices[i].geo[0] = i_geos[i][0];
        output.indices[i].geo[1] = i_geos[i][1];
        output.indices[i].geo[2] = i_geos[i][2];
    }


    std::cout << "   " << name << " has total vert count of " << v_geos.size() << ". That's big, right?" << std::endl;
    // std::cout << output.verts[0].geo[0] << std::endl;
    // std::cout << output.verts[0].geo[1] << std::endl;
    // std::cout << output.verts[0].geo[2] << std::endl;
    // std::cout << std::endl;
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