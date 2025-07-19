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
    std::array<std::string, 4>inputChunk;

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
            stringRead >> inputChunk[0] >> inputChunk[1] >> inputChunk[2] >> inputChunk[3];
            std::string outputIndex;
            // Triangle indices case
            if (inputChunk[3].empty()) {
                // Pushes in geometric verts push according to each chunk's first number in it's indices.
                for (int chunkIndex = 0; chunkIndex < 3; chunkIndex++) {
                    for (int chunkCharIndex = 0; chunkCharIndex < inputChunk[chunkIndex].size(); chunkCharIndex++) {
                        if (inputChunk[chunkIndex].at(chunkCharIndex) != '/') {
                            // Reading in current indice chunk and pushing it back into outputIndex if it is not a backslash.
                            outputIndex.push_back(inputChunk[chunkIndex].at(chunkCharIndex));
                        }
                        else {
                            // Delete chars up to the next occurance of '/'
                            inputChunk[chunkIndex].erase(0, inputChunk[chunkIndex].find_first_of('/') + 1);
                            break;
                        }
                    }
                    // Pushes back index according to it's read-in string value, subtracted by one since OBJ is indexed at 1.
                    output.geometricVerts.push_back(tempModel.geometricVerts.at(std::stoi(outputIndex) - 1));
                    // Clears string index for next chunk.
                    outputIndex.clear();
                }
            }
            // Quad case
            else {
                // TODO: Split Quads into Tris
                throw std::runtime_error("OBJ Doesn't support parsing quads right now.");
            }
        // Parsing should be completed by    here
        } else if (dataType == "") {
            break;
        }
    }

    std::cout << "   " << modelDir << " has total triangle count of " << (output.geometricVerts.size() / 3) << ". That's big, right?" << std::endl;
    return;
};

