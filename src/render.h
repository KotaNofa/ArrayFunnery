#ifndef RENDER_H
#define RENDER_H

#include "model.h"
#include "viewport.h"

#include "SFML/Graphics.hpp"

void DrawModelGeometricVerts(const Model& scene, const Viewport& viewport, sf::RenderWindow& window);

#endif