#ifndef RENDER_H
#define RENDER_H

#include "model.h"
#include "viewport.h"

#include "SFML/Graphics.hpp"

void DrawVerts(const Model& scene, const Viewport& viewport, sf::RenderWindow& window);

#endif