#pragma once

#include "egen/renderer/Texture.hpp"

namespace egen
{

struct Material
{
    Texture* diffuse = nullptr;
    Texture* specular = nullptr;
    float shininess = 32.f;
};

}