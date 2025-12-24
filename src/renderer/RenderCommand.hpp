#pragma once

#include "renderer/Shader.hpp"
#include "renderer/Texture.hpp"

#include <cstdint>

namespace egen
{
    class RenderCommand
    {
        uint32_t vao;
        uint32_t index_count;
        Shader* shader;
        Texture* texture;
        //glm::mat4 transform;
    };
}
