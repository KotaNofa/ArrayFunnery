#include "parser.h"

#include "model.h"

#include <array>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <thread>
#include <iostream>
#include <chrono>
#include <algorithm>

// Source file for difference parsers, should be read to add other filetypes.

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
        if (i < v_geos.size()) {
        output.verts[i].geo[0] = v_geos[i][0];
        output.verts[i].geo[1] = v_geos[i][1];
        output.verts[i].geo[2] = v_geos[i][2];

        output.verts[i].normal[0] = v_normals[i][0];
        output.verts[i].normal[1] = v_normals[i][1];
        output.verts[i].normal[2] = v_normals[i][2];

        output.verts[i].uv[0] = {v_uvs[i][0]};
        output.verts[i].uv[1] = {v_uvs[i][1]};
        }
        else {break;}
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
};

