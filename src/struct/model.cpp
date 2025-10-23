#include "model.h"
#include "parser/obj.h"
#include "viewport.h"

#include <SFML/Graphics.hpp>

Model::Model() {
};

void Model::InitFromOBJ(std::string dirName) {
    ObjParse(dirName, *this);
};


/*
// Multithreaded model loader. Shouldn't be too tough to adapt it to other file types. 
void Scene::loadModels(const std::string manifest) {

    auto start = std::chrono::high_resolution_clock::now();

    std::ifstream file(manifest);
    if (!file) {
        std::cout << "Failed to find model list: " << manifest << std::endl;
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
            models.push_back({});
        }
    }
    
    for (int i = 0; i < list.size(); i += batchSize) {
        std::vector<std::thread> threads;
        for (int j = 0; j < batchSize && (i + j) < list.size(); ++j) {
            threads.emplace_back(ObjToModelParser, list[i + j], std::ref(models.at(j + i)));
        }
        for (auto& t : threads) {
            t.join();
        } 
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Loaded " << list.size() << " models in " << duration.count() << "ms" << std::endl;
};

*/