#pragma once

#include "Utility/OptionsManager.hpp"
#include "Utility/ResourceHolder.hpp"

struct Context
{
    OptionsManager om;
    TextureHolder tex;
    FontHolder fonts;
    ShaderHolder shaders;

    sf::Vector2u windowSize;
};
