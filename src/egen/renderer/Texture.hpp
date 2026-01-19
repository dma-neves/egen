#pragma once

#include <filesystem>

#include "platform/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>


namespace egen
{
class Texture
{
public:
    Texture(const std::filesystem::path& texture_path);

    GLuint get();

private:
    GLuint m_texture;
};
}
