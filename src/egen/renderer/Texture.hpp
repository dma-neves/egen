#pragma once

#include "platform/glad/include/glad/glad.h"
#include <GLFW/glfw3.h>

#include "egen/filesystem/vfs.hpp"

namespace egen
{
class Texture
{
public:
    Texture(const VFS& vfs, const std::string& texture_path);

    GLuint get();

private:
    GLuint m_texture;
};
}
