#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include "Vertex.h"

class Object {
public:

	std::vector<Vertex> vertices; // The vertices that make up the model

	Object();

};

#endif // !MODEL_H