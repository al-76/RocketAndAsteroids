#pragma once

#include <string>

#include "graphics.h"

struct SpriteComponent final {
    std::string fileName;
    sf::Texture texture;
    sf::Sprite sprite;
};