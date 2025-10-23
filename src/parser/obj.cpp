#include "parser/obj.h"
#include "struct/model.h"

#include <array>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

void ObjParse(std::string modelDir, Model& output) {

    std::vector<Vector3f> geometricBuffer;
    std::vector<Vector3f> normalBuffer;
    std::vector<Vector2f> uvBuffer;
    std::vector<std::array<std::string, 4>> TriangleBuffer; // kill me

    std::ifstream file(modelDir);
    std::string lineBuffer;
    std::string dataType;
    bool ObjectLoaded = false; // For now, this just prevents you from parsing an OBJ with multiple objects in it.

    if (!file) {
        std::cout << "Failed to find " << modelDir << std::endl;
        return;
    }

    std::cout << "Beginning parse of: " << modelDir << std::endl;
    while (std::getline(file, lineBuffer)) {

        std::stringstream stringRead(lineBuffer);
        stringRead >> dataType;
        float x, y, z;
        std::array<std::string, 4>indice;

        // Object Name
        if (dataType == "o") {
            if (ObjectLoaded == false) {
                std::string name;
                stringRead >> name;
                output.name = name;
                std::cout << "in Name: " << name << std::endl;
                ObjectLoaded = true;
            } else {
                throw std::runtime_error("Second object detected in OBJ, this is not allowed right now");
            }
        }

        // Geometric Vertice
        if (dataType == "v") {
            stringRead >> x >> y >> z;
            geometricBuffer.push_back({x , y, z});
            // std::cout << "in Geometry: " << x << " " << y << " " << z << std::endl;
        }

        // Normal Vertice
        else if (dataType == "vn") {
            stringRead >> x >> y >> z;
            normalBuffer.push_back({x , y, z});
            // std::cout << "in Normal: " << x << " " << y << " " << z << std::endl;            
        }

        // UV Vertice
        else if (dataType == "vt") {
            stringRead >> x >> y;
            uvBuffer.push_back({x , y});
            // std::cout << "in UV: " << x << " " << y << std::endl;
        }

        else if (dataType == "f") {
            stringRead >> indice[0] >> indice[1] >> indice[2] >> indice[3];
            TriangleBuffer.push_back({indice[0],indice[1],indice[2],indice[3]});
        }

        else if (dataType == "") {
            break;
        }
    }
    
    // std::cout << "End of data, building model..." << std::endl;

    for (int triIndex = 0; triIndex < TriangleBuffer.size(); triIndex++) {
        for (int chunkIndex = 0; chunkIndex < 3; chunkIndex++) {
            std::string& chunk = TriangleBuffer[triIndex][chunkIndex];
            std::stringstream chunkStream(chunk);
            std::string indexStr;
            int dataSel = 0;

            Vertex assembledFrame;

            while (std::getline(chunkStream, indexStr, '/')) {
                if (indexStr.empty()) {
                    ++dataSel;
                    continue;
                }

                int index = std::stoi(indexStr) - 1; // OBJ is 1-based
                switch (dataSel) {
                    case 0:
                        assembledFrame.geometricCoord = geometricBuffer.at(index);
                        break;
                    case 1:
                        assembledFrame.uvCoord = uvBuffer.at(index);
                        break;
                    case 2:
                        assembledFrame.normalCoord = normalBuffer.at(index);
                        break;
                }
                ++dataSel;
            }

            output.vertices.push_back(assembledFrame);
        }
    }

    // std::cout << "   " << modelDir << " has total triangle count of " << output.vertices.size() / 3 << ". That's big, right?" << std::endl;
    return;
};

