#pragma once

#include "egen/renderer/Texture.hpp"
#include "egen/util/OptionalRef.hpp"

#include <glm/glm.hpp>

namespace egen
{

enum MaterialType 
{
    Solid = 0,
    Basic = 1, 
    Mapped = 2,
};

struct Material
{
    Material(MaterialType type_) : type(type_){}

    MaterialType type;
};

struct SolidMaterial : Material
{
    SolidMaterial(MaterialType type) : Material(type){}

    glm::vec3 diffuse;
    glm::vec3 specular;
    glm::vec3 ambient;
    glm::vec3 shininess;
};

struct BasicMaterial : Material
{
    BasicMaterial(MaterialType type) : Material(type){}

    OptionalRef<Texture> diffuse;
    float specular;
    float ambient;
    float shininess;
};

struct MappedMaterial : Material
{
    MappedMaterial(MaterialType type) : Material(type){}

    OptionalRef<Texture> diffuse;
    OptionalRef<Texture> specular;
    float ambient;
    float shininess;
};

}