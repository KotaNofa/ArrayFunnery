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

void ObjParse(std::string modelDir, Model& output) {

    std::ifstream file(modelDir);
    Model tempModel;
    std::string lineBuffer;
    std::string dataType;
    float x, y, z;
    std::array<std::string, 4>indexChunk;

    if (!file) {
        std::cout << "Failed to find " << modelDir << std::endl;
        return;
    }

    std::cout << "Beginning parse of: " << modelDir << std::endl;
    while (std::getline(file, lineBuffer)) {

        std::stringstream stringRead(lineBuffer);
        stringRead >> dataType;

        // Geometric Vertice
        if (dataType == "v") {
            stringRead >> x >> y >> z;
            tempModel.geometricVerts.push_back({x , y, z});
            std::cout << "Vert Geometry: " << x << " " << y << " " << z << std::endl;
        }

        // Normal Vertice
        else if (dataType == "vn") {
            stringRead >> x >> y >> z;
            tempModel.normalVerts.push_back({x , y, z});
            std::cout << "Vert Normal: " << x << " " << y << " " << z << std::endl;            
        }

        // UV Vertice
        else if (dataType == "vt") {
            stringRead >> x >> y;
            tempModel.uvsVerts.push_back({x , y});
            std::cout << "Vert UV: " << x << " " << y << std::endl;
        }

        // Push arranged data from tempModel into output according to its indices.
        else if (dataType == "f") {
            stringRead >> indexChunk[0] >> indexChunk[1] >> indexChunk[2] >> indexChunk[3];
            std::string tempStr;
            // triangle indices case
            if (indexChunk[3].empty()) {
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < indexChunk[i].size(); j++) {
                        if (indexChunk[i].at(j) != '/') {
                            tempStr.push_back(indexChunk[i].at(j));
                        }
                        else {
                            // Delete chars up to the next occurance of '/'
                            indexChunk[i].erase(0, indexChunk[i].find_first_of('/') + 1);
                            break;
                        }
                    }
                    output.geometricVerts.push_back(tempModel.geometricVerts.at(std::stoi(tempStr) - 1));
                    tempStr.clear();
                }
                
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < indexChunk[i].size(); j++) {
                        if (indexChunk[i].at(j) != '/') {
                            tempStr.push_back(indexChunk[i].at(j));
                        }
                        else {
                            indexChunk[i].erase(0, indexChunk[i].find_first_of('/') + 1);
                            break;
                        }
                    }
                    output.normalVerts.push_back(tempModel.normalVerts.at(std::stoi(tempStr) - 1));
                    tempStr.clear();
                }
                
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < indexChunk[i].size(); j++) {
                        if (indexChunk[i].at(j) != '/') {
                            tempStr.push_back(indexChunk[i].at(j));
                        }
                        else {
                            indexChunk[i].erase(0, indexChunk[i].find_first_of('/') + 1);
                            break;
                        }
                    }
                    output.uvsVerts.push_back(tempModel.uvsVerts.at(std::stoi(tempStr) - 1));
                    tempStr.clear();
                }
            }
            // quad case, split into tris
            else {
                // todo:
            }
        }
    }

    /*
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

     */

    std::cout << "   " << modelDir << " has total vert count of " << tempModel.normalVerts.size() << ". That's big, right?" << std::endl;
    // std::cout << output.verts[0].geo[0] << std::endl;
    // std::cout << output.verts[0].geo[1] << std::endl;
    // std::cout << output.verts[0].geo[2] << std::endl;
    // std::cout << std::endl;
};

