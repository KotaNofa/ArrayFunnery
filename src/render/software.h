#ifndef SOFTWARE_H
#define SOFTWARE_H

#include "struct/model.h"
#include "struct/viewport.h"

#include "SFML/Graphics.hpp"

void DrawModelGeometricVerts(const Model& model, sf::Texture texture, const Viewport& viewport, sf::RenderWindow& window);

#endif