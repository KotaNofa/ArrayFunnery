#ifndef RENDER_H
#define RENDER_H

#include "model.h"
#include "viewport.h"

#include "SFML/Graphics.hpp"

void Render(const Scene& scene, const Viewport& viewport, sf::RenderWindow& window);

#endif