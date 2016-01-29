#pragma once
#include "ResourceManager.h"

#include <SFML/Graphics/Texture.hpp>

using TextureHolder = ResourceManager<sf::Texture, std::string>;
